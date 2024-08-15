// PDFC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

const char *quality_levels[] = {"/default", "/prepress", "/printer", "/ebook", "/screen"};

void compress(const char *input_file_path, const char *output_file_path, int power) {
    if (access(input_file_path, F_OK) == -1) {
        fprintf(stderr, "Error: invalid path for input PDF file: %s\n", input_file_path);
        exit(1);
    }

    if (power < 0 || power > 4) {
        fprintf(stderr, "Error: invalid compression level: %d\n", power);
        exit(1);
    }

    const char *ext = strrchr(input_file_path, '.');
    if (!ext || strcmp(ext, ".pdf") != 0) {
        fprintf(stderr, "Error: input file is not a PDF: %s\n", input_file_path);
        exit(1);
    }

    const char *gs = NULL;
    const char *gs_names[] = {"/opt/homebrew/bin/gs", "/usr/local/bin/homebrew/", "gs", "gswin32", "gswin64"};
    for (int i = 0; i < 3; i++) {
        if (access(gs_names[i], X_OK) != -1) {
            gs = gs_names[i];
            break;
        }
    }

    if (!gs) {
        fprintf(stderr, "No GhostScript executable was found on path.\n");
        exit(1);
    }

    printf("Compressing PDF...\n");

    struct stat st;
    stat(input_file_path, &st);
    long initial_size = st.st_size;

    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "%s -sDEVICE=pdfwrite -dCompatibilityLevel=1.5 -dPDFSETTINGS=%s -dNOPAUSE -dQUIET -dBATCH -sOutputFile=%s %s", gs, quality_levels[power], output_file_path, input_file_path);
    system(cmd);

    stat(output_file_path, &st);
    long final_size = st.st_size;

    double ratio = 1.0 - ((double)final_size / initial_size);
    printf("Compression by %.0f%%.\n", ratio * 100);
    printf("Final file size is %.5fMB\n", final_size / 1000000.0);
    printf("Done.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s input_file [-o output_file] [-c compress_level] [-b] [--open]\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = "temp.pdf";
    int compress_level = 2;
    int backup = 0;
    int open_pdf = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            compress_level = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-b") == 0) {
            backup = 1;
        } else if (strcmp(argv[i], "--open") == 0) {
            open_pdf = 1;
        }
    }

    compress(input_file, output_file, compress_level);

    if (strcmp(output_file, "temp.pdf") == 0) {
        if (backup) {
            char backup_file[1024];
            snprintf(backup_file, sizeof(backup_file), "%s_BACKUP.pdf", input_file);
            rename(input_file, backup_file);
        }
        rename(output_file, input_file);
        remove(output_file);
    }

    if (open_pdf) {
        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "open %s", (strcmp(output_file, "temp.pdf") == 0 && backup) ? input_file : output_file);
        system(cmd);
    }

    return 0;
}


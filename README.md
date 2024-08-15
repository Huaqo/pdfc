
# PDF Compressor Tool (`pdfc`)

## Overview

`pdfc` is a command-line utility for compressing PDF files using GhostScript. It allows you to specify the compression quality, create backups, and optionally open the compressed PDF after processing. This tool can be easily installed via Homebrew.

## Features

- **Compression Levels**: Choose from five different compression quality levels (`/default`, `/prepress`, `/printer`, `/ebook`, `/screen`).
- **Custom Output**: Specify a custom output file name for the compressed PDF.
- **Backup Option**: Automatically backup the original PDF before compressing it.
- **Open PDF**: Optionally open the compressed PDF using the default PDF viewer after processing.

## Installation

Download and run the current release.

## Usage

```bash
pdfc input_file [-o output_file] [-c compress_level] [-b] [--open]
```

### Parameters

- `input_file`: (Required) The path to the input PDF file you want to compress.
- `-o output_file`: (Optional) The path for the output PDF file. If not specified, a temporary file (`temp.pdf`) will be used and can overwrite the original file if no other name is given.
- `-c compress_level`: (Optional) Compression level:
  - `0` - `/default`
  - `1` - `/prepress`
  - `2` - `/printer` (default)
  - `3` - `/ebook`
  - `4` - `/screen`
- `-b`: (Optional) If provided, the original PDF file will be backed up with a `_BACKUP.pdf` suffix.
- `--open`: (Optional) Opens the compressed PDF after processing.

### Example Commands

1. **Basic Compression with Default Settings**:
    ```bash
    pdfc myfile.pdf
    ```
    This will compress `myfile.pdf` with the `/printer` quality level and overwrite the original file.

2. **Compression with Custom Output**:
    ```bash
    pdfc myfile.pdf -o compressed.pdf
    ```
    This will compress `myfile.pdf` with the `/printer` quality level and save it as `compressed.pdf`.

3. **Compression with Backup and Custom Quality**:
    ```bash
    pdfc myfile.pdf -c 4 -b
    ```
    This will compress `myfile.pdf` with the `/screen` quality level, create a backup of the original file, and overwrite the original with the compressed version.

4. **Compression and Open PDF Afterward**:
    ```bash
    pdfc myfile.pdf --open
    ```
    This will compress `myfile.pdf` and then open the compressed file using the default PDF viewer.

## Error Handling

- The script will exit with an error message if:
  - The input file path is invalid.
  - The input file is not a PDF.
  - An invalid compression level is provided.
  - GhostScript is not installed or cannot be found.

## Notes

- The script assumes you are running on a Unix-like system with GhostScript installed. Adjustments may be needed for other environments.
- For Windows, ensure `gswin32` or `gswin64` is installed and accessible from the command line.

## License

This tool is provided as-is, without any warranties. Use at your own risk.

## Contact

For any issues or suggestions, please contact the developer at [joa.gottlebe@gmail.com].

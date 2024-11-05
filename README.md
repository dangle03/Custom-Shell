# Simple Shell Program in C

This project is a simple shell program written in C that simulates basic command-line operations, such as changing directories, listing files, creating files, and displaying help information. This shell offers a foundational look at how command-line interpreters work, using system calls and handling common tasks in a Unix-like environment.

## Purpose

The purpose of this shell program is to mimic some of the standard commands in a Unix-like command-line interface. It provides functionality for basic file and directory management, allowing users to interact with the system from a custom-built interface. This project is ideal for understanding how to construct a simple command processor in C, while also demonstrating low-level interactions with the operating system.

## Features

- **Command Parsing and Tokenization**: Uses a custom `tokenize` function to split input into arguments for handling.
- **Directory Navigation**: Implements a `cd` command to change directories.
- **File Creation**: Provides a `touch` command to create new files or update timestamps on existing files.
- **Directory Listing**: Includes an `ls` command to list directory contents, excluding hidden files.
- **Help Menu**: Displays available commands and their usage.
- **Current Working Directory**: Dynamically displays the working directory in the prompt, replacing the home directory with `~` for ease of use.
- **Error Handling**: Detects invalid commands and provides error messages for operation failures, such as missing directories or permission errors.

## Skills Showcased

- **C Programming**: Core skills in pointers, memory management, and error handling.
- **System Calls**: Demonstrates use of `open`, `chdir`, `getcwd`, `opendir`, and `utime` for managing files and directories.
- **File Operations**: Provides functionality for creating files with specified permissions and updating modification times.
- **String Manipulation**: Utilizes `strtok` for tokenizing input and `strdup` for managing memory safely.
- **Environment Variable Handling**: Uses the `HOME` environment variable for directory navigation and prompt customization.

## Requirements

- **Compiler**: `gcc` or any other C compiler.
- **Operating System**: Unix-like OS (Linux, macOS) is recommended, as the program relies on POSIX-compliant functions.

## Installation

1. Clone the repository or download the code files.
2. run the pre-compiled executable
   ```bash
   ./custom-shell
   ```

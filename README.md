# Mini Shell in C

## Overview
A simple Unix-like shell implemented in C.  
Supports basic command parsing, process execution, input/output redirection, signal handling, and changing directories.

## Features
- Execute standard Linux commands using `fork` and `execvp`.
- Built-in `cd` command to change directories.
- Send signals (`SIGSTOP`, `SIGCONT`, `SIGINT`) to other processes with custom commands:
  - `stop <pid>`: send SIGSTOP
  - `wake <pid>`: send SIGCONT
  - `term <pid>`: send SIGINT
- Input redirection (`< file`) and output redirection (`> file`) support.
- Blocking and non-blocking command execution (background jobs).
- Dynamic display of the current working directory as the shell prompt.

## Technologies
- Language: C
- Process management: `fork`, `execvp`, `waitpid`, `kill`
- I/O Redirection: `open`, `close`
- Directory handling: `chdir`, `getcwd`

## Build Instructions
```bash
make
```

## How to run
```bash
./myshell
```

## Environment and Compilation
- Operating System: **Linux**
- Compilation Target: **32-bit** architecture

## Notes
- This project uses a helper parser (LineParser.h) to parse command-line input, which written by Lab's TA.
- This is a basic educational shell and not suitable for production use.
- Developed as part of the System Programming Extended Lab course at BGU.

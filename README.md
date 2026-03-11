<header>
<h1 align="center">
  <a href="https://github.com/jdecorte-be/pipex"><img src=".assets/banner.png" alt="pipex" ></a>
  pipex
  <br>
</h1>

<p align="center">
  A C program that reproduces the behavior of the shell pipe (`|`). This 42 school project uses `fork()`, `pipe()`, and `dup2()` to manage processes and I/O.
</p>

<p align="center">
<a href="https://www.42.fr/">
    <img src="https://img.shields.io/badge/42-School%20Project-00BABC?logo=42&logoColor=white&labelColor=000000"
         alt="42 School Project">
  </a>
<a href="#">
    <img src="https://img.shields.io/badge/Type-CLI%20Tool-blue?logo=gnubash&logoColor=white&labelColor=000000"
         alt="Type CLI Tool">
  </a>
<a href="#">
    <img src="https://img.shields.io/badge/Focus-System%20Programming-informational?logo=linux&logoColor=white&labelColor=000000"
         alt="Focus System Programming">
  </a>
<a href="#">
    <img src="https://img.shields.io/badge/Technology-IPC%20%28pipe%2Ffork%29-orange?logo=c&logoColor=white&labelColor=000000"
         alt="Technology IPC (pipe/fork)">
  </a>
</p>

<p align="center">
<a href="#">
    <img src="https://img.shields.io/badge/Platform-Unix--like-lightgrey?logo=unix&logoColor=white&labelColor=000000"
         alt="Platform Unix-like">
  </a>
  <a href="https://github.com/jdecorte-be/pipex/stargazers">
    <img src="https://img.shields.io/github/stars/jdecorte-be/pipex?logo=star&logoColor=white&labelColor=000000&color=E6DB74"
         alt="pipex stars">
  </a>
  <a href="https://github.com/jdecorte-be/pipex/issues">
    <img src="https://img.shields.io/github/issues/jdecorte-be/pipex?logoColor=white&labelColor=000000&color=orange"
         alt="pipex issues">
  </a>
  <a href="https://github.com/jdecorte-be/pipex">
    <img src="https://img.shields.io/github/repo-size/jdecorte-be/pipex?logo=database&logoColor=white&labelColor=000000&color=AE81FF"
         alt="pipex repo size">
  </a>
  <a href="https://github.com/jdecorte-be/pipex">
    <img src="https://img.shields.io/github/languages/top/jdecorte-be/pipex?logo=code&logoColor=white&labelColor=000000&color=A6E22E"
         alt="pipex top language">
  </a>
  <a href="https://github.com/jdecorte-be/pipex/commits">
    <img src="https://img.shields.io/github/last-commit/jdecorte-be/pipex?logo=clock&logoColor=white&labelColor=000000&color=66D9EF"
         alt="pipex last commit">
  </a>
</p>

</header>

---

This project is a C program that reproduces the behavior of the shell pipe (`|`). It's a 42 school assignment designed to provide a deeper understanding of process creation and inter-process communication in Unix-like operating systems using system calls like `pipe()`, `fork()`, `dup2()`, and `execve()`.

### Features

*   **Mandatory Part:** Replicates the behavior of `< infile cmd1 | cmd2 > outfile`.
*   **Bonus Part:**
    *   Supports multiple pipes: `< infile cmd1 | cmd2 | ... | cmdn > outfile`.
    *   Supports `here_doc` input: `cmd1 << LIMITER | cmd2 >> outfile`.

## Getting Started

### Prerequisites

*   A C compiler (like `gcc` or `clang`)
*   `make`

### Building the Project

1.  Clone the repository:
    ```shell
    git clone https://github.com/jdecorte-be/pipex.git
    cd pipex
    ```

2.  The project includes a `libft` submodule. Initialize and update it:
    ```shell
    git submodule update --init --recursive
    ```

3.  Compile the program using the `Makefile`:
    ```shell
    # For the mandatory part
    make

    # For the bonus part (multiple pipes and here_doc)
    make bonus
    ```

## Usage

### Mandatory

The program takes four arguments: an input file, two commands, and an output file. It redirects the output of the first command to the input of the second command.

**Syntax:**
```shell
./pipex <infile> <cmd1> <cmd2> <outfile>
```

**Example:**
This is equivalent to the shell command: `< infile grep a1 | wc -l > outfile`
```shell
./pipex infile "grep a1" "wc -l" outfile
```

### Bonus: Multiple Pipes

The bonus version can handle an arbitrary number of commands chained together.

**Syntax:**
```shell
./pipex <infile> <cmd1> <cmd2> <cmd3> ... <outfile>
```

**Example:**
Equivalent to: `< infile grep a | cat -e | wc -l > outfile`
```shell
./pipex infile "grep a" "cat -e" "wc -l" outfile
```

### Bonus: Here Document (`here_doc`)

The bonus version also supports `here_doc` as an input source.

**Syntax:**
```shell
./pipex here_doc <LIMITER> <cmd1> <cmd2> ... <outfile>
```

**Example:**
Reads from standard input until `EOF` is entered, then pipes the result through `grep` and `wc`.
```shell
./pipex here_doc EOF "grep a" "wc -w" outfile
```

## Core Concepts

This project revolves around orchestrating multiple processes and managing their input and output streams. The goal is to create a data flow like this:

`infile` -> `[stdin]` **cmd1** `[stdout]` -> `[pipe]` -> `[stdin]` **cmd2** `[stdout]` -> `outfile`

This is achieved using four key system calls.

### 1. `pipe()` - Inter-Process Communication

A pipe is a unidirectional data channel that allows one process to send data to another.

```c
int pipe(int pipefd[2]);
```

*   `pipe()` creates a pipe and returns two file descriptors in the `pipefd` array:
    *   `pipefd[0]`: The **read end** of the pipe.
    *   `pipefd[1]`: The **write end** of the pipe.
*   Data written to `pipefd[1]` can be read from `pipefd[0]`.

### 2. `fork()` - Process Creation

To run two commands simultaneously, we need two separate processes. `fork()` creates a new process by duplicating the calling process.

```c
pid_t fork(void);
```

*   **In the parent process**, `fork()` returns the process ID (PID) of the newly created child process.
*   **In the child process**, `fork()` returns `0`.
*   If an error occurs, it returns `-1`.

This allows us to execute different code blocks for the parent and child, enabling them to handle `cmd1` and `cmd2` respectively.

### 3. `dup2()` - I/O Redirection

By default, a process reads from standard input (`stdin`, fd 0) and writes to standard output (`stdout`, fd 1). `dup2()` allows us to redirect these streams.

```c
int dup2(int oldfd, int newfd);
```

`dup2()` makes `newfd` a copy of `oldfd`, closing `newfd` first if necessary. This is the key to connecting our files and pipes to the commands.

*   **For the first command (child process):**
    1.  Redirect `stdin` to read from `infile`: `dup2(infile_fd, STDIN_FILENO)`.
    2.  Redirect `stdout` to write to the pipe: `dup2(pipefd[1], STDOUT_FILENO)`.
*   **For the second command (parent process):**
    1.  Redirect `stdin` to read from the pipe: `dup2(pipefd[0], STDIN_FILENO)`.
    2.  Redirect `stdout` to write to `outfile`: `dup2(outfile_fd, STDOUT_FILENO)`.

### 4. `execve()` - Command Execution

The `execve()` system call replaces the current process image with a new program. This is how we run the user-specified commands (e.g., `ls`, `grep`, `wc`).

```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```

*   `pathname`: The absolute path to the command's executable (e.g., `/bin/ls`).
*   `argv[]`: An array of arguments for the command, with the first element being the command name itself (e.g., `{"ls", "-l", NULL}`).
*   `envp[]`: An array of environment variables, which is needed to find the command `pathname` if it's not an absolute path.

To find the correct `pathname`, we parse the `PATH` variable from `envp`, split it by `:`, and test each directory to find the executable.

## Debugging Tips

*   **Hanging Program:** If your program hangs, it's almost always because a pipe's file descriptor was not closed correctly. Every process that has access to the pipe must close **both** ends when it's done with them. The kernel will only signal "end-of-file" on the read end when all write ends have been closed.
*   **No Output:** `printf` writes to `stdout`. If you have redirected `stdout` using `dup2`, your debug messages will go to a file or a pipe, not the terminal. Use `perror()` or write directly to `stderr` (fd 2) for debugging messages that should always appear on the console.
    ```c
    // perror prints the error message for the last failed system call
    perror("Error executing command");

    // ft_putstr_fd is a useful function from libft
    ft_putstr_fd("Debug: In child process\n", STDERR_FILENO);
    ```
*   **Command Not Found:** Before calling `execve()`, use `access()` to check if the command executable exists and has the correct permissions. This allows you to provide a more informative error message, like `bash: cmd: command not found`.
*   **File Permissions:** Handle errors from `open()` gracefully. Your program should mimic the shell's behavior when `infile` doesn't exist or `outfile` cannot be written to.

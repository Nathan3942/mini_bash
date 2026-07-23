# Minishell

A simplified Unix shell written in C, built as part of 42's common core curriculum.

## About

Minishell is a reimplementation of a basic command-line interpreter, inspired by bash. The goal of the project is to understand how a shell actually works under the hood: reading and parsing user input, executing commands, handling pipes and redirections, managing environment variables, and reacting to signals — all without relying on any shell-parsing library.

## Features

- Interactive command-line prompt with history
- Execution of external commands (via `PATH` resolution and `execve`)
- Pipes (`|`) chaining multiple commands together
- Redirections: `<`, `>`, `>>`, and heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Proper handling of single and double quotes
- Signal handling matching bash's behavior (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Built-in commands implemented natively (no `execve` call):
  - `echo` (with `-n` option)
  - `cd` (relative and absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

### Bonus (if implemented)
- Logical operators `&&` and `||` with parentheses for priority
- Wildcard (`*`) expansion in the current directory

*(Check/remove bonus features depending on what you actually implemented.)*

## Build

```bash
make
```

This generates the `minishell` executable at the root of the project.

Other available targets:
```bash
make clean    # removes object files
make fclean   # removes object files and the executable
make re       # rebuilds the project from scratch
```

## Usage

```bash
./minishell
```

This launches an interactive prompt. Example session:

```
minishell$ echo "Hello, world!"
Hello, world!
minishell$ ls -l | grep .c | wc -l
4
minishell$ export MY_VAR=hello
minishell$ echo $MY_VAR
hello
minishell$ exit
```

## Project structure

```
minishell/
├── src/
│   ├── main.c
│   ├── parsing/
│   ├── execution/
│   ├── builtins/
│   ├── signals/
│   └── env/
├── includes/
├── libft/          # personal library reused across projects
├── Makefile
└── README.md
```

*(Adjust this tree to match your actual project structure.)*

## What I learned

- Writing a recursive-descent-style parser for a real-world grammar (tokens, quotes, operators)
- Process creation and management with `fork`, `execve`, and `waitpid`
- Building complex pipelines by chaining multiple processes via `pipe`
- File descriptor manipulation and redirection with `dup`/`dup2`
- Signal handling and how it interacts with a running process (`sigaction`)
- Managing a custom environment variable table without relying on `envp` mutation directly

## Authors

- [Nathan Jeanbourquin](https://github.com/Nathan3942) / [Ilia Chpakovski](https://github.com/iliachpak) — 42

## License

Project built as part of the 42 curriculum. Educational use.

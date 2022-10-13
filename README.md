# pipex

## The Project

This project aims to reproduce shell pipe in C.

## Usage

Clone this repository and run `make`, and make the executable file `pipex`.

This program is used as follows :
```bash
./pipex infile cmd1 cmd2 outfile
```

It must take 4 arguments:
- infile and outfile are file names.
- cmd1 and cmd2 are shell commands with their parameters.

It must behave the same as the shell command below:
```bash
< infile cmd1 | cmd2 > outfile
```

### examples
```bash
./pipe infile "ls -l" "wc -l" outfile
```
should behave like: 
```bash
< infile ls -l | wc -l > outfile
```

I also have done the bonus part, so the program `pipex` made by the command `make bonus` handles multiple pipes and here document.
For example, This
```bash
./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile
```
behave like:
```bash
< infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile
```

Support << and >> when the first parameter is "here_doc", so this
```bash
./pipex here_doc LIMITER cmd cmd1 file
```

should behave like:
```bash
cmd << LIMITER | cmd1 >> file
```

> **Warning**
> I didn't manage multiple here document, so the command
> ```bash
> ./pipex here_doc LIMITER1 LIMITER2 cmd cmd1 file
> ```
> should behave like:
> ```
> LIMITER2 << LIMITER1 | cmd | cmd1 >> file
> ```

### misc
- I can use `close`, `open`, `read`, `write`, `malloc`, `free`, `perror`,
  `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`,
  `wait` and `waitpid`
  and other normal libc functions are forbidden.
- In no way can it quit abruptly.
  (segmentation fault, bus error, double free, etc).
- All heap allocated memory space must be properly freed when necessary.
  No leaks will be tolerated.
- Global variables are forbidden.
- All code must conform to the [42 Norm](https://github.com/42School/norminette).

## Approach

Before starting this project, I read
[this tutorial page](https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901).
The basic structure is similar to this; create a child process by `fork`,
properly adjust file descriptor by `dup2()` and `pipe()`, and execute the command
in the child process by `execve`.

In addition, I noted two points that were not clearly stated on page above.
1. I modified the parent process and check if the last command quit abruptly, and if so, detect the signal and output an appropriate error message.
2. `access()` searches the current directory for match files, so if there is an executable file (say `a.out`) in the current directory and `access()` isn't used properly, the command
    ```bash
    ./pipex infile "ls -l" "a.out" outfile
    ```
    interpreted as
    ```bash
    < infile ls -l | ./a.out > outfile
    ```
    not as
    ```bash
    < infile ls -l | a.out > outfile
    ```
    I carefully check this behavior.

## Author

[Twitter](https://twitter.com/t76_1205)

## Licence

[MIT](./LICENSE)
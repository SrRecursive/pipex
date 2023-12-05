# pipex

## Description

Pipex is a function that replicates the behaviour of a pipe in a Unix system.

This should behave the same way:

```Shell
./pipex infile cat "wc -l" outfile
```

```Shell
< infile cat | wc -l > outfile
```

### Bonus

It supports multiple pipes and the use of ***<<*** and ***>>*** when the first parameter is ***here_doc***

This should behave the same way:

```Shell
./pipex infile cat "wc -l" "grep hello" outfile
```

```Shell
< infile cat | wc -l | grep hello > outfile
```

This should also behave the same way:

```Shell
./pipex heredoc a cat "grep hello" "wc -l" outfile
```

```Shell
cat << a | grep hello | wc -l > outfile
```

## Allowed Functions

- [open()](https://linux.die.net/man/3/open)
- [close()](https://linux.die.net/man/3/close)
- [write()](https://man7.org/linux/man-pages/man2/write.2.html)
- [read()](https://linux.die.net/man/3/read)
- [malloc()](https://www.man7.org/linux/man-pages/man3/malloc.3.html)
- [free()](https://linux.die.net/man/3/free)
- [perror()](https://linux.die.net/man/3/perror)
- [access()](https://linux.die.net/man/3/access)
- [dup2()](https://linux.die.net/man/3/dup2)
- [execve()](https://linux.die.net/man/3/execve)
- [exit()](https://linux.die.net/man/3/exit)
- [fork()](https://linux.die.net/man/3/fork)
- [pipe()](https://linux.die.net/man/3/pipe)
- [waitpid()](https://linux.die.net/man/3/waitpid)
- Any function I coded from scratch.

## Progress

If you want to check my progress as a student in 42 Málaga check out my [main repository](https://github.com/SrVariable/42Malaga)!

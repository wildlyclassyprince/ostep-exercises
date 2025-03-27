# Overview

The C programs in this directory are from the chapter titled "_Interude: Process API_".

***
To run the `calling_fork.c` program:
```bash
gcc calling_fork.c -o fork_program
./fork_program
```

The output should show the non-deterministic behavior of `fork` by likely completing the parent process before the child is done.

***
To run the `calling_fork_with_wait.c` program:
```bash
gcc calling_fork_with_wait.c -o fork_with_wait
./fork_with_wait
```
`wait` allows us to control how the process runs, in this case we will have a more deterministic outcome where the child process with run and complete, then the parent with complete after.

We are able to control the behavior of the parent process by telling it to wait, with the `wait` system call, for the child process to start and complete.

***
To run the `calling_fork_with_wait_and_exec.c` program:
```bash
gcc calling_fork_with_wait_and_exec.c -o fork_wait_exec
./fork_wait_exec
```

Here, we use the `exec` system call, which similar to the `fork` system call, allows us to start a process. However, unlike the `fork` system call which only runs child processes that are identical to the parent, `exec` allows use to run other programs that are not necessarily similar to the parent process.

In our case, we run the `wc` program to count the number of words in our `calling_fork.c` file.

An interesting aside, the decoupling of `fork` and `exec` is the idea behind redirecting output and pipes in the UNIX system. For example, if we wanted to run a command like `wc input_file > results.txt`, we would use the `exec` call to open the `results.txt` file as a child process, then run the `wc` command as the parent after waiting for the child to complete.

***
To run the `all_the_calls_with_redirection.c` program:
```bash
gcc all_the_calls_with_redirection.c -o all_with_redirect
./all_with_redict
```
All the programs above will print something to `STDOUT` but this program will instead redirect output to a file without printing anything to the terminal window.

***
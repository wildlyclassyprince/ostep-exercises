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

## Homework Notes

To compile and run any of the homework scripts:
```bash
gcc homework_q1.c -o hw1
./hw1
```

### Question 1

- `fork()` create a complete copy of the process, including all its memory (think of it like a snapshot of all program memory and gives it to the child process), i.e., the parent and child get their own versions of all variables - this includes `x`

### Question 2

- `strdup()` creates strings by never free them - this is not a good practice.
- Using the `wait()` system call causes the program to be deterministic rather than concurrent.
- In order to get interleaved results, we had to use 1000 in `usleep(1000)` to ensure a longer delay. Result should be something like this:

```bash
parent-1
child-1
child-2
parent-2
child-3
parent-3
child-4
parent-4
child-5
parent-5
```

- `sprintf` can format strings that we can then write to standard output, however, it allows for buffer overflows, especially when dealing with variable-length strings.
- `snprintf` is a safer alternative because it prevents buffer overflows by specifying the exact formatted string without including unused buffer space or the null terminator (which is not typically included in file I/O operations).
- Summary:
>- We also now know that the file descriptor, `fd` is inherited during the forking operation.
>- The output shows non-deterministic execution.  There are no gurantees on the interleaving pattern since it depends on the OS scheduler deciding on how to allocate CPU time between the two processes. Using `wait` would make it deterministic if we needed to.


### Question 3

- There are several ways of "waiting" without using the `wait()` system call:
>- Using pipes for synchronisation: `pipe()`
>- using signals: `signal()`, `kill()`, `pause()`
>- using a shared file semaphore: `access()`, `unlink()`
>- using a sleep (not a good idea): `sleep()`

### Question 4

- The `exec` family of system calls has a lot of variants to handle different programming requirements and scenarios:
>- `execl`: uses a list of arguments
>- `execv`: uses an array of arguments
>- `execlp`: uses a list of arguments, searches PATH
>- `execvp`: uses an array of arguments, searches PATH
>- `execle`: uses a list of arguments and allows environment specification
>- `execve`: uses an array of arguments and allows environment specification
- We also discovered that the name of each function describes it's behavior:
>- `l`(list): arguments are passed as a list of parameters
>- `v`(vector): arguments are passed as an array (vector)
>- `p`(path): system searches for the program in the PATH environment variable
>- `e`(environment): allows specification of the environment for the new program

### Question 5

- `fork()` returns:
>- the child process ID (PID) in the parent process.
>- 0 in the child process.
>- a negative value if the fork failed
- The `wait()` system call is quite interesting:
>- when called by the parent process, it blocks it until any one of the child processes terminates.
>- when a child terminates, it returns the PID of that terminated child.
>- if the parent has no children, or all it's children have already been waited for, it returns -1 and sets `errno` to `ECHILD`.
>- if it is interrupted by a signal, it returns -1 and sets `errno` to `EINTR`.
- __NB__: the child process should never call the `wait()` system call unless it has forked its own children.

### Question 6

- `waitpid()` is often more useful over `wait()` because it gives control over which child to wait for and whether to block, making it ideal for a wider range of applications.

### Question 7

### Question 8
***
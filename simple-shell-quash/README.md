## Quash: A Simple Shell Implementation

## Project Overview
Quash (Quick Shell) is a simple command-line shell that replicates the core functionalities 
of popular UNIX shells like sh, bash, csh, and tcsh. The goal of this project is to develop 
a deeper understanding of command-line interfaces (CLI), process forking, background processes,
 signal handling, I/O redirection, and piping.

## This shell was implemented in multiple tasks to incrementally add features:
Task 1: Basic built-in commands (cd, pwd, echo, env, setenv, exit).
Task 2: Process creation and forking for external commands.
Task 3: Background process support using &.
Task 4: Signal handling for Ctrl-C to avoid quitting the shell.
Task 5: Timer to kill long-running foreground processes after 10 seconds.
Task 6: I/O redirection with > and < and piping with |.

## How to Use the Shell

Compile the shell:
make

Run the shell:
./shell

Exit the shell by typing:
exit

## Built-in Commands
cd <directory>: Change the current working directory.
pwd: Print the current working directory.
echo <message>: Print a message or environment variables (e.g., echo $PATH).
env: Display the list of environment variables.
setenv <VAR> <VALUE>: Set a new environment variable.
exit: Exit the shell.

## Features Implemented
1. Task 1: Built-in Commands
We implemented essential built-in commands such as cd, pwd, echo, env, setenv, and exit.
We tokenized user input to separate commands from arguments.
2. Task 2: Process Forking
We used fork() to create child processes and execvp() to execute external commands.
We handled errors for non-existent commands.
3. Task 3: Background Processes
We implemented background process support using &.
The shell returns immediately to the prompt when a command is run in the background.
4. Task 4: Signal Handling
We implemented SIGINT (Ctrl-C) handling to prevent the shell from exiting.
The shell catches Ctrl-C and returns to the prompt without quitting.
5. Task 5: Killing Long-Running Processes
We used alarm() to set a 10-second timeout for foreground processes.
If a process exceeds the timeout, it is killed using kill().
6. Task 6: I/O Redirection and Piping
I/O Redirection:
> '>' redirects command output to a file.
Example:
cat shell.c > output.txt

> '<' redirects a file as input to a command.
Example:
more < shell.c

Piping:
> Pipes the output of one command as input to another.
Example:
cat testData | grep "this"

## Design Choices
Tokenization: We used strtok() to split user input into tokens.
Built-in Command Handling: we Checked if the user command was built-in before attempting to fork a new process.
Signal Handling: We implemented custom signal handlers for SIGINT and SIGALRM.
Redirection & Piping: We used dup2() to redirect input/output streams and pipe() for piping between processes.

## Known Limitations and Future Improvements
Command History: Currently, the shell does not store or display command history.
Job Control: Commands like fg, bg, and jobs are not implemented.
Enhanced Piping: Multiple piping (cmd1 | cmd2 | cmd3) could be added.

## Team Members
Manoj Nath Yogi
Siddhartha Gautam

## Acknowledgements and References
1. Codio Instruction
2. Professor Legan Burge Lecture
3. Textbook: Used Chapter 3 as a reference for basic shell concepts.
4. Labs: Referenced Lab 3 - Part 1 for process forking and signal handling.
5. Linux Manual Pages: Used for understanding fork(), execvp(), signal(), dup2(), and wait() system calls.

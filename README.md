# Linux-shell Project

This project involves implementing a custom shell prompt that mimics the functionality of Linux cortices. The cortex program will repeat a set of steps to process user commands until the user enters the "exit" command.

## Steps to Implement

The implemented cortex should follow these steps:

1. Display a prompt to the user, indicating that the cortex is ready to accept commands. For example:

2. Read a command from the terminal entered by the user.

3. Create an appropriate number of processes to execute each command. The cortex should handle multiple commands entered on a single line, separated by semicolons (;).

4. Queue the processes to execute each task/command entered by the user.

5. Wait for the newly created processes to terminate before proceeding.

6. Once a process is terminated, the cortex will read and execute the next command entered by the user.

7. Repeat steps 2-6 until the user enters the "exit" command.

## Supported Features

The cortex should be capable of executing the following:

1. Execution of basic commands:
   - Displaying a prompt.
   - Running a shell program.
   - Creating a new process to execute a program.
   - Reading commands entered by the user.

2. Commands with parameters:
   - The cortex should be able to execute commands with parameters passed.
  
3. Commands with redirection of standard input and output:
    - The cortex should support commands where standard input and output are redirected to/from files. Both overwrite (`>`) and append (`>>`) modes should be supported.

4. Commands with pipes:
    - The cortex should be able to execute commands with at least one pipe.
(Bonus: Support for multiple piping, e.g., `ps ax | grep /bin/bash | wc -l > out.txt`).

## Conclusion

By implementing this cortex, you will have a custom program that can handle user commands, execute programs, support parameters, handle input/output redirection, and handle commands with pipes. It provides a basic shell-like interface similar to Linux cortices while also offering some additional functionalities.





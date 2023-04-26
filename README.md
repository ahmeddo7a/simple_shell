Simple Shell Project
Description

This project is a simple version of the linux shell made for Holberton School. This simple_shell is a command line interpreter, created using the C programming Language and it can do many functionalities that a real shell does.
Requirements

Simple_shell is designed to run in the Ubuntu 14.04 and to be compiled using the GNU compiler collection v. gcc 4.8.4.
Usage

To use this simple shell, follow these steps:

    Open a terminal window.
    Navigate to the directory where the simple shell files are located.
    Compile the files using the command: gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
    Run the shell using the command: ./hsh
    You can now enter commands and see the results in the terminal window.

Features

This simple shell is capable of performing the following functions:

    Display a prompt and wait for the user to type a command.
    Handle command lines with arguments.
    Handle the PATH environment variable.
    Handle the exit command.
    Handle the env command.
    Handle the Ctrl+C signal.

Examples

Here are some examples of how to use the simple shell:

    ls -l - lists the files in the current directory.
    echo "Hello, World!" - prints the message "Hello, World!" to the terminal.
    pwd - prints the current working directory to the terminal.
    exit - exits the simple shell.
    env - prints the environment variables to the terminal.

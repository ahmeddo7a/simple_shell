#Simple Shell Project
##Description
This project is a simple version of the linux shell made for Holberton School. This simple_shell is a command line interpreter, created using the C programming Language and it can do many functionalities that a real shell does.
Requirements
Simple_shell is designed to run in the Ubuntu 14.04 and to be compiled using the GNU compiler collection v. gcc 4.8.4.
Usage
To use this simple shell, follow these steps:
1. Open a terminal window.
2. Navigate to the directory where the simple shell files are located.
3. Compile the files using the command: gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
4. Run the shell using the command: ./hsh
5. You can now enter commands and see the results in the terminal window.
##Features
This simple shell is capable of performing the following functions:
* Display a prompt and wait for the user to type a command.
* Handle command lines with arguments.
* Handle the PATH environment variable.
* Handle the exit command.
* Handle the env command.
* Handle the Ctrl+C signal.
##Examples
Here are some examples of how to use the simple shell:
* ls -l - lists the files in the current directory.
* echo "Hello, World!" - prints the message "Hello, World!" to the terminal.
* pwd - prints the current working directory to the terminal.
* exit - exits the simple shell.
* env - prints the environment variables to the terminal.
##Installation
* Clone this repository: git clone "https://github.com/ahmeddo7a/simple_shell"
* Change directories into the repository: cd simple_shell
* Compile: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
* Run the shell in interactive mode or non-interactive mode.
* ./hsh
## Authers
* Ahmed Mamdouh
* Sherif Safwat

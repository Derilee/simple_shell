# 0x16. C - Simple Shell
Full Project Information
https://intranet.alxswe.com/projects/235

<p align="center">
 <img src= "https://s3.eu-west-3.amazonaws.com/hbtn.intranet.project.files/holbertonschool-low_level_programming/235/shell.jpeg" width="400" height="400" />

# Simple Shell :robot:

## Introduction
This repository contains the files to simulate a basic Unix Shell with its respective commands.

## Description
This repository contains the executable files to simulate a simple Unix shell with its respective basic commands as well as some advanced ones developed by the contributors. Each functionality of the file will be commented, as well as each line of the function where its compression is not so clear to the naked eye. <br>
In the Shell you can interact both in interactive and non-interactive modes.


Tasks
Task 0. Betty would be proud
Task 1. Simple shell 0.1(100% done): Write a UNIX command line interpreter.
Task 2. Simple shell 0.2(100% done): Handle command lines with arguments.
Task 3. Simple shell 0.3(100% done): Handle the PATH. Fork must not be called if the command doesn’t exist.
Task 4. Simple shell 0.4(100% done): Implement the exit built-in, that exits the shell
                          Usage: exit. You don’t have to handle any argument to the built-in exit.
Task 5. Simple shell 1.0(100% done): Implement the env built-in, that prints the current environment.
Task 6. Simple shell 0.1.1(100% done): Write your own getline function
                            Use a buffer to read many chars at once and call the least possible the read system call
                            You will need to use static variables
                            You are not allowed to use getline. You don’t have to: be able to move the cursor.
Task 7. Simple shell 0.2.1(100% done): You are not allowed to use strtok.
Task 8. Simple shell 0.4.1(100% done): handle arguments for the built-in exit
                            Usage: exit status, where status is an integer used to exit the shell.
Task 9. setenv, unsetenv(71.43% done): Implement the setenv and unsetenv builtin commands
                           In setenv, Initialize a new environment variable, or modify an existing one
                           Command syntax: setenv VARIABLE VALUE. Should print something on stderr on failure
                           In unsetenv, Remove an environment variable
                           Command syntax: unsetenv VARIABLE. Should print something on stderr on failure.
Task 10. cd(88.89% done): Implement the builtin command cd: Changes the current directory of the process.
                          Command syntax: cd [DIRECTORY]
                          If no argument is given to cd the command must be interpreted like cd $HOME
                          You have to handle the command cd -
                          You have to update the environment variable PWD when you change directory.
Task 11. ;(100% done): Handle the commands separator ;
Task 12. && and ||(100% done): Handle the && and || shell logical operators.
Task 13. alias(50% done): Implement the alias builtin command
                          Usage: alias [name[='value'] ...]
                          alias: Prints a list of all aliases, one per line, in the form name='value'
                          alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
                          alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias,
                          replaces its value with value.
Task 14. Variables(100% done): Handle variables replacement
                               Handle the $? variable. Handle the $$ variable.
Task 15. Comments(20% done): Handle comments (#)
Task 16. File as input(75% done): Your shell can take a file as a command line argument
                                  Usage: simple_shell [filename]
                                  The file contains all the commands that your shell should run before exiting
                                  The file should contain one command per line
                                  In this mode, the shell should not print a prompt and should not read from stdin


## Requeriments

* Programs and functions will be compiled with ```gcc``` using the flags ```-Wall``` ```-Werror``` ```-Wextra``` ```-pedantic``` and ```-std=gnu89```
* All files should end with a new line
* No more than 5 functions per file
* Operating System: [Ubuntu 20.04 LTS](http://releases.ubuntu.com/20.04/)
* Compiler: [GCC](https://gcc.gnu.org)
* Authorized functions and system calls:
  * ```access``` (```man 2 access```)
  * ```chdir``` (```man 2 chdir```)
  * ```close``` (```man 2 close```)
  * ```closedir``` (```man 3 closedir```)
  * ```execve``` (```man 2 execve```)
  * ```exit``` (```man 3 exit```)
  * ```fork``` (```man 2 fork```)
  * ```free``` (```man 3 free```)
  * ```stat``` (```__xstat```)(```man 2 stat```)
  * ```lstat``` (```__lxstat```)(```man 2 lstat```)
  * ```fstat``` (```__fxstat```)(```man 2 fstat```)
  * ```getcwd``` (```man 3 getcwd```)
  * ```getline``` (```man 3 getline```)
  * ```kill``` (```man 2 kill```)
  * ```malloc``` (```man 3 malloc```)
  * ```open``` (```man 2 open```)
  * ```opendir``` (```man 3 opendir```)
  * ```perror``` (```man 3 perror```)
  * ```read``` (```man 2 read```)
  * ```readdir``` (```man 3 readdir```)
  * ```signal``` (```man 2 signal```)
  * ```strtok``` (```man 3 strtok```)
  * ```wait``` (```man 2 wait```)
  * ```waitpid``` (```man 2 waitpid```)
  * ```wait3``` (```man 2 wait3```)
  * ```wait4``` (```man 2 wait4```)
  * ```write``` (```man 2 write```)
  * ```_exit``` (```man 2 _exit```)
  * ```isatty``` (```man 3 isatty```)
  * ```fflush``` (```man 3 fflush```)


## Usage :computer:
All the files are to be compiled on an Ubuntu 20.04 LTS machine with:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89
```

Once compiled, to start the program, run:
```./hsh```
  
To exit the program, run:
```$ exit```



## Modes
The user can have the experience in an interactive and non-interactive way.

To use the **interactive mode** use . Immediately the user will see a warning $ indicating that our shell is ready to read the command.
And to exit the program, use the word  ```exit```.
Example:
```
$ ./hsh
$ /bin/ls
```

En **non-interactive mode** the user will enter command line arguments,In non-interactive mode, you can pipe commands to the program using echo or cat:

Example:
```
$ echo "/bin/ls" | ./hsh
$ cat file_name | ./hsh
```

## Bugs
No known bugs.


## Authors
* **Samuel Victor** [Github](https://github.com/Derilee)

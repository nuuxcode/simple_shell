gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Task 1 :

Display a prompt and wait for the user to type a command. A command line always ends with a new line.
The prompt is displayed again each time a command has been executed.
The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
The command lines are made only of one word. No arguments will be passed to programs.
If an executable cannot be found, print an error message and display the prompt again.
Handle errors.
You have to handle the “end of file” condition (Ctrl+D)
execve will be the core part of your Shell, don’t forget to pass the environ to it…

You don’t have to:

use the PATH
implement built-ins
handle special characters : ", ', `, \, *, &, #
be able to move the cursor
handle commands with arguments

-error handling using errno
- way to handle input command through echo "/bin/ls" | ./shell

task 2 :

+Handle command lines with arguments
use strtok with getline and send it to execve

task 3 :

Handle the PATH
fork must not be called if the command doesn’t exist

- if the the file doesnt exist in current directory, loop through path directory and check if it exsit there
- before fork, make sure the the path valid

-before fork, check if u have neccesary permission and file exist before doing execve


task 4 :
Implement the exit built-in, that exits the shell
Usage: exit
You don’t have to handle any argument to the built-in exit

- before the fork, check the command entered if it built in command
(handle built in command)

task 5:

Implement the env built-in, that prints the current environment
- get global environtmt with environ or env and print it

builtin command : env, exit

###########################################

task 6:
Write your own getline function
Use a buffer to read many chars at once and call the least possible the read system call
You will need to use static variables
You are not allowed to use getline

You don’t have to:
be able to move the cursor

-make our own getline

task 7:
You are not allowed to use strtok
- make ower _strtook

task 8:
handle arguments for the built-in exit
Usage: exit status, where status is an integer used to exit the shell

- add status argement, maybe it gonna be something liek exit(55)
    - exit handler

task 9:
Implement the setenv and unsetenv builtin commands

	setenv
		Initialize a new environment variable, or modify an existing one
		Command syntax: setenv VARIABLE VALUE
		Should print something on stderr on failure
	unsetenv
		Remove an environment variable
		Command syntax: unsetenv VARIABLE
		Should print something on stderr on failure

edit environ and add to it ore delete from it

task10:
Implement the builtin command cd:

Changes the current directory of the process.
Command syntax: cd [DIRECTORY]
If no argument is given to cd the command must be interpreted like cd $HOME
You have to handle the command cd -
You have to update the environment variable PWD when you change directory
man chdir, man getcwd

handle CD :
update and use OLDPWD , PWD
cd -
cd (cd $HOME)
man chdir, man getcwd

task11:
Handle the commands separator ;

- check if any seperator in user input
	if ;
		use strtok to seprate the commands
			then each command should be execve in seprate fork
			and synchronise using wait 1 by 1
			main wait for all of them to finish

task12:
Handle the && and || shell logical operators

&& : read exit status or execve error and only go to the next command if the previous one is succes
|| : exec 1by1 and stop when 1 of them is succes

task13:
Implement the alias builtin command
Usage: alias [name[='value'] ...]
alias: Prints a list of all aliases, one per line, in the form name='value'
alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

temporary array of aliases, that we gonna check the moment user enter a command
	- built in
	- aliases
	- then search for file in current directly or PATH

task14:
Handle variables replacement
Handle the $? variable
Handle the $$ variable

-get exsit status of any fork, and update it to global variable $?
-our main terminal, should update the global variable $$ with getpid
echo $$

task15:
Handle comments (#)
use strtok to check
#
&&
||
;
echo $$; echo $$ # ls -la
echo $$|| echo $$ && echo $$ # ls -la

task16:
Usage: simple_shell [filename]
Your shell can take a file as a command line argument
The file contains all the commands that your shell should run before exiting
The file should contain one command per line
In this mode, the shell should not print a prompt and should not read from stdin

-check for argument if it a file or valid command
	- hadnle the file that have commands in each line



built in commands :
exit
env
setenv
unsetenv
cd
seperator ; && ||

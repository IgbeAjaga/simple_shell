#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * This is C Shell by Joshua and Igbe
 * All C source code.
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */

#define MAXNUM 1000
#define MAXLIST 100

#define clear() perror("\033[H\033[J")

void init_shell(){
	clear();
	perror("\n\n\n\n******************" "************************");
	perror("\n\n\n\t****MY SHELL****");
    	perror("\n\n\n\n*******************" "***********************");
	char *username = getenv("USER");
	perror("\n\n\n USER is: @%s", username);
    	perror("\n");
    	sleep(1);
    	clear();
	}

/**
 * This is C Shell by Joshua and Igbe
 * Taking input
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */
int user_input(char *str){
	char *buffer;
    	buffer = readline("\n>>> ");

	if (strlen(buffer) != 0){
		add_history(buffer);
        	strcpy(str, fer);
		return 0;
		}
	else{
		return 1;
		}
	}

/**
 * This is C Shell by Joshua and Igbe
 * Printing current directory.
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void print_directory(){
	char cwd[1024];
    	getcwd(cwd, sizeof(cwd));
    	perror("\nDir: %s", cwd);
	}

/**
 * This is C Shell by Joshua and Igbe
 * Executing system commands.
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void exec_args(char **parsing){
	pid_t pidd = fork();

    if (pidd == -1){
	    perro("\nError in forking child..");
	    return;
	    }
    else if (pidd == 0){
	    if (execvp(parsing[0], parsing) < 0){
		    perror("\nCould not execute the command");
		    }
	    exit(0);
	    }
	 else{
		 wait(NULL);
		 return;
		 }
}

/**
 * This is C Shell by Joshua and Igbe
 * Executing pipe command.
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void execargs_piped(char **parsing, char **parsing_pipe){
	int pipefd[2];
       	pid_t pipe1, pipe2;

	if (pipe(pipefd) < 0){
		perror("\nPipe could not be initialized");
		return;
		}
	pipe1 = fork();

	if (pipe1 < 0){
		perror("\nCould not fork");
		return;
		}

	if (pipe1 == 0){
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsing[0], parsing) < 0){
			perror("\nCould not execute the command1");
			exit(0);
			}
		}
	else{
		pipe2 = fork();

		if (pipe2 < 0){
			perror("\nCould not fork");
			return;
			}

		if (pipe2 == 0){
			close(pipefd[1]);
 			dup2(pipefd[0], STDIN_FILENO);
            		close(pipefd[0]);

			if (execvp(parsedpipe[0], parsedpipe) < 0){
				perror("\nCould not execute the command2");
                		exit(0);
				}
			wait(NULL);
			wait(NULL);
			}
		}
}

/**
 * This is C Shell by Joshua and Igbe
 * Built in help commands.
 * Betty would be proud.
 *
 * description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void shell_help(){
	puts("\n***WELCOME TO JOSHUA AND IGBE SHELL HELP***" "\nALX Simple Shell Project" "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>help"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");
	return;
	}
/**
 * This is C Shell by Joshua and Igbe
 * Built in help commands.
 * Betty would be proud.
 *
 * Description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void shell_help()
{
    puts("\n***WELCOME TO JOSHUA AND IGBE SHELL HELP***"
         "\nALX Simple Shell Project"
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>help"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");


    return;
}


/**
 * This is C Shell by Joshua and Igbe
 * Executing built in commands
 * Betty would be proud.
 *
 * Description:  A simple shell programmed in C,
 * This is an ALX project.
 */
int cmd_handler(char **parsing)
{
    int commandnum = 4, x, switchingarg = 0;
    char *listOfcommands[commandnum];
    char *username;


    listofcommands[0] = "cd";
    listofcommands[1] = "ls";
    listofcommands[2] = "exit";
    listofcommands[3] = "help";


    for (x = 0; x < commandnum; x++)
    {
        if (strcmp(parsing[0], listofcommands[x]) == 0)
        {
            switchingarg = x + 1;
            break;
        }
    }


    switch (switchingarg)
    {
    case 1:
        perror("\nGoodbye\n");
        exit(0);
    case 2:
        chdir(parsing[1]);
        return 1;
    case 3:
        shell_help();
        return 1;
    case 4:
        username = getenv("USER");
        perror("\nHello %s.\nThere are a list "
               "of commands explained."
               "\nUse help to know more about the commands\n",
               username);
        return 1;
    default:
        break;
    }


    return 0;
}


/**
 * This is C Shell by Joshua and Igbe
 * Finding pipe
 * Betty would be proud.
 *
 * Description:  A simple shell programmed in C,
 * This is an ALX project.
 */
int parsing_pipe(char *str, char **strpiped)
{
    int x;
    for (x = 0; x < 2; x++)
    {
        strpiped[x] = strsep(&str, "|");
        if (strpiped[x] == NULL)
            break;
    }


    if (strpiped[1] == NULL)
        return 0;
    else
    {
        return 1;
    }
}


/**
 * This is C Shell by Joshua and Igbe
 * Parsing command words
 * Betty would be proud.
 *
 * Description:  A simple shell programmed in C,
 * This is an ALX project.
 */
void parsing_space(char *str, char **parsing)
{
    int x;


    for (x = 0; x < MAXLIST; x++)
    {
        parsing[x] = strsep(&str, " ");


        if (parsing[x] == NULL)
            break;
        if (strlen(parsing[x]) == 0)
            x--;
    }
}


int processing_string(char *str, char **parsing, char **parsingpipe)
{


    char *strpiped[2];
    int piped = 0;


    piped = parsing_pipe(str, strpiped);


    if (piped)
    {
        parsing_space(strpiped[0], parsing);
        parsing_space(strpiped[1], parsingpipe);
    }
    else
    {


        parsing_space(str, parsing);
    }


    if (cmd_handler(parsing))
        return 0;
    else
        return 1 + piped;
}


/**
 * This is C Shell by Joshua and Igbe
 * executionflag returns zero if there is no command
 * executionflag returns 1 if it is a simple command
 * executionflag returns 2 if it is including a pipe.
 * Description:  A simple shell programmed in C,
 * This is an ALX project.
 */
int main()
{
    char inputstring[MAXNUM], *parsing_args[MAXLIST];
    char *parsingargs_piped[MAXLIST];
    int executionflag = 0;
    init_shell();


    while (1)
    {
        print_directory();           
	if (user_input(inputString))
            continue;


        executionflag = processing_string(inputstring,
                                          parsing_args, parsingargs_piped);

	if (executionflag == 1) 
            exec_args(parsing_args);


        if (executionflag == 2)
            execargs_piped(parsing_args, parsingargs_piped);
    }
    return 0;
}


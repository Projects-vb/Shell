#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int execcmd(char *cmd)
{
    char *token = NULL;
    char *cmd_cpy = NULL;
    char *delim = " \n";

    cmd_cpy = strdup(cmd);
    
    token = strtok(cmd, delim);
    int argc = 0;   //counts no of args
    while (token)
    {
        token = strtok(NULL, delim);
        argc++;
    }

    char **argv = NULL; //creating array of pointers to string passed to the new programas as its command-line arguments
    argv = malloc(sizeof(char *) * argc);  

    token = strtok(cmd_cpy, delim);
    int i = 0;
    while (token)
    {
        argv[i] = token;
        token = strtok(NULL, delim);
        i++;
    }
    argv[i] = NULL;

    //printing array to be passed
    // i=0;
    // while (argv[i])
    // {
    //     printf("i = %d", i);
    //     printf("; %s\n", argv[i]);
    //     i++;
    // }

    pid_t pid;
    pid = fork(); //creating a child process
    if (pid == 0)
    {
        // Inside child process
        int rt = execvp(argv[0], argv);  // replcaing the stack, ds of the child process with the passed args from argv, argv[0] wil; contain the command name.
        if (rt == -1) // if the execvp fails
        {
            perror("Execv returned error\n");
        }       
    }
    else
    {
        wait(NULL); //waiting for child to finish else it will be orphana and parent will return before child.
        printf("Back to Main\n");

    }
    return 0;

}

int main(void)
{
    char *cmd = NULL;
    size_t n = 0;

    while (true)  //loop through the prompt
    {
        printf("$$MyShell$$:");
        getline(&cmd, &n, stdin);
        execcmd(cmd);
    }
    
}
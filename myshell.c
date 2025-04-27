#include <linux/limits.h>
#include <stdio.h>
#include "LineParser.h"
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#define USER_INPUT_MAX 2048


// 0 = non-blocking, no wait
// 1 = blocking(default), wait
void execute(cmdLine* pCmdLine){
    int res;
    int pid;
    int sig;
    
    if(strcmp(pCmdLine->arguments[0], "cd") == 0){ // cd command: accepts one more arg(path)
        if(pCmdLine->argCount == 2){
            chdir(pCmdLine->arguments[1]);
        }
        else{
            fprintf(stderr, "Error: cd command accepts exactly 1 argument <path>.\n");
        }
    }
    else if(strcmp(pCmdLine->arguments[0], "stop") == 0 || strcmp(pCmdLine->arguments[0], "wake") == 0 || strcmp(pCmdLine->arguments[0], "term") == 0){ // signal: accepts one more arg(pid)
        char error_flag = 1;
        if(pCmdLine->argCount != 2){
            fprintf(stderr, "Error: %s command accepts exactly one argument <pid>.", pCmdLine->arguments[0]);
            error_flag = 0;
        }
        if(error_flag){ // if no error encountered, implement logic here
            if(strcmp(pCmdLine->arguments[0], "stop") == 0){
                sig = SIGSTOP;
            }
            else if(strcmp(pCmdLine->arguments[0], "wake") == 0){
                sig = SIGCONT;
            }
            else{
                sig = SIGINT;
            }
            if (kill(atoi(pCmdLine->arguments[1]), sig) != 0){
                perror("kill failed.");
            }
        }
    }
    else{
        pid = fork();
        if (pid == 0){ // child proccess
            if (pCmdLine->inputRedirect){ // if input-redirect is not null
                close(STDIN_FILENO);
                open(pCmdLine->inputRedirect, O_RDONLY);
            }
            if (pCmdLine->outputRedirect){
                close(STDOUT_FILENO);
                open(pCmdLine->outputRedirect, O_CREAT | O_WRONLY  | O_TRUNC, 0644);
            }
            res = execvp(pCmdLine->arguments[0] ,pCmdLine->arguments);
            if(res == -1)
                perror("Error during execv");
        }   
        else{ // main proccess, assuming fork didnt fail
            if(pCmdLine->blocking){ // if blocking, wait else keep going
                waitpid(0, NULL, 0);
            }
        }
    }

}

int main(int argc, char** argv){
    char line_buffer[USER_INPUT_MAX];
    char working_dir[PATH_MAX];
    
    while(1){
        getcwd(working_dir, sizeof(working_dir));
        printf("%s$ ", working_dir);
        fgets(line_buffer, sizeof(line_buffer), stdin);

        cmdLine* cmd_line = parseCmdLines(line_buffer);

            execute(cmd_line);

        freeCmdLines(cmd_line);
    }

}

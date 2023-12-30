#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 80

/* setup() reads in the next command line string stored in inputBuffer,
separating it into distinct tokens using whitespace as delimiters.
setup() modifies the args parameter so that it holds pointers to the
null-terminated strings that are the tokens in the most recent user
command line as well as a NULL pointer, indicating the end of the
argument list, which comes after the string pointers that have been
assigned to args. */

void setup(char inputBuffer[], char *args[], int *background) {
 int j, /* index for accessing inputBuffer */
 first,  /* index position of the first (or next) command parameter */
 insert,     /* index position of the next args[] parameter insertion */
 size; /* the amount of characters in the command line */
    
    insert = 0;

    /* read user input and initialize first position */
    size = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    first = -1;
    
    /* if ctrl+d is entered, terminate the command stream */
    if (size == 0)
        exit(0);
    /* if the input is invalid, terminate the stream and print an error code */
        if (size < 0){
        perror("Error: invalid command");
        exit(-1);          
    }

    /* loop through each element in the inputBuffer array */
    for (j = 0; j < size; j++) {
        switch (inputBuffer[j]){
            case ' ':
            case '\t' :   
            
    /* loop that creates the pointer */
                if(first != -1){
args[insert] = &inputBuffer[first];    
                    insert++;
                }
    /* insert a null character to create a string of C,
    then define the last character to be checked */
                inputBuffer[j] = '\0'; 
                first = -1;
                break;
            case '\n':   
            
    /* loop to examine arguments and increment insertions */
                if (first != -1){
                    args[insert] = &inputBuffer[first];
            insert++;
                }
                inputBuffer[j] = '\0';
    /* intialize to NULL to cut off the argument stream */
                args[insert] = NULL; 
                break;

            case '&':
                *background = 1;
                inputBuffer[j] = '\0';
                break;
            default :    
                if (first == -1)
                    first = j;
        }
    }
    /* contingency for MAX input lines (if it surpasses 80) */
    args[insert] = NULL; 
}

int main(void) {
    char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
    int background;	  /* equals 1 if a command is followed by '&' */
    char *args[MAX_LINE+1]; /* command line arguments */

    while (1) {
        background = 0;
        printf(" COMMAND->\n");
        setup(inputBuffer,args,&background); /* get next command */
        int condition; /* the current condition of execvp */
        pid_t child; /* child process id */
        /* The steps are:
     (1) fork a child process using fork() */
                child = fork();
/* The fork will fail if the child process returns a negative value */
         if(child < 0){ 
            printf("Error: Fork process failed. \n");
    /* else, move on to step (2) the child process will invoke execvp() */    
         }else if(child==0){
            condition = execvp(args[0],args);
            /* print an error if the condition is not 0 */
            if(condition !=0){
                printf("%s: command does not exist. \n", args[0]);
            }

	}else{ /* (3) if background == 0, the parent will wait */
            if(background == 0)
                waitpid(child,&background,0);
}
    }return 0;
}

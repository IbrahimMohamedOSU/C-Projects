#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define MAX_LINE 80
#define HISTORY_SIZE 10
#define HISTORY_FILE "mohamed511.history"

char history[HISTORY_SIZE][MAX_LINE];
int historyCount = 0;

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

	// Retry if interrupted system call error occurs
    while (size == -1 && errno == EINTR) {
        size = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    }
    
    // Handle error if read() still fails
    if (size < 0) {
        perror("Error: invalid command");
        exit(-1);
    }
    
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


/* Signal handler for SIGINT */
void handle_SIGINT() {
    printf("\nHistory of the last 10 commands:\n");
    
    int i;
    int start = (historyCount > HISTORY_SIZE) ? (historyCount - HISTORY_SIZE) : 0;
    for (i = start; i < historyCount; i++) {
        printf("%d: %s\n", i + 1, history[i % HISTORY_SIZE]);
    }
    
    printf("Enter 'r x' to execute the command starting with the letter x.\n");
    printf("Enter 'r' to execute the most recent command.\n");
    printf("COMMAND-> ");
    fflush(stdout);
}

// Function to load command history from the history file
void load_history() {
    FILE* file = fopen(HISTORY_FILE, "r");
    if (file != NULL) {
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), file) != NULL) {
            line[strcspn(line, "\n")] = '\0'; // Remove the newline character
            strcpy(history[historyCount % HISTORY_SIZE], line);
            historyCount++;
        }
        fclose(file);
    }
}

// Function to save command history to the history file
void save_history() {
    FILE* file = fopen(HISTORY_FILE, "w");
    if (file != NULL) {
        int start = (historyCount > HISTORY_SIZE) ? (historyCount - HISTORY_SIZE) : 0;
        int i;
        for (i = start; i < historyCount; i++) {
            fprintf(file, "%s\n", history[i % HISTORY_SIZE]);
        }
        fclose(file);
    }
}


int main(void) {
    char inputBuffer[MAX_LINE];
    int background;
    char *args[MAX_LINE + 1];
    
    /* Set up the signal handler for SIGINT */
    struct sigaction handler;
    handler.sa_handler = handle_SIGINT;
    sigaction(SIGINT, &handler, NULL);
    
    while (1) {
        background = 0;
        printf("COMMAND-> ");
        fflush(stdout);
        setup(inputBuffer, args, &background);
	int condition;
        
        // Handle r command
if (args[0] != NULL && args[0][0] == 'r') {
            if (historyCount > 0) {
                if (args[0][1] == '\0') {
                    // Execute most recent command
                    strcpy(inputBuffer, history[(historyCount - 1) % HISTORY_SIZE]);
                } else {
                    // Execute command starting with the specified letter
                    char letter = args[0][1];
                    int i;
                    for (i = historyCount - 1; i >= 0; i--) {
                        if (history[i % HISTORY_SIZE][0] == letter) {
                            strcpy(inputBuffer, history[i % HISTORY_SIZE]);
                            break;
                        }
                    }
                    if (i < 0) {
                        printf("Error: No command found starting with '%c'.\n", letter);
                        continue;
                    }
                }
                printf("Executing: %s\n", inputBuffer);
                fflush(stdout);
            } else {
                printf("Error: No commands in history.\n");
                continue;
            }
        }

        // Store command in history
        strcpy(history[historyCount % HISTORY_SIZE], inputBuffer);
        historyCount++;

	// Remove newline character from inputBuffer
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';
        
        pid_t child;
	child = fork();
        if (child < 0) {
            printf("Error: Fork process failed.\n");
        } else if (child == 0) {
            condition = execvp(args[0], args);
            if (condition != 0) {
                printf("%s: command does not exist.\n", args[0]);
            }
            exit(0);
        } else {
            if (background == 0) {
                waitpid(child, &background, 0);
            }
        }
        
        // Save command history to the history file before exiting
        save_history();
    }
    
    return 0;
}

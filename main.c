#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#define DEBUG
#define MAX_TOKENS 10
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char ** tokenize(char * input, const char * delim, size_t maxTokens);

char ** tokenize(char * input, const char * delim, size_t maxTokens){
    
    // Allocate the proper memory for our tokens
    char ** tokens = malloc(sizeof(char *) * maxTokens);  
    if (tokens == NULL){
        puts("Memory allocation for tokenize function failed.");
    }
    
    size_t tokenCount = 0;
    char * input_dupe = strdup(input); // Duplicate input because strtok modifies the string
    
    if (input_dupe == NULL) {
        free(tokens);
        puts("Failed to duplicate the input. Was it null?");
        return NULL;
    }
    
    // Start by getting the fist token
    char * token = strtok(input, delim);

    while(token != NULL && tokenCount < maxTokens){
        tokens[tokenCount] = token;
    }
}
int main(void) {
    char *input = NULL;
    size_t input_length = 0;

    int debug_exit = 0;

    while (debug_exit == 0 && (input == NULL || strcmp(input, "exit\n") != 0)) {
        char cwd[PATH_MAX]; 
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            // Get the home directory
            char *home = getenv("HOME");

            // Check if cwd starts with home path
            if (home != NULL && strncmp(cwd, home, strlen(home)) == 0) {
                printf("~%s: ", cwd + strlen(home));  // Replace home with '~'
            } else {
                printf("%s: ", cwd);  // Print cwd as is
            }

            // Get user input
            if (getline(&input, &input_length, stdin) == -1) {
                perror("getline() error");
                break;
            }

            // printf("You entered: %s", input);
            tokenize(input, " ", MAX_TOKENS);


            #ifdef DEBUG
            debug_exit = 1;  // Set flag to exit loop in debug mode
            #endif
        } else {
            perror("getcwd() error");  // Print error message if getcwd fails
            break;
        }
    }

    free(input);  // Free allocated memory for input
    return 0;
}

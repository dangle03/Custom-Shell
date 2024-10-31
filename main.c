#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
// #define DEBUG
#define MAX_TOKENS 10
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char ** tokenize(char * input, const char * delim, size_t maxTokens);
int handle_command_if_else(const char* cmd);

int handle_command_if_else(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        printf("\nShowing help menu\n");
        return 0;
    } else if (strcmp(cmd, "ls") == 0) {
        printf("\nListing items\n");
        return 0;
    } else if (strcmp(cmd, "exit") == 0) {
        printf("\nExiting program\n");
        return 1;
    } else {
        printf("\nUnknown command: %s\n", cmd);
        return 0;
    }
}

char **tokenize(char *input, const char *delim, size_t maxTokens) {
    // Allocate the array of token pointers
    char **tokens = malloc(sizeof(char *) * maxTokens);
    
    if (tokens == NULL) {
        puts("Memory allocation for tokens array failed.");
        return NULL;
    }

    size_t tokenCount = 0;
    char *input_dupe = strdup(input); // Duplicate input because strtok modifies the string

    if (input_dupe == NULL) {
        free(tokens);
        puts("Failed to duplicate the input.");
        return NULL;
    }

    // Start by getting the first token
    char *token = strtok(input_dupe, delim);

    while (token != NULL && tokenCount < maxTokens) {
        tokens[tokenCount] = strdup(token); // Duplicate each token for safe storage
        if (tokens[tokenCount] == NULL) {
            puts("Memory allocation failure for a token.");
            for (size_t i = 0; i < tokenCount; i++) {
                free(tokens[i]);
            }
            free(tokens);
            free(input_dupe);
            return NULL;
        }
        tokenCount++;
        token = strtok(NULL, delim);
    }

    // Null-terminate the tokens array to mark the end of tokens
    if (tokenCount < maxTokens) {
        tokens[tokenCount] = NULL;
    }

    free(input_dupe); // Free the duplicated input string
    return tokens;
}


// Main //
int main(void) {
    char *input = NULL;
    size_t input_length = 0;

    int debug_exit = 0;

    while (debug_exit == 0) {
        input = NULL;
        input_length = 0;
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
            // Remove newline character if it exists
            input[strcspn(input, "\n")] = 0;

            printf("You entered: %s", input);
            char ** tokenizedInput = tokenize(input, " ", MAX_TOKENS);
            if (tokenizedInput != NULL && tokenizedInput[0] != NULL) {
                debug_exit = handle_command_if_else(tokenizedInput[0]);
                printf("Debug exit status: %d\n", debug_exit);

                // Free each token and the token array
                for (size_t i = 0; i < MAX_TOKENS && tokenizedInput[i] != NULL; i++) {
                    free(tokenizedInput[i]);
                }
                free(tokenizedInput);
            } else puts("Null pointer.");

            


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
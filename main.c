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
#include <dirent.h>

char ** tokenize(char * input, const char * delim, const size_t maxTokens);
int handle_command_if_else(char ** args);
void changeDirectory(char ** args);
void showHelp();
void listDirectory(const char * path);
void showHelp(){
    printf("List of options that are currently supported\nls - Prints out contents of current directory\ncd dir - changes the current directory to 'dir'\nexit - exits the program\n");
}

void listDirectory(const char * path){
    DIR * dir = opendir(path);
    if (dir == NULL){
        perror("opendir");
        return;
    }
    struct dirent * entry; // pointer to each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')  // Skip hidden files
            continue;
        printf("%s\n", entry->d_name);  // Print file name
    }

    closedir(dir);
}
void changeDirectory(char ** args) {
    if (args[1] == NULL) {
        // No argument provided, go to the home directory
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME environment variable not set\n");
        } else if (chdir(home) != 0) {
            perror("cd");
        }
    } else {
        // Attempt to change to the specified directory
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

int handle_command_if_else(char** args) {
    if (strcmp(args[0], "help") == 0) {
        printf("Showing help menu\n");
        showHelp();
        return 0;
    } else if (strcmp(args[0], "ls") == 0) {
        printf("Listing items\n");
        const char *path = args[1] ? args[1] : ".";  // Use current directory if no argument
        listDirectory(path);
        return 0;
    } else if (strcmp(args[0], "cd") == 0){
        changeDirectory(args);
    }
     else if (strcmp(args[0], "exit") == 0) {
        printf("Exiting program\n");
        return 1;
    } else {
        printf("\nUnknown command: %s\n", args[0]);
        showHelp();
        return 0;
    }
}

char ** tokenize(char * input, const char * delim, const size_t maxTokens) {
    // Allocate the array of token pointers
    char ** tokens = malloc(sizeof(char *) * maxTokens);
    
    if (tokens == NULL) {
        puts("Memory allocation for tokens array failed.");
        return NULL;
    }

    size_t tokenCount = 0;
    char * input_dupe = strdup(input); // Duplicate input because strtok modifies the string

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
            char * home = getenv("HOME");

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

            // printf("You entered: %s\n", input);
            char ** tokenizedInput = tokenize(input, " ", MAX_TOKENS);
            if (tokenizedInput != NULL && tokenizedInput[0] != NULL) {
                debug_exit = handle_command_if_else(tokenizedInput);
                // printf("Debug exit status: %d\n", debug_exit);

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

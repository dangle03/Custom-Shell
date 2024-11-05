// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command_handler.h"
#include "directory_operations.h"
#include "utility.h"

// char ** tokenize(char * input, const char * delim, const size_t maxTokens);

// void changeDirectory(char ** args);
// void listDirectory(const char * path);
// void touch(char * fileName);




// int handle_command_if_else(char** args) {
//     if (strcmp(args[0], "help") == 0) {
//         printf("Showing help menu\n");
//         showHelp();
//         return 0;
//     } else if (strcmp(args[0], "ls") == 0) {
//         printf("Listing items\n");
//         const char *path = args[1] ? args[1] : ".";  // Use current directory if no argument
//         listDirectory(path);
//         return 0;
//     } else if (strcmp(args[0], "cd") == 0){
//         changeDirectory(args);
//         return 0;
//     } else if (strcmp(args[0], "echo") == 0){
//         if (args[1] != NULL) {
//             int i = 1;
//             while (args[i] != NULL) {
//                 printf("%s ", args[i]);  // Print each argument
//                 i++;
//             }
//         }
//         puts("");
//         return 0;
//     } else if (strcmp(args[0], "exit") == 0) {
//         printf("Exiting program\n");
//         return 1;
//     } else if (strcmp(args[0], "touch") == 0){
//         if (args[1] != NULL) {
//             touch(args[1]);  // Call touchFile with the specified filename
//             return 0;
//         } else {
//             printf("touch: missing file operand\n");
//         }
//     } else {
//         printf("\nUnknown command: %s\n", args[0]);
//         showHelp();
//         return 0;
//     }
// }




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

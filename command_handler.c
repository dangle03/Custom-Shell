// command_handler.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_handler.h"
#include "directory_operations.h"
#include "utility.h"

void showHelp(){
    printf("List of options that are currently supported\nls - Prints out contents of current directory\ncd dir - changes the current directory to 'dir'\nexit - exits the program\n");
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
        return 0;
    } else if (strcmp(args[0], "echo") == 0){
        if (args[1] != NULL) {
            int i = 1;
            while (args[i] != NULL) {
                printf("%s ", args[i]);  // Print each argument
                i++;
            }
        } 
        puts("");
        return 0;
    } else if (strcmp(args[0], "exit") == 0) {
        printf("Exiting program\n");
        return 1;
    } else if (strcmp(args[0], "grep") == 0) {
        char ** test = grep(args);
        //if (args[1] != NULL && args[2] != NULL) {
            // args[1] is the search string, args[2] is the file path
            //char **results = grep(args);
            //if (results != NULL) {
                //for (size_t i = 0; results[i] != NULL; i++) {
                    //printf("%s", results[i]);  // Print each matched line
                    //free(results[i]);         // Free the line after use
                //}
                //free(results);  // Free the array itself
            //}
        //} else {
           // printf("Usage: grep <search_string> <file_path>\n");
        //}
        return 0;
    } else if (strcmp(args[0], "touch") == 0){
        if (args[1] != NULL) {
            touch(args[1]);  // Call touchFile with the specified filename
            return 0;
        } else {
            printf("touch: missing file operand\n");
        }
    } else {
        printf("\nUnknown command: %s\n", args[0]);
        showHelp();
        return 0;
    }
}

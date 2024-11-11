// directory_operations.c
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include "directory_operations.h"

// For reference //
/*
args[0] will be the command
args[1-n] will be additional arguments provided by the user
*/
void touch(char * fileName){
    int fd = open(fileName, O_CREAT | O_RDWR, 0666); // Create the file if it doesn't exist, edit it if it does
    if (fd == -1) {
        perror("touch");
        return;
    }
    close(fd);

    // Update the modification time
    if (utime(fileName, NULL) == -1) {
        perror("utime");
        return;
    }
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

char ** grep(char ** args){
    int numFound = 0;
    char **returnStrings = malloc(sizeof(char*));
    
    FILE * file = fopen(args[2], "r"); // In this case args[1] will be the pattern, args[2] will be the filename
    if (file == NULL){
        perror("error opening file (does it exist?)");
    }
    char buffer[256];
    printf("Contents of the file:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); // Print each line
    
    return returnStrings;
    }
}

void cat(char ** args){
    FILE * file = fopen(args[1], "r"); // In this case args[1] will be the filename
    if (file == NULL){
        perror("error opening file (does it exist?)");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer); // Print each line
    }
    printf("\n");
    fclose(file);
}

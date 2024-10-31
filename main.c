#ifndef PATH_MAX
#define PATH_MAX 4096
#endif
#define DEBUG
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
int main(void){
    char * input = "null";
    size_t input_length = 0;
    while (input != "exit"){
        char cwd[PATH_MAX]; 
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s:" , cwd); // Display cwd
            getline(&input, &input_length, stdin);
            printf("You entered: %s", input);
            #ifdef DEBUG
            input = "exit";
            #endif
        } else {
            perror("getcwd() error");  // Print error message if getcwd fails
            #ifdef DEBUG
            input = "exit";
            #endif
    }

    }
}
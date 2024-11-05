// utility.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

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
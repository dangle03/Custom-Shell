#ifndef UTILITY_H
#define UTILITY_H
#define MAX_TOKENS 10
#define PATH_MAX 4096
char ** tokenize(char * input, const char * delim, const size_t maxTokens);
#endif
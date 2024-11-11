#ifndef DIRECTORY_OPERATIONS_H
#define DIRECTORY_OPERATIONS_H
void changeDirectory(char ** args);
void listDirectory(const char * path);
void touch(char * fileName);
char **grep(char ** args);
void cat(char ** args);
#endif
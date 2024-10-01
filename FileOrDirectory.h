#include <iostream>
#include <sys/stat.h>

#define FILE 0
#define DIRECTORY 1
#define SYMBOLIC_LINK 2

bool isDirectory(const char *path);

bool isFile(const char *path);

int return_type(const char *path);
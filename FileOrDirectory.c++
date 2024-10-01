#include <iostream>
#include <sys/stat.h>

#include "FileOrDirectory.h"

bool isDirectory(const char *path) {
  struct stat pathStat;
  if (stat(path, &pathStat) == 0) {
    return S_ISDIR(pathStat.st_mode); // Return true if it's a directory
  }
  return false;
}

bool isFile(const char *path) {
  struct stat pathStat;
  if (stat(path, &pathStat) == 0) {
    return S_ISREG(pathStat.st_mode); // Return true if it's a regular file
  }
  return false;
}

int return_type(const char *path) {
  if (isDirectory(path))  return DIRECTORY;
  else if (isFile(path))  return FILE;
  else                    return SYMBOLIC_LINK;
}
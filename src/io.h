#ifndef IO_H
#define IO_H

#include "stack.h"

// Read from stdin into stack
int read_input(Stack *s);

// Read numbers from file into stack
int read_file(const char *filename, Stack *s);

// Save stack to file
void save_stack(const char *filename, Stack *s);

// Main IO logic
int IO(int argc, char *argv[]);

#endif

#ifndef IO_H
#define IO_H

void save_array(const char *filename, const int *arr, int n);

int read_input(int **arr);

int read_file(const char *filename,  int **arr);

int IO(int argc, char **argv);

#endif

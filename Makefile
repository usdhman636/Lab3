CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = src/main.o src/stack.o src/sort.o src/timer.o src/io.o

program: $(OBJ)
	$(CC) $(CFLAGS)  -o run $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o run

run: program
	./run

#for windows cmd
#run.exe: main.c stack.c sort.c io.c timer.c stack.h sort.h io.h timer.h
  #gcc -Wall -Wextra -std=c99 -o run.exe main.c stack.c sort.c io.c timer.c

#clean:
  #del /Q *.o *.exe

#run: run.exe
  #run.exe

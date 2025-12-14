CC = gcc
CFLAGS = -Wall -Wextra -O2

OBJ = src/main.o src/stack.o src/sort.o src/timer.o src/io.o

program: $(OBJ)
	$(CC) $(CFLAGS) -o program $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o program

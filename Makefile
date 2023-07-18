CFLAGS = -std=c17 -Wall -O3

Patcher: Patch.o Patcher.o
	$(CC) $^ -o $@

%.o: %.c
	$(CC) -c $^ -o $@

clean:
	rm --force *.o *.gch Patcher

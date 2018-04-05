CC=gcc
FLAGS=-Wall -Wextra -std=c11 -O2
DEPS=tree.h linked_list.h
OBJ=main.o linked_list.o tree.o

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c $<

main: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

.PHONY : clean
clean:
	rm -rf *.o main


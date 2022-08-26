CC = gcc
prog = hash

all: $(prog)

$(prog): *.o
	$(CC) *.o -o $(prog) -lm

*.o : *.c 
	$(CC) -c *.c -lm

clean: 
	rm -f *.o

purge: clean
	rm -f $(prog)


	

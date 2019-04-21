.PHONY: all clean

CC=gcc


all: main
	 

main: main.c
	$(CC) main.c -lpthread -lm -o Main
	
clean:
	rm -rf *.o 

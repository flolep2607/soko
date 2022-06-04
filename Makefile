OBJS	= compiled/io.o
SOURCE	= librairies/io.c
HEADER	= 
OUT	= compiled/io
CC	 = gcc
FLAGS	 = -Wall -g -fsanitize=address,undefined -std=c99
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o io $(LFLAGS)

test:
	clear
	$(CC) $(FLAGS) tests/file_test.c -o compiled/file_test.o
	./compiled/file_test.o


compiled/io.o: librairies/io.c
	$(CC) $(FLAGS) librairies/io.c -o compiled/io.o

clean:
	rm -f *.o **.o $(OBJS) $(OUT)

run: $(OUT)
	./compiled/io

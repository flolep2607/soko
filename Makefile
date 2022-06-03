OBJS	= compiled/io.o
SOURCE	= librairies/io.c
HEADER	= 
OUT	= compiled/io
CC	 = gcc
FLAGS	 = -Wall -g -fsanitize=address
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o io $(LFLAGS)

compiled/io.o: librairies/io.c
	$(CC) $(FLAGS) librairies/io.c -std=c99 -o compiled/io.o

clean:
	rm -f *.o **.o $(OBJS) $(OUT)

run: $(OUT)
	./compiled/io

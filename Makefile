OBJS	= compiled/io.o
SOURCE	= librairies/io.c
HEADER	= 
OUT	= compiled/io
CC	 = gcc
FLAGS	 = -Wall -Wextra -g3 -std=c99 
LDFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer 
# apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0
# -fsanitize=address,undefined 
# --leak-check=full
all: $(OBJS)
	$(CC) -g $(OBJS) -o io $(LFLAGS)

test:
	clear
	$(CC) $(FLAGS) tests/file_test.c -o compiled/file_test.o
	./compiled/file_test.o
	$(CC) $(FLAGS) tests/movement_test.c -o compiled/movement_test.o
	./compiled/movement_test.o

affich_mask:
	clear
	$(CC) $(FLAGS) librairies/game.c -o compiled/game.o $(LDFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=test.log ./compiled/game.o
	grep -E '^( |\{|\})' test.log >> supressions.txt

affich_leak:
	clear
	$(CC) $(FLAGS) librairies/game.c -o compiled/game.o $(LDFLAGS)
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes --suppressions=supressions.txt ./compiled/game.o

affich:
	clear
	$(CC) $(FLAGS) -fsanitize=address,undefined librairies/affichage.c librairies/file.c librairies/movement.c librairies/pile.c librairies/game.c -o compiled/game.o $(LDFLAGS)
	./compiled/game.o



compiled/io.o: librairies/io.c
	$(CC) $(FLAGS) librairies/io.c -o compiled/io.o

clean:
	rm -f *.o **.o $(OBJS) $(OUT)

run: $(OUT)
	./compiled/io

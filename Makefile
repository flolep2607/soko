OBJS	= compiled/io.o
SOURCE	= src/io.c
HEADER	= 
OUT	= compiled/io
CC	 = gcc
FLAGS	 = -ggdb3 -std=c99 
LIBS = src/file.c src/movement.c src/pile.c
LIBS_SDL = src/affichage.c src/animation.c src/file.c src/movement.c src/pile.c
LDFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer -lSDL2_ttf 
VALGRIND_PARAMS = --show-mismatched-frees=yes --trace-children=yes --track-fds=no --error-limit=no --errors-for-leak-kinds=definite --show-leak-kinds=definite --leak-check=full --track-origins=yes

# -fsanitize=address,undefined 
# -Wall -Wextra 
# --suppressions=supressions.txt 
all: game

test:
	clear
	$(CC) $(FLAGS) -fsanitize=address,undefined src/pile.c src/file.c tests/file_test.c -o compiled/file_test.o
	./compiled/file_test.o
	$(CC) $(FLAGS) -fsanitize=address,undefined src/affichage.c src/pile.c src/file.c src/movement.c src/animation.c tests/movement_test.c -o compiled/movement_test.o $(LDFLAGS)
	./compiled/movement_test.o
	$(CC) $(FLAGS) -fsanitize=address,undefined src/pile.c src/file.c tests/save_test.c -o compiled/save_test.o
	./compiled/save_test.o

install:
	sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-ttf-2.0-0 libsdl2-ttf-dev

affich_mask:
	clear
	$(CC) $(FLAGS) $(LIBS) src/game.c -o compiled/game.o $(LDFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all --gen-suppressions=all --log-file=test.log ./compiled/game.o
	grep -E '^( |\{|\})' test.log >> supressions.txt

affich_leak:
	clear
	$(CC) $(FLAGS) $(LIBS) src/game.c -o compiled/game_leak.o $(LDFLAGS)
	valgrind $(VALGRIND_PARAMS)  --log-file=out.log ./compiled/game_leak.o

gamesdl: clean
	clear
	$(CC) $(FLAGS) $(LIBS_SDL) src/game.c -o game $(LDFLAGS)
	./game

game: clean
	clear
	$(CC) $(FLAGS) $(LIBS) src/game_no_sdl.c -o game_no_sdl
	./game_no_sdl


compiled/io.o: src/io.c
	$(CC) $(FLAGS) src/io.c -o compiled/io.o

clean:
	rm -f *.o compiled/* game

run: game
	./game

doc: Doxyfile
	doxygen Doxyfile
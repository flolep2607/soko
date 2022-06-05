OBJS	= compiled/io.o
SOURCE	= librairies/io.c
HEADER	= 
OUT	= compiled/io
CC	 = gcc
FLAGS	 = -Wall -Wextra -Werror -g3 -std=c99 -m32
SDL_FLAGS	 = -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -pthread -lpulse -pthread -lX11 -lXext -lXcursor -lXinerama -lXi -lXfixes -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt
# -fsanitize=address,undefined 
# $(sdl2-config --cflags --libs)
all: $(OBJS)
	$(CC) -g $(OBJS) -o io $(LFLAGS)

test:
	clear
	$(CC) $(FLAGS) tests/file_test.c -o compiled/file_test.o
	./compiled/file_test.o
	$(CC) $(FLAGS) tests/movement_test.c -o compiled/movement_test.o
	./compiled/movement_test.o

affich:
	clear
	$(CC) $(SDL_FLAGS) $(FLAGS) librairies/affichage.c -o compiled/affichage.o 
	./compiled/affichage.o
	valgrind --leak-check=full --gen-suppressions=all --log-file=test.log 


compiled/io.o: librairies/io.c
	$(CC) $(FLAGS) librairies/io.c -o compiled/io.o

clean:
	rm -f *.o **.o $(OBJS) $(OUT)

run: $(OUT)
	./compiled/io

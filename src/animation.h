#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
#ifndef AFFICHAGE_H
#include "affichage.h"
#define AFFICHAGE_H
#endif
#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif
void animate_box_moving(runtime_t* runtime,unsigned char direction,unsigned int index_start,unsigned int index_end);
#include <stdbool.h>
#include <stdlib.h>
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
//? directions
#define HAUT 1
#define BAS 2
#define DROITE 3
#define GAUCHE 4
#define xy2x(X, Y,LONG)  (X + Y * LONG)
#define x2x(X, LONG)  (X%LONG)
#define x2y(X, LONG)  (X/LONG)
void x2xy(unsigned int X,unsigned int LONG,unsigned int *x,unsigned int *y);
void find_human(level_t *level);
bool is_on_map(level_t *level,unsigned int x,unsigned int y);
bool is_on_map2(unsigned largeur,unsigned int hauteur,unsigned int x,unsigned int y);
void move_direction(char direction,unsigned int *x_after,unsigned int *y_after);
bool is_finish(gll_t *map);
void move_object(gll_t *map,unsigned int pos1,unsigned int pos2,unsigned char object_value);
bool move_human(level_t *level,char direction,bool save);
bool go_back(level_t *level);
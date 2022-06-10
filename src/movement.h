#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#ifndef RUNTIME_H
#include "runtime.h"
#define RUNTIME_H
#endif
#ifndef STRUCTURES_H
#include "structures.h"
#define STRUCTURES_H
#endif
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif

// associe a chacun des mouvements une valeur correspondant à la sortie du clavier quand on appuie sur la touche correspondant au mouvement

#define xy2x(X, Y,LONG)  (X + Y * LONG)
#define x2x(X, LONG)  (X%LONG)
#define x2y(X, LONG)  (X/LONG)
void x2xy(unsigned int X,unsigned int LONG,unsigned int *x,unsigned int *y);
bool is_on_map(level_t *level,unsigned int x,unsigned int y);
bool is_on_map2(unsigned largeur,unsigned int hauteur,unsigned int x,unsigned int y);
unsigned int move_direction(char direction,unsigned int index,unsigned int largeur);
bool is_finish(liste_double *map);
void move_object(liste_double *map,unsigned int pos1,unsigned int pos2);//,unsigned char object_value
bool move_human(level_t *level,char direction,bool save,bool move_box,runtime_t* runtime);
bool go_back(level_t *level,runtime_t* runtim);
void go_all_back(level_t *level,runtime_t* runtime);
bool path_finding(level_t *level,unsigned int x,unsigned int y,runtime_t* runtime,void (*refresh_screen)(runtime_t*,int,int));
bool check_empty(liste_double* map,unsigned int index);
void possible_move(level_t *level,bool *array);
char random_from_array(bool array[4]);
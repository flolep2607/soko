#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif
gll_t *read_map(FILE *flux_entree,unsigned int largeur_max);
unsigned int largeur(FILE *flux_entree);
bool remove_useless(FILE *flux_entree);
int read_one_level(FILE *flux_entree,level_t *level);
gll_t *read_file(const char *file_name);
bool save_game(gll_t *levels,unsigned int current_level,const char *file_name);
#include <stdbool.h>
#ifndef STRUCTURES_H
#include "structures.h"
#define STRUCTURES_H
#endif
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
void read_map(FILE *flux_entree,unsigned int largeur_max,liste_double *map);
unsigned int largeur(FILE *flux_entree);
bool remove_useless(FILE *flux_entree);
int read_one_level(FILE *flux_entree,level_t *level);
liste_double *read_file(const char *file_name);
bool save_game(liste_double *levels,const char *file_name);
bool read_save(const char *file_name, liste_double* levels);
void save_coups(liste_double* coups,int level_number);
void find_human(level_t *level);
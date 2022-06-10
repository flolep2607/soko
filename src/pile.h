#include <stdlib.h>
#include <stdbool.h>
#ifndef STRUCTURES_H
#include "structures.h"
#define STRUCTURES_H
#endif
//? case  => case_t
//? map   => liste_double
//? coup  => coup_t
//? coups => liste_double
//? level => level_t
//? levels=> liste_double


liste_double *liste_double_init();
level_t *level_init();
case_t* create_case(unsigned char bloc, bool cible);
coup_t* create_coup (unsigned char direction, bool pousse);


void *liste_double_get(liste_double *, unsigned int);


void liste_double_ajout_en_tete(liste_double *, void *);
void liste_double_ajout_en_queue(liste_double *, void * data);


void liste_double_vider(liste_double *liste,bool levels);
void *liste_double_supprimer_tete(liste_double *);
void *liste_double_depiler_tete(liste_double *);


void liste_double_destroy(liste_double *);
void level_destroy(level_t* level);
void levels_destroy(liste_double *levels);

int somme_poussees(liste_double *coups);
#include <stdbool.h>
#ifndef LISTE_CHAINE
#include "liste_chaine.c"
#define LISTE_CHAINE
#endif

typedef struct Case
{
    unsigned char bloc; // 0->air 1->wall 2->box 3->body
    bool cible;
} case_t;

typedef struct Level
{
    node_t Map;
    node_t coups;
    bool resolue;
    int numero_lvl;
    unsigned int largeur;
    unsigned int hauteur;
} level_t;

typedef struct Levels
{
    node_t level;
} levels_t;

case_t* create_case (int bloc, bool cible){
    case_t* case_=(case_t *) malloc(sizeof(case_t));
    case_->bloc = bloc;
    case_->cible = cible;
    return case_;
}

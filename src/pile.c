#include <stdbool.h>
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif

/**
 * @brief Creer une structure case_t en prenant le contenu de la structure en parametre.
 * 
 * @param bloc 
 * @param cible 
 * @return case_t* 
 */
case_t* create_case (unsigned char bloc, bool cible){
    case_t* case_=(case_t *) malloc(sizeof(case_t));
    case_->bloc = bloc;
    case_->cible = cible;
    return case_;
}

/**
 * @brief Initialise une structure level_t. Met les valeurs des donnees de type entiers a 0 et celle de type booleen a false.
 *Initialise la valeur des liste chainee contenue dans level_t en faisant appel a 2 fonctions d'initialisation.
 * 
 * @return level_t* 
 */
level_t *level_init() 
{
  level_t *level = (level_t *) malloc(sizeof(level_t));
  level->solved = false;
  level->lvl_number = 0;
  level->largeur = 0;
  level->hauteur = 0;
  level->map=liste_double_init();
  level->coups=liste_double_init();
  level->index=0;
  return level;
}

/**
 * @brief Creer une structure coup_t en prenant le contenu de la structure en parametre
 * 
 * @param direction 
 * @param pousse (pousse ou non => Bool)
 * @return coup_t* 
 */
coup_t* create_coup (unsigned char direction, bool pousse){
    coup_t* coup_=(coup_t *) malloc(sizeof(case_t));
    coup_->direction = direction;
    coup_->pousse = pousse;
    return coup_;
}

static liste_double_node_t *liste_double_trouver_node(liste_double *, unsigned int);
static liste_double_node_t *liste_double_init_node(void *);



/**
 * @brief intialise une liste chainee, met la valeur de ses donnees a 0 et intialise le pointeur de tete et de queue a NULL
 * 
 * @return liste_double* 
 */
liste_double *liste_double_init() 
{
  liste_double *liste = (liste_double *) malloc(sizeof(liste_double));
  liste->size = 0;
  liste->first = NULL;
  liste->last = NULL;
  return liste;
}


 /**
  * @brief initialise un maillon d'une liste chainee avec une valeur passee en parametre
  * 
  * @param data 
  * @return liste_double_node_t* 
  */
static liste_double_node_t *liste_double_init_node(void *data) 
{
  liste_double_node_t *node = (liste_double_node_t *) malloc(sizeof(liste_double_node_t));
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}


/**
 * @brief Trouve un maillon d'une liste chainee dont la position est passee en parametre. 
 * 
 * @param liste 
 * @param pos 
 * @return liste_double_node_t* (un pointeur vers le maillon dont la position est passee en parametre)
 */
static liste_double_node_t *liste_double_trouver_node(liste_double *liste,unsigned int pos) 
{
  if(pos > liste->size){
    return NULL; 
  }
  liste_double_node_t *current_node;
  unsigned int position_en_cours;
  bool reverse; 
  /* decide where to start iterating from (font or back of the liste) */
  if(pos > ((liste->size-1) / 2)) {
    reverse  = true;
    position_en_cours  = liste->size - 1;
    current_node = liste->last;
  } else {
    reverse  = false;
    position_en_cours  = 0;
    current_node = liste->first;
  }  
  
  while(current_node != NULL) {
    if(position_en_cours == pos){
      break;
    }
    current_node = (reverse ? (current_node->prev) : (current_node->next));
    position_en_cours  = (reverse ? (position_en_cours-1) : (position_en_cours+1));
  }
  return current_node;
}

/**
  * @brief recupere la valeur d'un element d'une liste a une certaine position passee en parametre
  * 
  * @param liste 
  * @param pos 
  * @return void* du type de la donnee contenu dans la liste chainee
  */
void *liste_double_get(liste_double *liste, unsigned int pos) 
{
  liste_double_node_t *node = liste_double_trouver_node(liste, pos);
  if(node != NULL){
    return node->data;
  }else{
    return NULL;
  }
}

 /**
  * @brief Empile un maillon au debut d'une liste chainee en prenant en parametre la donnee du maillon a ajouter
  * 
  * @param liste 
  * @param data 
  */
void liste_double_ajout_en_tete(liste_double *liste, void *data) 
{
  liste_double_node_t *newNode = liste_double_init_node(data); 
  /* if liste is empty */
  if(liste->size == 0) {
    liste->last = newNode;
  } else {
    /* if there is at least one element */
    liste->first->prev = newNode;
    newNode->next = liste->first;
  }
  liste->first = newNode;
  liste->size++;
}



/**
 * @brief Empile un maillon a la fin d'une liste chainee en prenant en parametre la valeur contenu dans le maillon qu'il faut ajouter
 * 
 * @param liste 
 * @param data 
 */
void liste_double_ajout_en_queue(liste_double *liste, void *data) 
{
  /* initialize new node */
  liste_double_node_t *newNode = liste_double_init_node(data);
  /* if liste is empty */
  if(liste->size == 0) {
    liste->first = newNode;
  } else {
    /* if there is at least one element */
    liste->last->next = newNode;
    newNode->prev = liste->last;
  }
  liste->last = newNode;
  liste->size++;
}



/**
 * @brief Supprime une maillon d'une liste chainee dont la position est passee en parametre
 * 
 * @param liste liste double
 * @return void* 
 */
void *liste_double_supprimer_tete(liste_double *liste) 
{
  liste_double_node_t *current_node = liste_double_trouver_node(liste, 0);
  void *data = NULL;

  if(current_node == NULL){
    return NULL;
  }
  data = current_node->data;

  if(current_node->prev == NULL) {
    liste->first = current_node->next;
  }else{
    current_node->prev->next = current_node->next;
  }
  if(current_node->next == NULL){
    liste->last = current_node->prev; 
  } else{
    current_node->next->prev = current_node->prev;
  }
  liste->size--;
  free(current_node);
  return data;
}



 /**
  * @brief Depile l'element en tete de la liste chainee et nous retourne sa valeur
  * 
  * @param liste 
  * @return void* (du type de la donnee contenu dans les maillons de la liste)
  */
void* liste_double_depiler_tete(liste_double *liste) 
{
  if(!liste){
    return NULL;
  }
  liste_double_node_t *node = liste->first;
  if(node == NULL){
    return NULL;
  }
  void *data = node->data;
  if(liste_double_supprimer_tete(liste) == NULL){
    return NULL;
  }
  return data;
}



 /**
  * @brief Supprime une liste et libere l'espace memoire de chacun des maillons de la liste
  * 
  * @param liste 
  */
void liste_double_destroy(liste_double *liste) 
{
  liste_double_node_t *current_node = liste->first;
  liste_double_node_t *nextNode;
  
  while(current_node != NULL) {
    nextNode = current_node->next;
    free(current_node->data);
    free(current_node);
    current_node = nextNode;  
  }
  free(liste);
}

/**
 * @brief Vide une liste chainee. Parcours la liste et libere chacun des maillons pour les supprimer
 * 
 * @param liste 
 * @param levels si c'est une liste de levels
 */
void liste_double_vider(liste_double *liste,bool levels) 
{
  liste_double_node_t *current_node = liste->first;
  liste_double_node_t *nextNode;
  
  while(current_node != NULL) {
    nextNode = current_node->next;
    if(levels){
      level_destroy(current_node->data);
    }else{
      free(current_node->data);
    }
    free(current_node);
    current_node = nextNode;  
  }

  liste->first = NULL;
  liste->last = NULL;
  liste->size = 0;
}

/**
 * @brief Supprime une structure niveau en liberant les liste chainees contenu dans la structure (map et coups) puis libere l'espace alloue a la structure
 * 
 * @param level 
 */
void level_destroy(level_t* level){
  if(level->map!=NULL){
    liste_double_destroy(level->map);
  }
  if(level->coups!=NULL){
    liste_double_destroy(level->coups);
  }
  free(level);
}

/**
 * @brief Supprime une liste chainee de level en appliquant en boucle la fonction "level_destroy" tant que le pointeur 
 * vers le level suivant est different de NULL
 * 
 * @param levels 
 */
void levels_destroy(liste_double *levels){
  liste_double_node_t *current_node = levels->first;
  liste_double_node_t *nextNode;
  
  while(current_node != NULL) {
    nextNode = current_node->next;
    level_destroy(current_node->data);
    free(current_node);
    current_node = nextNode;  
  }
  free(levels);
}

int somme_poussees(liste_double *coups){
    unsigned int i=0;
    liste_double_node_t *current_node = coups->first;
    while(current_node != NULL) {
        if(((coup_t*)current_node->data)->pousse){
            i++;
        }
        current_node = current_node->next;  
    }
    return i;
}
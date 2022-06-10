#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
#ifndef ANIMATION_H
#include "animation.h"
#define ANIMATION_H
#endif

/**
 * @brief transforme les donnees de la liste chainee (en 1 dimension) en un tableau (de 2 dimensions) pour l'affichage du niveau
 * 
 * @param X 
 * @param LONG 
 * @param x 
 * @param y 
 */
void x2xy(unsigned int X,unsigned int LONG, unsigned int *x, unsigned int *y){
    *x=X%LONG;
    *y=X/LONG;
}


/**
 * @brief fonction permettant de verifier si l'on a pas depasse les limites du niveau (utile aussi pour le pathfiding)
 * 
 * @param level 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool is_on_map(level_t* level,unsigned int x, unsigned int y){
    if(level->hauteur>y && level->largeur>x){
        return true;
    }    
    return false;
}

/**
 * @brief permet aussi de verifier si l'on a pas depasse les limites du niveau
 * 
 * @param largeur 
 * @param hauteur 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
bool is_on_map2(unsigned largeur,unsigned int hauteur,unsigned int x, unsigned int y){
    if(hauteur>y && largeur>x){//? unsigned donc inutile && y>=0 && x>=0 
        return true;
    }    
    return false;
}

/**
 * @brief permet de connaitre les coordonnees de la case qui se trouve dans la direction demandee
 * 
 * @param direction 
 * @param index 
 * @param largeur 
 * @return unsigned int 
 */
unsigned int move_direction(char direction,unsigned int index,unsigned int largeur){
    switch (direction)
    {
        case HAUT:
            return index-largeur;
            break;
        case BAS:
            return index+largeur;
            break;
        case DROITE:
            return index+1;
            break;
        case GAUCHE:
            return index-1;
            break;
        default:
            fprintf(stderr,"[ERROR] Direction %d\n",direction);
            exit(-1);
            break;
    }
    fprintf(stderr,"[ERROR] No Direction\n");
    exit(-1);
}

/**
 * @brief verifie si toute les cibles sont occupees et renvoie true si c'est le cas
 * 
 * @param map 
 * @return true 
 * @return false 
 */
bool is_finish(liste_double *map) //! peut etre opti en mettant une pile de cible
{ 
    liste_double_node_t *current_node = map->first;
    bool cible;
    unsigned char bloc;
    while (current_node != NULL)
    {
        bloc=((case_t *)current_node->data)->bloc;
        cible=((case_t *)current_node->data)->cible;
        if((bloc==2 && !cible)||(cible && bloc!=2)){
            return false;
        }
        current_node = current_node->next;
    }
    return true;
}

/**
 * @brief deplace un objet vers la position demandee (donc adjacente)
 * 
 * @param map 
 * @param from 
 * @param to 
 */
void move_object(liste_double* map,unsigned int from,unsigned int to){//unsigned char object_value
    ((case_t *)liste_double_get(map,to))->bloc=((case_t *)liste_double_get(map,from))->bloc;
    ((case_t *)liste_double_get(map,from))->bloc=0;
}

/**
 * @brief fonction verifiant si un deplacement dans une direction est possible, en verifiant si la case suivante est bien vide
 * 
 * @param map 
 * @param index 
 * @return true 
 * @return false 
 */
bool check_empty(liste_double* map,unsigned int index){
    return ((case_t*)liste_double_get(map,index))->bloc == 0;
}

/**
 * @brief Fonction qui permet de choisir un indice aleatoire dans une liste de 4 elements 
 (correspondant aux 4 mouvements idealement disponibles pour le joueur)et verifiant si le
 deplacement est faisable avec la fonction precedente avant de l'effectuer
 * 
 * @param array 
 * @return char 
 */
char random_from_array(bool array[4]){
    //? le random est mieux sans
    char choice=rand() % (int)(array[0]+array[1]+array[2]+array[3]);
    for(unsigned char i=0;i<4;i++){
        if(array[i]){
            if(choice==0){
                return i;
            }else{
                choice--;
            }
        }
    }
    return -1;
}

/**
 * @brief verifie la nature des blocs adjacents pour determiner les mouvements possibles
 * 
 * @param level 
 * @param array 
 */
void possible_move(level_t *level,bool *array){
    array[HAUT]=check_empty(level->map,level->index-level->largeur);// HAUT
    array[BAS]=check_empty(level->map,level->index+level->largeur);// BAS
    array[DROITE]=check_empty(level->map,level->index+1);// DROITE
    array[GAUCHE]=check_empty(level->map,level->index-1);// GAUCHE
}


 /**
  * @brief permet de depiler la pile des mouvements au maximum, et donc de revenir a la situation initiale
  * 
  * @param level 
  * @param runtime 
  */
void go_all_back(level_t *level,runtime_t* runtime){
    while(go_back(level,runtime)){}
}


 /**
  * @brief deplier la double pile d'un element pour connaitre le dernier deplacement effectue
  * 
  * @param level 
  * @param runtime 
  * @return true 
  * @return false 
  */
bool go_back(level_t *level,runtime_t* runtime){
    coup_t* coup=(coup_t*)liste_double_depiler_tete(level->coups);
    if(coup==NULL){
        return false;
    }
    unsigned int old_index=level->index;
    unsigned int old_index_box=old_index;

    /**
     * @brief identifie le coup deplile et "l'inverse" afin d'annuler le deplacement effectue precedement
     * 
     */
    switch (coup->direction)
    {
        case HAUT:
            coup->direction=BAS;
            old_index_box-=level->largeur;
            break;
        case BAS:
            coup->direction=HAUT;
            old_index_box+=level->largeur;
            break;
        case GAUCHE:
            coup->direction=DROITE;
            old_index_box--;
            break;
        case DROITE:
            coup->direction=GAUCHE;
            old_index_box++;
            break;
        
        default:
            break;
    }

    /**
     * @brief deplace le joueur et l'objet dans le sens contraire au dernier coup ( = reviens en arriere)
     * 
     */
    if(!move_human(level,coup->direction,false,false,runtime)){
        return false;
    }
    if(coup->pousse){
        move_object(level->map,old_index_box,old_index);
    }
    return true;
}


/**
 * @brief gere les deplacements du joueur et de l'objet
 * 
 * @param level 
 * @param direction 
 * @param save 
 * @param move_box 
 * @param runtime
 * @return booleen qui indique si l'on peut bouger (oui = true)
 */
bool move_human(level_t *level,char direction,bool save,bool move_box,runtime_t* runtime){
    if(0==x2x(level->index,level->largeur)){return false;}
    unsigned int index_after = move_direction(direction,level->index,level->largeur);
    if(level->map->size>index_after){
        case_t* cell=(case_t*)liste_double_get(level->map,index_after);
       
        /**
         * @brief diferencie les differentes situations que l'on rencontre , 
         cas 0: on es sur du vide, on peut bouger, et on modifie l'indice et la direction + gestion du chargement de la sauvegarde
         cas 2: on doit deplacer l'objet, il faut verifier si c'est possible, puis on deplace l'objet et le joueur, en modifiant 
            son indices et sa direction
         cas 3: on se trouve dans un cas d'erreur, car on ne dois pas pouvoir rencontrer un autre joueur
         cas de base: on se trouve face a un mur, on ne peux pas bouger
         * 
         */
        switch (cell->bloc)
            {
                case 0:// air=> peut bouger no problemo
                    move_object(level->map,level->index,index_after);
                    level->index=index_after;
                    runtime->direction=direction;
                    if(save){
                        liste_double_ajout_en_tete(level->coups,create_coup(direction,false));
                    }
                    return true;
                case 2:
                    if(move_box){
                        unsigned int index_after2 = move_direction(direction,index_after,level->largeur);
                        case_t* next_cell=(case_t*)liste_double_get(level->map,index_after2);
                        if (next_cell->bloc==0){
                            move_object(level->map,index_after,index_after2);
                            move_object(level->map,level->index,index_after);
                            animate_box_moving(runtime,direction,index_after,index_after2);
                            level->index=index_after;
                            runtime->direction=direction;
                            if(save){
                                liste_double_ajout_en_tete(level->coups,create_coup(direction,true));
                            }
                            if(next_cell->cible){
                                level->solved=is_finish(level->map);
                            }
                            return true;
                        }
                    }
                    break;
                case 3: //cas ou il y a 2 perso = problem
                    fprintf(stderr,"[ERROR]2 humans %d(%d-%d)->%d(%d-%d)\n",
                        level->index,x2x(level->index,level->largeur),x2y(level->index,level->largeur),
                        index_after,x2x(index_after,level->largeur),x2y(index_after,level->largeur)
                    );
                    exit(-1);
                default:
                    break;
            }
    }
    return false;
}

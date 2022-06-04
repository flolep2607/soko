#pragma once
#include <stdbool.h>
#include <stdlib.h>
#ifndef LEVEL_C
#include "level.c"
#define LEVEL_C
#endif
#ifndef FILE_C
#include "../librairies/file.c"
#define FILE_C
#endif
//? directions
#define HAUT 1
#define BAS 2
#define DROITE 3
#define GAUCHE 4
#define xy2x(X, Y,LONG)  (X + Y * LONG)
void x2xy(unsigned int X,unsigned int LONG, unsigned int *x, unsigned int *y){
    *x=X%LONG;
    *y=X/LONG;
}

unsigned int find_human(gll_t *map){
    unsigned int index=0;
    gll_node_t *currNode = map->first;
    while(currNode != NULL) {
        if(((case_t*)currNode->data)->bloc==3){
            return index;
        }
        currNode = currNode->next;
        index++;
    }
    printf("[ERROR] No human\n");
    exit(-1);
}

bool is_on_map(level_t* level,unsigned int x, unsigned int y){
    if(level->hauteur>y && y>0 && level->largeur>x && x>0){
        return true;
    }    
    return false;
}
bool is_on_map2(unsigned largeur,unsigned int hauteur,unsigned int x, unsigned int y){
    if(hauteur>y && y>0 && largeur>x && x>0){
        return true;
    }    
    return false;
}

void move_direction(char direction,unsigned int *x_after,unsigned int *y_after){
    switch (direction)
    {
        case HAUT:
            (*y_after)--;
            break;
        case BAS:
            (*y_after)++;
            break;
        case DROITE:
            (*x_after)++;
            break;
        case GAUCHE:
            (*x_after)--;
            break;
        default:
            printf("Direction error\n");
            break;
    }
}


bool is_finish(gll_t *map) //! peut etre opti en mettant une pile de cible
{ 
    gll_node_t *currNode = map->first;
    bool cible;
    unsigned char bloc;

    while (currNode != NULL)
    {
        bloc=((case_t *)currNode->data)->bloc;
        cible=((case_t *)currNode->data)->cible;
        if((bloc==2 && !cible)||(cible && bloc!=2)){
            return false;
        }
        currNode = currNode->next;
    }
    return true;
}

void move_object(gll_t* map,unsigned int pos1,unsigned int pos2,unsigned char object_value){
    ((case_t *)gll_get(map,pos1))->bloc=0;
    ((case_t *)gll_get(map,pos2))->bloc=object_value;
}

bool move_human(level_t *level,char direction,unsigned int *x,unsigned int *y){
    unsigned int x_after=*x;
    unsigned int y_after=*y;
    move_direction(direction,& x_after,& y_after);
    unsigned int pos=xy2x(x_after,y_after,level->largeur);
    case_t* cell=(case_t*)gll_get(level->map,pos);
    if(is_on_map(level,x_after,y_after)){
        switch (cell->bloc)
            {
                case 0:// air=> peut bouger no problemo
                    move_object(level->map,xy2x(*x,*y,level->largeur),pos,2);
                    *x=x_after;
                    *y=y_after;
                    return true;
                    break;
                case 2:
                    //? check behind box
                    move_direction(direction,& x_after,& y_after);
                    unsigned int next_pos=xy2x(x_after,y_after,level->largeur);
                    case_t* next_cell=(case_t*)gll_get(level->map,xy2x(x_after,y_after,level->largeur));
                    if (next_cell->bloc==0){
                        move_object(level->map,pos,next_pos,2);
                        move_object(level->map,xy2x(*x,*y,level->largeur),pos,2);
                        *x=x_after;
                        *y=y_after;
                        //! move box
                        return true;
                    }
                    break;
                case 3:
                    printf("[ERROR]2 humans\n");
                    exit(-1);
                default:
                    break;
            }
    }
    return false;
}

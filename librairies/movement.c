#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "level.c"
//? directions
#define HAUT 1
#define BAS 2
#define DROITE 3
#define GAUCHE 4
#define xy2x(X, Y,LONG)  (X + Y * LONG)
void x2xy(unsigned int X,unsigned int LONG, unsigned int *x, unsigned int *y){
    x=X%LONG;
    y=X/LONG;
}

unsigned int find_human(level_t *level){
    unsigned int index=0;
    gll_node_t *currNode = level->map->first;

    while(currNode != NULL) {
        if(((case_t*)currNode->data)->bloc==3){
            return index;
        }
        currNode = currNode->next;
        index++;
    }
    return NULL;
}

bool on_map(level_t* level,unsigned int x, unsigned int y){
    if(level->hauteur>y>0){
        if(level->largeur>x>0){
            return true;
        }
    }    
    return false;
}

bool move(level_t *level,int direction,unsigned int *x,unsigned int *y){
    unsigned int x_after=&x;
    unsigned int y_after=&y;
    switch (direction)
    {
    case HAUT:
        y_after--;
        break;
    case BAS:
        y_after++;
        break;
    case DROITE:
        x_after++;
        break;
    case GAUCHE:
        x_after--;
        break;
    default:
        printf("Direction error\n");
        break;
    }
    case_t* cell=(case_t*)gll_get(level->map,xy2x(x_after,y_after,level->largeur));
    switch (cell->bloc)
    {
    case 0:
        /* code */
        break;
    
    default:
        break;
    }
    return true;
}

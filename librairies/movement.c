#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif


void x2xy(unsigned int X,unsigned int LONG, unsigned int *x, unsigned int *y){
    *x=X%LONG;
    *y=X/LONG;
}
void find_human(level_t *level){
    unsigned int index=0;
    gll_node_t *currNode = level->map->first;
    while(currNode != NULL) {
        if(((case_t*)currNode->data)->bloc==3){
            x2xy(index,level->largeur,&(level->x),&(level->y));
            level->index=index;
            level->x=x2x(index,level->largeur);
            level->y=x2y(index,level->largeur);
            return;
            // return index;
        }
        currNode = currNode->next;
        index++;
    }
    printf("[ERROR] No human\n");
    exit(-1);
}

bool is_on_map(level_t* level,unsigned int x, unsigned int y){
    if(level->hauteur>y && level->largeur>x){//? unsigned donc inutile && y>=0 && x>=0 
        return true;
    }    
    return false;
}

bool is_on_map2(unsigned largeur,unsigned int hauteur,unsigned int x, unsigned int y){
    if(hauteur>y && largeur>x){//? unsigned donc inutile && y>=0 && x>=0 
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

bool go_back(level_t *level){
    coup_t* coup=(coup_t*)gll_pop(level->coups);
    if(coup==NULL){
        return false;
    }
    unsigned int old_index=level->index;
    unsigned int old_index_box=old_index;
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
    if(!move_human(level,coup->direction,false)){
        return false;
    }
    if(coup->pousse){
        move_object(level->map,old_index_box,old_index,2);
    }
    return true;
}
bool move_human(level_t *level,char direction,bool save){
    unsigned int x_after=level->x;
    unsigned int y_after=level->y;
    move_direction(direction,& x_after,& y_after);
    unsigned int pos=xy2x(x_after,y_after,level->largeur);
    case_t* cell=(case_t*)gll_get(level->map,pos);
    if(is_on_map(level,x_after,y_after)){
        switch (cell->bloc)
            {
                case 0:// air=> peut bouger no problemo
                    //; Move human
                    printf("nothing in front I can move\n");
                    move_object(level->map,level->index,pos,3);
                    level->x=x_after;
                    level->y=y_after;
                    level->index=xy2x(level->x,level->y,level->largeur);
                    if(save){
                        coup_t* coup=(coup_t*)malloc(sizeof(coup_t));
                        coup->direction=direction;
                        coup->pousse=false;
                        gll_push(level->coups,coup);
                    }
                    return true;
                    break;
                case 2:
                    //? check behind box
                    printf("box in front\n");
                    unsigned int x_after2=x_after;
                    unsigned int y_after2=y_after;
                    move_direction(direction,& x_after2,& y_after2);
                    case_t* next_cell=(case_t*)gll_get(level->map,xy2x(x_after2,y_after2,level->largeur));
                    printf("%d-%d->%d-%d=%d\n",x_after,y_after,x_after2,y_after2,next_cell->bloc);
                    if (next_cell->bloc==0){
                        printf("box in front but I can move\n");
                        //; Move box
                        move_object(level->map,pos,xy2x(x_after2,y_after2,level->largeur),2);
                        //; Move human
                        move_object(level->map,level->index,pos,3);
                        level->x=x_after;
                        level->y=y_after;
                        level->index=xy2x(level->x,level->y,level->largeur);
                        if(save){
                            coup_t* coup=(coup_t*)malloc(sizeof(coup_t));
                            coup->direction=direction;
                            coup->pousse=true;
                            gll_push(level->coups,coup);
                        }
                        //! move box
                        return true;
                    }
                    break;
                case 3:
                    printf("[ERROR]2 humans\n");
                    exit(-1);
                default:
                    printf("It's a wall\n");
                    break;
            }
    }
    return false;
}

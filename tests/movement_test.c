#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef FILE_H
#include "../librairies/movement.c"
#define FILE_C
#endif
#ifndef FILE_H
#include "../librairies/file.c"
#define FILE_C
#endif
#ifndef LEVEL_C
#include "../librairies/#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif"
#define LEVEL_C
#endif

void test_one_lvl(gll_node_t *node_lvl,bool can_move,unsigned int direction,unsigned int human_pos_good,unsigned int x_before,unsigned int y_before,unsigned int x_after,unsigned int y_after){
    level_t* level_current = (level_t*)node_lvl->data;
    find_human(level_current);
    // printf("lvlnum:%d\n",level_current->numero_lvl);
    // printf("human_pos:%hhu\n",human_pos);
    assert(level_current->index==human_pos_good);
    // printf("x:%hhu|y:%hhu\n",x,y);
    assert(level_current->x==x_before);assert(level_current->y==y_before);
    assert(is_on_map2(level_current->largeur,level_current->hauteur,level_current->x,level_current->y));
    assert(move_human(level_current,direction)==can_move);
    assert(level_current->x==x_after);assert(level_current->y==y_after);
    printf("✓Map %d\n",level_current->numero_lvl);
}

int main(){
    
    gll_t* levels = read_file("data/levels_test.lvl");
    //; MAP1
    gll_node_t *node_lvl = levels->first;
    test_one_lvl(node_lvl,false,DROITE,12,2,2,2,2);
    //; MAP2
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,DROITE,13,3,2,3,2);
    //; MAP3
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,DROITE,14,4,2,4,2);
    //; MAP4
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,true,DROITE,13,3,2,4,2);
    //; MAP5
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,DROITE,13,3,2,3,2);
    //; MAP6
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,GAUCHE,12,2,2,2,2);
    //; MAP7
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,GAUCHE,11,1,2,1,2);
    //; MAP8
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,GAUCHE,10,0,2,0,2);
    //; MAP9
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,true,GAUCHE,11,1,2,0,2);
    //; MAP10
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,true,GAUCHE,11,1,2,0,2);
    case_t* cell=(case_t*)gll_get(((level_t*)node_lvl->data)->map,10);
    assert(cell->cible);
    assert(cell->bloc==3);
    //; MAP11
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,HAUT,7,2,1,2,1);









    
    destroy_levels(levels);
    return 0;
}




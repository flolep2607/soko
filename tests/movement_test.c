#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef MOVEMENT_H
#include "../src/movement.h"
#define MOVEMENT_H
#endif
#ifndef FILE_H
#include "../src/file.h"
#define FILE_H
#endif
#ifndef PILE_H
#include "../src/pile.h"
#define PILE_H
#endif

/**
 * @brief Verifie si le niveau a ete lu correctement. 
 * Verifie si la position trouve pour l'humain est bien la bonne et si apres un deplacement il se trouve bien a l'endroit souhaite
 * 
 * @param node_lvl 
 * @param can_move 
 * @param direction 
 * @param human_pos_good 
 * @param x_before 
 * @param y_before 
 * @param x_after 
 * @param y_after 
 */
void test_one_lvl(liste_double_node_t *node_lvl,bool can_move,unsigned int direction,unsigned int human_pos_good,unsigned int x_before,unsigned int y_before,unsigned int x_after,unsigned int y_after){
    level_t* level_current = (level_t*)node_lvl->data;
    find_human(level_current);
    assert(level_current->index==human_pos_good);
    runtime_t runtime;
    assert(level_current->index==xy2x(x_before,y_before,level_current->largeur));
    assert(move_human(level_current,direction,true,true,&runtime)==can_move);
    assert(level_current->index==xy2x(x_after,y_after,level_current->largeur));

    printf("✓Map %d\n",level_current->lvl_number);
}

/**
 * @brief Effectue les tests de mouvements à l'aide des fonctions precedentes.  
 * 
 * @return int 
 */
int main(){
    
    liste_double* levels = read_file("data/levels_test.lvl");
    //; MAP1
    liste_double_node_t *node_lvl = levels->first;
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
    case_t* cell=(case_t*)liste_double_get(((level_t*)node_lvl->data)->map,10);
    assert(cell->cible);
    assert(cell->bloc==3);
    //; MAP11
    node_lvl = node_lvl->next;
    test_one_lvl(node_lvl,false,HAUT,7,2,1,2,1);    
    levels_destroy(levels);
    return 0;
}




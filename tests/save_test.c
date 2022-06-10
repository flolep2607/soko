#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#ifndef FILE_H
#include "../src/file.h"
#define FILE_H
#endif


int main(void)
{
    liste_double* coups = liste_double_init();
    liste_double_ajout_en_tete(coups,create_coup(1,0));
    save_coups(coups,0);
    liste_double_destroy(coups);
    liste_double* levels = liste_double_init();
    read_save("data/save.bin",levels);
    liste_double_node_t *current_node= levels->first;
    level_t* level;
    while(current_node!=NULL){
        level=current_node->data;
        // printf("lvl:%d solved:%d mapsize:%d\n",level->lvl_number,level->solved,level->map->size);
        assert(level->map->size=level->hauteur*level->largeur);
        printf("✓Map %d\n",level->lvl_number);
        current_node=current_node->next;
    }
    // printf("%d\n",levels->size);
    // printf("first:%d\n",((level_t*)levels->first)->solved);
    // printf("last(%d):%d\n",((level_t*)levels->last->prev->prev)->lvl_number,((level_t*)levels->last->prev)->map->size);
    // printf("last(%d):%d\n",((level_t*)levels->last->prev)->lvl_number,((level_t*)levels->last)->map->size);
    // printf("first(%d)):%d\n",((level_t*)levels->first)->lvl_number,((level_t*)levels->first)->map->size);
    // assert(((level_t*)levels->first)->solved);
    assert(levels->size==88);
    levels_destroy(levels);
}

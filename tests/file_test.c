#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef FILE_H
#include "../src/file.h"
#define FILE_H
#endif
#ifndef PILE_H
#include "../src/pile.h"
#define PILE_H
#endif
#define SIZE 209


/**
 * @brief test la lecture d'un fichier source "levels_test2.lvl", cree une liste double associee et 
 compare ensuite la liste nouvellement cree et la liste attendue
 * 
 * @param liste 
 * @param size 
 * @return true 
 * @return false, dans les cas 
 */
bool test_read(int* liste,unsigned int size){
    unsigned int i=0;
    FILE * inputFile;
    inputFile = fopen( "data/levels_test2.lvl", "r" );
    if ( inputFile == NULL ) {
        inputFile = fopen("../data/levels_test2.lvl", "r");
        if ( inputFile == NULL ) {
            return false;
        }
    }
    int largeur_max = largeur(inputFile);
    assert(largeur_max==19);
    liste_double* map = liste_double_init();
    read_map(inputFile,largeur_max,map);
    liste_double_node_t *current_node = map->first;
    while(current_node != NULL && i<size) {
        if(((case_t*)current_node->data)->bloc!=liste[i]){
            return false;
        }
        i++;
        current_node = current_node->next;
    }
    assert(i==size && size == map->size);
    liste_double_destroy(map);
    return i==size;
}
/**
 * @brief lis le fichier "levels_officiel.lvl", associe a chaque niveau sa largeur et sa hauteur, pour 
 creer l'espace de la taille correspondante
 * 
 * @param liste 
 * @param size 
 * @return true
 */
bool test_read_file(){
    liste_double* levels = read_file("data/levels_offficiel.lvl");
    if(&(levels->size)==NULL){
        printf("sizemap:NULL");
        return false;
    }
    assert(((level_t*)levels->first->data)->map->size==209);
    assert(((level_t*)levels->first->data)->largeur==19);
    assert(((level_t*)levels->first->data)->hauteur==11);
    assert(((level_t*)levels->first->data)->hauteur==11);
    levels_destroy(levels);
    return true;
}

int main(void)
{
                    // 1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0
    int liste1[SIZE]={0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,2,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,0,2,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,1,3,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
    // int liste1[SIZE]= {1,1,1,1,0,1,1,0};
    // int liste1[SIZE]= {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0};
    // int liste2[SIZE]= {1,1,1,1,1,1,0,3,0,1,1,2,1,1,1,1,0,0,0,1,1,1,1,1};
    // int liste3[SIZE]= {1,1,1,1,1,1,2,0,0,1,1,1,1,2,1,1,3,0,0,1,1,1,1,1};
    assert(test_read(liste1,SIZE));
    printf("✓test_read\n");
    assert(test_read_file(liste1,SIZE));
    printf("✓test_read_file\n");
    return 0;
}
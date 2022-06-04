#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef FILE_C
#include "../librairies/file.c"
#define FILE_C
#endif
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif
#define SIZE 209
//24

bool test_read(int* liste,unsigned int size){
    unsigned int i=0;
    FILE * inputFile;
    inputFile = fopen( "data/levels_test2.lvl", "r" );
    if ( inputFile == NULL ) {
        inputFile = fopen("../data/levels_test2.lvl", "r");
        // printf( "Cannot open file data/levels_test2.lvl\n" );
        // exit( 0 );
    }
    int largeur_max = largeur(inputFile);
    printf("->%d\n",largeur_max);
    //? READ MAP
    gll_t* map = read_map(inputFile,largeur_max);
    gll_node_t *currNode = map->first;
    while(currNode != NULL && i<size) {
        // printf("%d-%d\n",((case_t*)currNode->data)->bloc,liste[i]);
        if(((case_t*)currNode->data)->bloc!=liste[i]){
            return false;
        }
        i++;
        currNode = currNode->next;
    }
    printf("=>%u==%d==%d\n",i,size,map->size);
    gll_destroy(map);
    return i==size;
}
bool test_read_file(int* liste,unsigned int size){
    gll_t* levels = read_file("data/levels_offficiel.lvl");
    if(&(levels->size)==NULL){
        printf("sizemap:NULL");
    }else{
        printf("sizemap:%d\n",((level_t*)levels->first->data)->map->size);
    }
    printf("largeur:%d\n",((level_t*)levels->first->data)->largeur);
    printf("hauteur:%d\n",((level_t*)levels->first->data)->hauteur);
    printf("cases:%d==%d\n",((level_t*)levels->first->data)->map->size,((level_t*)levels->first->data)->hauteur*((level_t*)levels->first->data)->largeur);
    destroy_levels(levels);
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
    assert(test_read_file(liste1,SIZE));
    return 0;
}
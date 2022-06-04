#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// #ifndef LISTE_CHAINE
// #include "../librairies/liste_chaine.c"
// #define LISTE_CHAINE
// #endif 
#ifndef FILE_C
#include "../librairies/file.c"
#define FILE_C
#endif
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif
#define SIZE 24





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
    gll_node_t *currNode = map->last;
    while(currNode != NULL && i<size) {
        printf("%d\n",((case_t*)currNode->data)->bloc);
        i++;
        currNode = currNode->prev;
    }
    printf("=>%u==24\n",i);
    gll_destroy(map);
    return i==size;
}

int main(void)
{
    int liste1[SIZE]= {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0};
    int liste2[SIZE]= {1,1,1,1,1,1,0,3,0,1,1,2,1,1,1,1,0,0,0,1,1,1,1,1};
    int liste3[SIZE]= {1,1,1,1,1,1,2,0,0,1,1,1,1,2,1,1,3,0,0,1,1,1,1,1};
    assert(test_read(liste1,SIZE));
    return 0;
}
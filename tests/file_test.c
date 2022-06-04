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

static unsigned int i=0;
int liste1[SIZE]= {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0};

void test_map_bloc(void *x){
    printf("%d\n",((case_t*)x)->bloc);
    i++;
}

bool test_read(int* liste,unsigned int size){
    i=0
    int length = 0;
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
    
    gll_eachReverse(map,test_map_bloc);
    // while (map->next != NULL && i<size )
    // {
    //     printf("%d-%d-%d\n",((case_t *)map->data)->bloc,liste[size-i],i);
    //     // if(((case_t *)level->data)->bloc!=liste[i]) return false;
    //     i++;
    //     level = map->next;
    // }
    printf("=>%u==24\n",i);
    gll_destroy(map);
    return i==size;
}

int main(void)
{
    
    // int liste2[]= {1,1,1,1,1,1,0,3,0,1,1,2,1,1,1,1,0,0,0,1,1,1,1,1,1};
    // int liste3[]= {1,1,1,1,1,1,2,0,0,1,1,1,1,2,1,1,3,0,0,1,1,1,1,1,1};
    assert(test_read(liste1,SIZE));
    return 0;
}
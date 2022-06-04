#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef FILE_C
#include "../librairies/movement.c"
#define FILE_C
#endif
#ifndef FILE_C
#include "../librairies/file.c"
#define FILE_C
#endif
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif

int main(){
    FILE * inputFile;
    inputFile = fopen( "data/levels_test2.lvl", "r" );
    if ( inputFile == NULL ) {
        inputFile = fopen("../data/levels_test2.lvl", "r");
        // printf( "Cannot open file data/levels_test2.lvl\n" );
        // exit( 0 );
    }
    int largeur_max = largeur(inputFile);
    gll_t* map = read_map(inputFile,largeur_max);
    unsigned int human_pos = find_human(map);
    assert(human_pos==163);
    printf("human_pos:%hhu\n",human_pos);
    unsigned int x;
    unsigned int y;
    x2xy(human_pos,largeur_max,&x,&y);
    printf("x:%hhu|y:%hhu\n",x,y);
    assert(x==11);assert(y==8);
    assert(is_on_map2(largeur_max,map->size/largeur_max,x,y));
    gll_destroy(map);
    return 0;
}




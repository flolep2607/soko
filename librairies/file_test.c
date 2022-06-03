#include <stdio.h>
#include <stdlib.h>
#ifndef LISTE_CHAINE
#include "../librairies/liste_chaine.c"
#define LISTE_CHAINE
#endif
#ifndef FILE_C
#include "../librairies/file.c"
#define FILE_C
#endif 
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif
#define SIZE 25



bool test_read(int liste[SIZE]){
    // ! Fopen
    node_t* level = read_map();
    int i=0;
    while (level->next != NULL)
    {
        if(((case_t *)level->data)->bloc!=liste[i]) return false;
        i++;
        level = level->next;
    }
    return i==SIZE;
}

int main(void)
{
    int liste1[SIZE]= {1,1,1,1,1,1,0,0,0,1,1,0,3,0,1,1,0,0,0,1,1,1,1,1,1};
    // int liste2[]= {1,1,1,1,1,1,0,3,0,1,1,2,1,1,1,1,0,0,0,1,1,1,1,1,1};
    // int liste3[]= {1,1,1,1,1,1,2,0,0,1,1,1,1,2,1,1,3,0,0,1,1,1,1,1,1};
    if( test_read(liste1)){
        printf("GOOD\n");
    }
    return 0;
}
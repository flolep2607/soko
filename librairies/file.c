#include <stdio.h>
#include <stdlib.h>
#include "liste_chaine.c"
#include "level.c"


void size(){
    
}

void affiche_lvl(void){
    
    


}

void read(void){
    FILE* flux_entree;
    flux_entree = fopen("data/levels_tests2.lvl","r");

    node_t* level=(node_t *) malloc(sizeof(node_t));
    while(fgetc(flux_entree) != '\n'){
        switch (fgetc(flux_entree))
        {
        case '#':
            case_t* case_=(case_t *) malloc(sizeof(case_t));
            case_->bloc = 1;
            case_->cible = false;
            push(level, case_,sizeof(case_t));

            break;
        case ' ':

            break;

        
        default:
            break;
        }


             

        
    }
}


int main (void)
{
    read();


    return 1;
}
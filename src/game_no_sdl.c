#ifndef GAME_H
#include "game_no_sdl.h"
#define GAME_H
#endif
#ifndef PATH_C
#include "pathfinding.c"
#define PATH_C
#endif

void go_to(unsigned int x,unsigned int y){
    printf("\e[%d;%dH",y,x);
}

void show_game(runtime_t *runtime){
    printf("\e[1;1H\e[3J");
    liste_double_node_t *map_node=runtime->level->map->first;
    unsigned int i=0;
    while(map_node!=NULL){
        case_t* cell=((case_t*)map_node->data);
        switch (cell->bloc)
        {
            case WALL:
                printf("█");
                break;
            case BOX:
                if(cell->cible){
                    printf("*");
                }else{
                    printf("$");
                }
                break;
            case BODY:
                if(cell->cible){
                    printf("O");
                }else{
                    printf("@");
                }
                break;
            default:
                if(cell->cible){
                    printf(".");
                }else{
                    printf(" ");
                }
                break;
        }
        map_node=map_node->next;
        i++;
        if(i%runtime->level->largeur==0){
            printf("\n");
        }
    }
    printf("\n");
    printf("Level %d\n",runtime->level->lvl_number);
}
void refresh_screen(runtime_t* runtime,int x,int y){
    show_game(runtime);
}

void animate_box_moving(runtime_t* runtime,unsigned char direction,unsigned int index_start,unsigned int index_end){

}


/**
 * @brief Reagis aux actions des touches pendant qu'il n'y a pas d'action en cours.
 * 
 * @param levels 
 * @param level_node position dans la liste des levels
 * @param runtime 
 * @return bool
 */
bool event_handler(liste_double* levels,liste_double_node_t *level_node,runtime_t* runtime){
    int c = litClavier();
    switch(c){
        case 1://UP
            move_human(runtime->level,HAUT,true,true,runtime);
            break;
        case 2: //BAS
            move_human(runtime->level,BAS,true,true,runtime);
            break;
        case 4://GAUCHE
            move_human(runtime->level,GAUCHE,true,true,runtime);
            break;
        case 3://DROITE
            move_human(runtime->level,DROITE,true,true,runtime);
            break;
        case 127://BACKSPACE
            if(!go_back(runtime->level,runtime)){
                fprintf(stderr,"[INFO] go_back empty or error \n");
                return false;
            }
            // printf("REVERSE\n");
            break;
        case 114: //R
            go_all_back(runtime->level,runtime);
            // printf("REVERSED\n");
            break;
        case 103: // G
            save_game(levels,"data/save.bin");
            printf("SAVED\n");
            break;
        case 112: //P
            go_to(1,1);printf("✗\n");
            c=litClavier();
            int x=0,y=0;
            while(c!='\n'){
                switch(c){
                    case 1://UP
                        if(y>0){
                            y--;
                        }
                        break;
                    case 2: //BAS
                        if(y<runtime->level->hauteur){
                            y++;
                        }
                        break;
                    case 4://GAUCHE
                        if(x>0){
                            x--;
                        }
                        break;
                    case 3://DROITE
                        if(x<runtime->level->largeur){
                            x++;
                        }
                        break;
                    default:
                    break;
                }
                show_game(runtime);
                go_to(x+1,y+1);
                printf("✗\n");
                c=litClavier();
            }
            path_finding(runtime->level,x,y,runtime,refresh_screen);
            break;
        case 110: //R
            liste_double_vider(runtime->level->coups,false);
            runtime->level->solved=true;
            break;
        case 108: //L
            read_save("data/save.bin",levels);
            level_node=levels->first;
            runtime->level=(level_t *)level_node->data;
            break;
        case 113: //Q
            runtime->QUIT_GAME=true;
            break;
        default:
            printf("%d\n",c);
            return false;
    }
    return true;
}

int main(void){
    configureTerminal();
    runtime_t* runtime = (runtime_t*)malloc(sizeof(runtime_t));
    runtime->QUIT_GAME=false;
    runtime->pathfinding=false;
    runtime->direction=DROITE;
    liste_double* levels = read_file("data/levels_offficiel.lvl");//"data/hugemap.lvl");
    liste_double_node_t* level_node=levels->first;
    runtime->level=(level_t*)level_node->data;
    printf("\e[1;1H\e[2J");
    show_game(runtime);
    while(!runtime->QUIT_GAME){
        if(event_handler(levels,level_node,runtime)){
            show_game(runtime);
        }
        if(runtime->level->solved && level_node->next!=NULL){
            save_coups(runtime->level->coups,runtime->level->lvl_number);
            level_node=level_node->next;
            runtime->level=(level_t*)level_node->data;
            printf("\e[1;1H\e[2J");
            show_game(runtime);
        }
    }
Quit:
    levels_destroy(levels);
    resetTerminal();
    return 0;
}
#include <stdbool.h>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>

#ifndef RUNTIME_H
#include "runtime.h"
#define RUNTIME_H
#endif
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif

// /**
//  * @brief fonction de pathfinding random (donc pas l'utiliser svp)
//  * 
//  * @param level 
//  * @param x 
//  * @param y 
//  * @param runtime 
//  * @return true 
//  * @return false 
//  */
// bool random_pathfinding(level_t *level,unsigned int x,unsigned int y,runtime_t* runtime){
//     case_t* final_cell = ((case_t*)liste_double_get(level->map,xy2x(x,y,level->largeur)));
//     bool possible[4];
//     char direction;
//     if(is_on_map(level,x,y) && final_cell->bloc==0){
//         unsigned short int i=1;
//         while(i>0 && !runtime->QUIT_GAME && runtime->pathfinding){
//             possible_move(level,possible);
//             direction=random_from_array(possible);
//             if(direction<0){
//                 fprintf(stderr,"[ERROR] u blocked between walls/blocks\n");
//                 return false;
//             }
//             move_human(level,direction,true,false,runtime);
//             if(final_cell->bloc==3){
//                 return true;
//             }
//             renderer_clear_window(runtime);
//             show_game(runtime);
//             SDL_Rect rect = {x*SIZE_TEXTURE, y*SIZE_TEXTURE, SIZE_TEXTURE, SIZE_TEXTURE};
//             renderer_set_color(runtime,(SDL_Color){255,0,0,255});
//             SDL_RenderFillRect(runtime->renderer, &rect); 
//             SDL_RenderPresent(runtime->renderer);
//             // SDL_Delay(1);
//             SDL_PumpEvents();
//         }
//     }
//     return false;
// }



/**
 * @brief pathfind avec recurrence simple mais efficace (ne trouve pas le chemin le plus court mais utilise peu de memoire)
 * 
 * @param level 
 * @param index 
 * @param value 
 * @param index_cible 
 * @param coups 
 * @return bool
 */
bool working_pathfinding(level_t* level,unsigned int index,unsigned int value,unsigned int index_cible,liste_double* coups){
    if(index_cible==index){
        return true;
    }
    case_t* cell =(case_t*)liste_double_get(level->map,index);
    if((cell->bloc==0 || cell->bloc==3) && !(cell->weight)){
        cell->weight=true;
        for(char i=0;i<4;i++){
            //! if index_cible found
            if(working_pathfinding(level,move_direction(i,index,level->largeur),value,index_cible,coups)){
                liste_double_ajout_en_tete(coups,create_coup(i,false));
                return true;
            }
        }
    }
    return false;
}


/**
 * @brief 
 * 
 * @param map 
 */
void map_reset_weigth(liste_double* map){
    liste_double_node_t *current_node = map->first;

    while(current_node != NULL) {
        ((case_t*)current_node->data)->weight=false;
        current_node = current_node->next;
    }
}

/**
 * @brief 
 * 
 * @param level 
 * @param x 
 * @param y 
 * @param runtime 
 * @return true 
 * @return false 
 */
bool recurrence_pathfinding(level_t *level,unsigned int x,unsigned int y,runtime_t* runtime,void (*refresh_screen)(runtime_t*,int,int)){
    unsigned int index_cible=xy2x(x,y,level->largeur);
    if(index_cible>=level->map->size || ((case_t*)liste_double_get(level->map,index_cible))->bloc!=0 ){
        return false;
    }
    
    map_reset_weigth(level->map);
    liste_double* coups = liste_double_init();
    if(working_pathfinding(level,level->index,0,index_cible,coups)){
        liste_double_node_t *current_node = coups->first;
        while(current_node != NULL) {
            coup_t* coup=(coup_t*)(current_node->data);
            move_human(level,coup->direction,true,false,runtime);
            current_node = current_node->next;
            (*refresh_screen)(runtime,x,y);
        }
        liste_double_destroy(coups);
        return true;
    }else{
        fprintf(stderr,"NOT FOUND\n");
    }
    liste_double_destroy(coups);
    return false;
}

/**
 * @brief 
 * 
 * @param level 
 * @param x 
 * @param y 
 * @param runtime 
 * @return true 
 * @return false 
 */
bool path_finding(level_t *level,unsigned int x,unsigned int y,runtime_t* runtime,void (*refresh_screen)(runtime_t*,int,int)){
    runtime->pathfinding=true;
    // if(random_pathfinding(level,x,y,runtime)){
    //     runtime->pathfinding=false;
    //     return true;
    // }
    if(recurrence_pathfinding(level,x,y,runtime,refresh_screen)){
        runtime->pathfinding=false;
        return true;
    }
    runtime->pathfinding=false;
    return false;
}
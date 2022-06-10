#ifndef ANIMATION_H
#include "animation.h"
#define ANIMATION_H
#endif


/**
 * @brief Anime le mouvement des oeufs.
 * 
 * @param runtime 
 * @param direction 
 * @param index_start 
 * @param index_end 
 */
void animate_box_moving(runtime_t* runtime,unsigned char direction,unsigned int index_start,unsigned int index_end){
    int depart,arrive;
    double angle = 0;
    SDL_Rect clear_zone={
        x2x(index_start<index_end?index_start:index_end,runtime->level->largeur)*SIZE_TEXTURE,
        x2y(index_start,runtime->level->largeur)*SIZE_TEXTURE,
        2*SIZE_TEXTURE,SIZE_TEXTURE};
    SDL_Rect * position=(SDL_Rect *) malloc(sizeof(SDL_Rect));
    position->w=(int)SIZE_TEXTURE;
    position->h=(int)SIZE_TEXTURE;
    switch (direction)
    {
    case DROITE:
        position->y=x2y(index_start,runtime->level->largeur)*SIZE_TEXTURE;
        depart=x2x(index_start,runtime->level->largeur)*SIZE_TEXTURE;
        arrive=x2x(index_end,runtime->level->largeur)*SIZE_TEXTURE;
        for(int i=depart;i<arrive;i++){
            position->x=i;
            renderer_set_color(runtime,runtime->empty);
            SDL_RenderFillRect(runtime->renderer, &clear_zone);
            angle=(double)(i-depart)/(arrive-depart)*360;
            SDL_RenderCopyEx(runtime->renderer,runtime->textures[1],NULL,position,angle,NULL,SDL_FLIP_NONE);
            SDL_RenderPresent(runtime->renderer);
            SDL_Delay(30/(arrive-depart));
        }
        break;
    case GAUCHE:
        position->y=x2y(index_start,runtime->level->largeur)*SIZE_TEXTURE;
        depart=x2x(index_start,runtime->level->largeur)*SIZE_TEXTURE;
        arrive=x2x(index_end,runtime->level->largeur)*SIZE_TEXTURE;
        for(int i=depart;i>arrive;i--){
            position->x=i;
            renderer_set_color(runtime,runtime->empty);
            SDL_RenderFillRect(runtime->renderer, &clear_zone);
            angle=(double)(i-arrive)/(depart-arrive)*360;
            SDL_RenderCopyEx(runtime->renderer,runtime->textures[1],NULL,position,angle,NULL,SDL_FLIP_NONE);
            SDL_RenderPresent(runtime->renderer);
            SDL_Delay(30/(depart-arrive));
        }
        break;
    
    default:
        break;
    }
    free(position);
}
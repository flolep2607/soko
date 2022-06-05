#include <stdbool.h>
#include <SDL2/SDL.h>
#include <unistd.h> 
#include <stdio.h>
#include "movement.c"


int affichage_init(runtime_t *runtime){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0){
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    runtime->win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(NULL == runtime->win)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return -1;
    }
    runtime->renderer = SDL_CreateRenderer(runtime->win, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == runtime->renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}
// void affiche_lvl(level_t *level)
// {
    
// }
void affichage_quit(runtime_t *runtime){
    if(NULL != runtime->renderer){
        SDL_DestroyRenderer(runtime->renderer);
    }
    if(NULL != runtime->win){
        SDL_DestroyWindow(runtime->win);
    }
    SDL_Quit();
    free(runtime);
}
int main(void){
    runtime_t* runtime = (runtime_t*)malloc(sizeof(runtime_t));
    if(affichage_init(runtime)==-1){
        goto Quit;
    }
    sleep(5);
Quit:
    affichage_quit(runtime);
    return 0;
}
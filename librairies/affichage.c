#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h> 
#include <stdio.h>
#ifndef LEVEL_C
#include "level.c"
#define LEVEL_C
#endif
// #include "movement.c"


SDL_bool QUIT_GAME = SDL_FALSE;

int renderer_set_color(runtime_t *runtime,SDL_Color color){
    if(0 != SDL_SetRenderDrawColor(runtime->renderer, color.r, color.g, color.b, color.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

int renderer_clear(runtime_t *runtime){
    if(0 != SDL_RenderClear(runtime->renderer))
    {
        fprintf(stderr, "Erreur SDL_RenderClear : %s", SDL_GetError());
        return -1;
    }
    return 0;
}
int renderer_setWindowColor(runtime_t *runtime, SDL_Color color)
{
    if(renderer_set_color(runtime, color) < 0){
        return -1;
    }
    if(renderer_clear(runtime) < 0){
        return -1;
    }
    return 0;  
}
SDL_Texture* loadTexture( const char* file_name,runtime_t* runtime)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( file_name );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", file_name, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( runtime->renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", file_name, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

int affichage_init(runtime_t *runtime){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0){ //SDL_INIT_AUDIO
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
    for(int i=0;i<NUMBER_TEXTURES;i++){
        runtime->textures[i] = SDL_CreateTexture(runtime->renderer, SDL_PIXELFORMAT_RGBA8888,  SDL_TEXTUREACCESS_STATIC, SIZE_TEXTURE_W, SIZE_TEXTURE_H);
        if(NULL == runtime->textures[i])
        {
            fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
            return -1;
        }
    }
    if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)!=(IMG_INIT_PNG|IMG_INIT_JPG)){
        printf("IMG_Init: Failed to init required png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        return -1;
    }
    return 0;
}
// void affiche_lvl(level_t *level)
// {
    
// }
void affichage_quit(runtime_t *runtime){
    for(int i=0;i<NUMBER_TEXTURES;i++){
        if(NULL != runtime->textures[i]){
            SDL_DestroyTexture(runtime->textures[i]);
        }
    }
    if(NULL != runtime->renderer){
        SDL_DestroyRenderer(runtime->renderer);
    }
    if(NULL != runtime->win){
        SDL_DestroyWindow(runtime->win);
    }
    SDL_Quit();
    free(runtime);
}

void affichage_texture(runtime_t *runtime,unsigned int texture_number,int X,int Y){
    SDL_Rect dest = {(int)X*SIZE_TEXTURE_W,(int)Y*SIZE_TEXTURE_H,(int)SIZE_TEXTURE_W,(int)SIZE_TEXTURE_H};
    SDL_RenderCopy(runtime->renderer, runtime->textures[texture_number], NULL, &dest);
}

void load_all_textures(runtime_t* runtime){
    runtime->textures[0]=loadTexture("data/textures/brick1.jpg",runtime);
    runtime->textures[1]=loadTexture("data/textures/caisse1.jpg",runtime);
    runtime->textures[2]=loadTexture("data/textures/perso1.png",runtime);
    runtime->textures[3]=loadTexture("data/textures/cible.png",runtime);
    runtime->textures[4]=loadTexture("data/textures/caisse2.jpg",runtime);
}
void show_game(runtime_t *runtime,level_t* level){
    gll_node_t *currNode = level->map->first;
    case_t * cell;
    for(unsigned int y=0;y<level->hauteur;y++){
        for(unsigned int x=0;x<level->largeur;x++){
            cell=(case_t*)currNode->data;
            switch (cell->bloc)
            {
                case 1:
                    affichage_texture(runtime,0,x,y);
                    break;
                case 2:
                    if(cell->cible){
                        affichage_texture(runtime,4,x,y);
                    }else{
                        affichage_texture(runtime,1,x,y);
                    }
                    break;
                case 3:
                    affichage_texture(runtime,2,x,y);
                    break;
                default:
                    if(cell->cible){
                        affichage_texture(runtime,3,x,y);
                    }
                    break;
            }
            currNode = currNode->next;
            if(currNode==NULL){
                break;
            }
        }
    }
}
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <unistd.h> 
#include <stdio.h>
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
int renderer_set_color(runtime_t *runtime,SDL_Color color);
int renderer_clear(runtime_t *runtime);
int renderer_setWindowColor(runtime_t *runtime,SDL_Color color);
SDL_Texture *loadTexture(const char *file_name,runtime_t *runtime);
int affichage_init(runtime_t *runtime);
void affichage_quit(runtime_t *runtime);
void affichage_texture(runtime_t *runtime,unsigned int texture_number,int X,int Y);
int load_music(runtime_t *runtime,const char *file_path);
void load_all_textures(runtime_t *runtime);
void show_game(runtime_t *runtime,level_t *level);

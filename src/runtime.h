#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#ifndef STRUCTURES_H
#include "structures.h"
#define STRUCTURES_H
#endif

/**
 * @brief structure qui stock tout ce qui fait parti de l'affichage
 * 
 */
typedef struct runtime_s {
  SDL_Window* win;        ///< fenetre (SDL2
  SDL_Renderer* renderer; ///< renderer pour afficher (SDL2)
  SDL_Texture* textures[NUMBER_TEXTURES]; ///< array de textures (SDL2)
  level_t* level; ///< pointeur vers le level en cours
  Mix_Music *musique; ///< musique (SDL2)
  SDL_Color empty;   ///< couleur de l'arriere plan (SDL2)
  bool QUIT_GAME;
  bool pathfinding;
  unsigned char direction;
  unsigned char texture_size;
} runtime_t;

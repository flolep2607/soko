#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
//? case  => case_t
//? map   => gll_t
//? coup  => coup_t
//? coups => gll_t
//? level => level_t
//? levels=> gll_t
#define NUMBER_TEXTURES 5
#define SIZE_TEXTURE_W 16
#define SIZE_TEXTURE_H 16

typedef struct runtime_s {
  SDL_Window* win;
  SDL_Renderer* renderer;
  SDL_Texture* textures[NUMBER_TEXTURES];
  Mix_Music *musique;
} runtime_t;

typedef struct Case
{
  unsigned char bloc; // 0->air 1->wall 2->box 3->body
  bool cible;
} case_t;

typedef struct Coups
{
  unsigned char direction;
  bool pousse;
} coup_t;

// typedef struct Levels {
//     level_t level;
//     struct Levels * next;
//     struct Levels * previous;
// } levels_t;

typedef struct node_t
{
  void *data;
  struct node_t *prev;
  struct node_t *next;
} gll_node_t;

/*
 * Generic Linked List Type: gll_t
 */
typedef struct
{
  unsigned int size;
  gll_node_t *first;
  gll_node_t *last;
} gll_t;

typedef struct Level
{
  gll_t *map;
  gll_t *coups; //? faire une pile simple pour prendre moins de place et moins complexe
  bool solved;
  unsigned int numero_lvl;
  unsigned int largeur;
  unsigned int hauteur;
  unsigned int index;
  unsigned int x;
  unsigned int y;
} level_t;

/*  create new list */
gll_t *gll_init();
level_t *level_init();
case_t* create_case(unsigned char bloc, bool cible);

/*  get/find functions */
void *gll_get(gll_t *, unsigned int);
void *gll_first(gll_t *);
void *gll_last(gll_t *);

/*  add functions */
unsigned int gll_add(gll_t *, void *, unsigned int);
void *gll_set(gll_t *, void *, unsigned int);
void gll_push(gll_t *, void *);
void gll_pushBack(gll_t *, void *);

/*  remove functions */
void *gll_remove(gll_t *, unsigned int);
void *gll_pop(gll_t *);
void *gll_popBack(gll_t *);

/*  iterate functions */
void gll_each(gll_t *, void (*f)(void *));
void gll_eachReverse(gll_t *, void (*f)(void *));

/*  destructive functions */
void gll_clear(gll_t *);
void gll_destroy(gll_t *);
void destroy_level(level_t* level);
void destroy_levels(gll_t *levels);

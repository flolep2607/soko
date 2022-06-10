#ifndef RUNTIME_H
#include "runtime.h"
#define RUNTIME_H
#endif
#ifndef PILE_H
#include "pile.h"
#define PILE_H
#endif
#ifndef AFFICHAGE_H
#include "affichage.h"
#define AFFICHAGE_H
#endif
#ifndef FILE_H
#include "file.h"
#define FILE_H
#endif
#ifndef MOVEMENT_H
#include "movement.h"
#define MOVEMENT_H
#endif
#ifndef PATHFINDING_H
#include "pathfinding.c"
#define PATHFINDING_H
#endif
bool event_handler(liste_double* levels,liste_double_node_t *level_node,runtime_t* runtime);
unsigned char ratio_finder(runtime_t* runtime);
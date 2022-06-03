#include <stdio.h>
#include <stdlib.h>
#ifndef LISTE_CHAINE
#include "../librairies/liste_chaine.c"
#define LISTE_CHAINE
#endif
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif

void affiche_lvl(node_t *head, unsigned int largeur_)
{
    node_t *current = head;
    unsigned int i = 0;
    while (current->next != NULL)
    {
        current = current->next;
        printf(current->data);
        if (i != 0 && i % largeur_ == 0)
        {
            printf("\n");
        }
        i++;
    }
    printf("\n");
}

node_t *read_map(FILE *flux_entree, unsigned int largeur_max)
{
    node_t *level = (node_t *)calloc(1, sizeof(node_t));
    char character;
    while (!feof(flux_entree) && character != ';')
    {
        character = fgetc(flux_entree);
        //? lit la ligne
        unsigned int i = 1;
        while (character != '\n')
        {
            switch (character)
            {
            case '#':
                push(&level, create_case(1, false), sizeof(case_t));
                break;
            case ' ':
                push(&level, create_case(0, false), sizeof(case_t));
                break;
            case '$':
                push(&level, create_case(2, false), sizeof(case_t));
                break;
            case '@':
                push(&level, create_case(3, false), sizeof(case_t));
                break;
            case '.':
                push(&level, create_case(0, true), sizeof(case_t));
                break;
            case '*':
                push(&level, create_case(2, true), sizeof(case_t));
                break;
            default:
                printf("Fichier corrompu\n");
                exit(-1);
                break;
            }
            character = fgetc(flux_entree);
            i++;
        }
        //? fill with void empty space
        while (i < largeur_max)
        {
            push(&level, create_case(0, false), sizeof(case_t));
            i++;
        }

        character = fgetc(flux_entree);
        if (character == '\r')
        {
            character = fgetc(flux_entree);
        }
    }
    return level;
}

int largeur(FILE *flux_entree)
{
    int largeur_max = 0;
    int a = 0;
    char caract = 0;
    while (!feof(flux_entree) && caract != ';')
    {
        caract = fgetc(flux_entree);
        while (!feof(flux_entree) && caract != '\n')
        {
            a++;
            if (a > largeur_max)
            {
                largeur_max = a;
            }
            caract = fgetc(flux_entree);
        }
        if (!feof(flux_entree))
        {
            caract = fgetc(flux_entree);
            if (caract == '\r')
            {
                caract = fgetc(flux_entree);
            }
            a = 1;
        }
    }
    return largeur_max;
}

node_t *read_file(void)
{
    FILE *flux_entree = fopen("./data/levels_test2.lvl", "r");
    if (flux_entree == NULL)
    {
        printf("Cannot open file\n");
        exit(-1);
    }
    int hauteur = 0;
    int longueur_max = 0;
    node_t *level = (node_t *)calloc(1, sizeof(node_t));
    int position_before_map = ftell(flux_entree);
    int largeur_max = largeur(flux_entree);
    //? READ MAP
    fseek(flux_entree, position_before_map, SEEK_SET);
}
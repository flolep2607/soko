#include <stdio.h>
#include <stdlib.h>
// #ifndef LISTE_CHAINE
// #include "../librairies/liste_chaine.c"
// #define LISTE_CHAINE
// #endif
#ifndef LEVEL_C
#include "../librairies/level.c"
#define LEVEL_C
#endif

// void affiche_lvl(gll_t *head, unsigned int largeur_)
// {
//     gll_t *current = head;
//     unsigned int i = 0;
//     while (current->next != NULL)
//     {
//         current = current->next;
//         printf(current->data);
//         if (i != 0 && i % largeur_ == 0)
//         {
//             printf("\n");
//         }
//         i++;
//     }
//     printf("\n");
// }


gll_t *read_map(FILE *flux_entree, unsigned int largeur_max)
{
    gll_t *map = gll_init();
    char character;
    while (!feof(flux_entree) && !ferror(flux_entree) )
    {
        //? lit la ligne
        unsigned int i = 0;
        while (!feof(flux_entree) && !ferror(flux_entree) && character != ';')
        {
            character = fgetc(flux_entree);
            if(i==0 && character==';'){
                fseek(flux_entree,-1,SEEK_CUR);
                return map;
            }else if (character=='\n'){
                break;
            }else if(character==EOF){
                return map;
            }
            // printf("%c",character);
            switch (character)
            {
            case '#':
                gll_pushBack(map, create_case(1, false));
                break;
            case ' ':
                gll_pushBack(map, create_case(0, false));
                break;
            case '$':
                gll_pushBack(map, create_case(2, false));
                break;
            case '@':
                gll_pushBack(map, create_case(3, false));
                break;
            case '.':
                gll_pushBack(map, create_case(0, true));
                break;
            case '*':
                gll_pushBack(map, create_case(2, true));
                break;
            case '\r':
                i--;
                break;
            default:
                printf("|%c|%d|",character,character);
                printf("Fichier corrompu\n");
                exit(-1);
                break;
            }
            i++;
        }
        //? fill with void empty space
        while (i < largeur_max)
        {
            // printf(".");
            gll_pushBack(map, create_case(0, false));
            i++;
        }
        // printf("\n");
    }
    return map;
}

unsigned int largeur(FILE *flux_entree)
{
    int position_before_map = ftell(flux_entree);
    unsigned int largeur_max = 0;
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
    fseek(flux_entree, position_before_map, SEEK_SET);
    return largeur_max;
}

bool remove_useless(FILE * flux_entree){
    if(fgetc(flux_entree)==';'){
        while(fgetc(flux_entree)!='\n'){}
        if(fgetc(flux_entree)!='\r'){
            fseek(flux_entree,-1,SEEK_CUR);
        }
        return true;
    }else{
        fseek(flux_entree,-1,SEEK_CUR);
        return false;
    }
}
int read_one_level(FILE * flux_entree,level_t* level){
    int level_number=-1;
    while(!feof(flux_entree) && fscanf(flux_entree,";LEVEL %d",&level_number)==0){
        fgetc(flux_entree);
    }
    // printf("Level number:%d\n",level_number);
    while(!feof(flux_entree) && fgetc(flux_entree)!='\n'){}
    if(fgetc(flux_entree)!='\r'){
        fseek(flux_entree,-1,SEEK_CUR);
    }
    //? enlever les commentaires et autre trucs inutiles
    while (remove_useless(flux_entree)){}
    //? READ MAP
    if(level_number==-1){
        return 0;
    }
    level->numero_lvl=level_number;
    int largeur_max = largeur(flux_entree);
    level->largeur=largeur_max;
    level->map=read_map(flux_entree,largeur_max);
    if(level->map->size<=0){
        printf("[ERROR] map size null");
        exit(-1);
    }
    level->hauteur=level->map->size/largeur_max;
    return 1;
}

gll_t *read_file(const char * file_name)
{
    FILE *flux_entree;
    flux_entree = fopen(file_name, "r");
    if (flux_entree == NULL){
        printf("Cannot open file\n");
        exit(-1);
    }
    printf("open file\n");
    gll_t * levels=gll_init();
    while(1){
        level_t* level = level_init();
        if(read_one_level(flux_entree,level)==1){
            gll_pushBack(levels,level);
        }else{
            destroy_level(level);
            break;
        }
    }
    fclose(flux_entree);
    return levels;
}

/*
numerolvlencours
largeur(uint)|hauteur(uint)|[map(uchar,bool)]|[coup(uchar,bool)]|numerolvl(uint)|resolu(bool)
*/
bool save_game(gll_t* levels,unsigned int current_level,const char *file_name){
    FILE *flux_sortie;
    flux_sortie = fopen(file_name, "wb");
    if (flux_sortie == NULL){
        printf("Cannot open save_file\n");
        exit(-1);
    }
    fprintf(flux_sortie,"%d\n",current_level);
    gll_node_t *currNode = levels->first;
    while(currNode != NULL) {
        level_t* level=(level_t*)currNode->data;
        
        fprintf(flux_sortie,"%hhu",level->largeur);
        fputc('|',flux_sortie);
        fprintf(flux_sortie,"%hhu",level->hauteur);
        fputc('|',flux_sortie);
        //! Save MAP
        gll_node_t *currNode_temp = (level->map)->first;
        while(currNode_temp != NULL) {
            case_t* cell=(case_t*)currNode_temp->data;
            fprintf(flux_sortie,"%hhu%i",cell->bloc,cell->cible);
            currNode_temp = currNode_temp->next;
        }
        fputc('|',flux_sortie);
        //! Save COUPS
        currNode_temp = (level->coups)->first;
        while(currNode_temp != NULL) {
            coups_t* coup=(coups_t*)currNode_temp->data;
            fprintf(flux_sortie,"%hhu%i",coup->direction,coup->pousse);
            currNode_temp = currNode_temp->next;
        }
        fputc('|',flux_sortie);
        fprintf(flux_sortie,"%hhu",level->numero_lvl);
        fputc('|',flux_sortie);
        fprintf(flux_sortie,"%i",level->resolue);

        currNode = currNode->next;
        fputc('\n',flux_sortie);
    }
    fclose(flux_sortie);
    return true;
}
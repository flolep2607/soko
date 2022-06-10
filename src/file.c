#include <stdio.h>
#include <stdlib.h>
#ifndef FILE_H
#include "file.h"
#define FILE_H
#endif

/**
 * @brief permet d'initialiser et de trouver la position du joueur en parcourant la liste chainee 
 (en reconstituant la position du joueur sur le tableau)
 * 
 * @param level 
 */
void find_human(level_t *level){
    unsigned int index=0;
    liste_double_node_t *current_node = level->map->first;
    while(current_node != NULL) {
        if(((case_t*)current_node->data)->bloc==3){
            level->index=index;
            return;
        }
        current_node = current_node->next;
        index++;
    }
    fprintf(stderr,"[ERROR] No human\n");
    exit(-1);
}


/**
 * @brief Fonction de creation / gestion des files
 *
 * @param flux_entree
 * @param largeur_max
 * @param map map qui va etre remplie
 */
void read_map(FILE *flux_entree, unsigned int largeur_max,liste_double *map)
{
    char character;
    while (!feof(flux_entree) && !ferror(flux_entree))
    {
        /**
        Lit la ligne tant que l'on ne rencontre pas un ';' qui indique la fin d'un plateau, gere les cas de retour a la ligne
        et de fin de fichier
        */
        unsigned int i = 0;
        while (!feof(flux_entree) && !ferror(flux_entree) && character != ';')
        {
            character = fgetc(flux_entree);
            if (i == 0 && character == ';')
            {
                fseek(flux_entree, -1, SEEK_CUR);
                return ;
            }
            else if (character == '\n')
            {
                break;
            }
            /**
             * @brief Construct a new switch object permettant d'associer chaque caractere du fichier source a un couple d'int et de booleen,
             le premier permettant de determiner le type du bloc, le second permettant de savoir si l'on se trouve sur une cible ou non
             *
             */
            switch (character)
            {
            case '#':
                liste_double_ajout_en_queue(map, create_case(1, false));
                break;
            case ' ':
                liste_double_ajout_en_queue(map, create_case(0, false));
                break;
            case '$':
                liste_double_ajout_en_queue(map, create_case(2, false));
                break;
            case '@':
                liste_double_ajout_en_queue(map, create_case(3, false));
                break;
            case '.':
                liste_double_ajout_en_queue(map, create_case(0, true));
                break;
            case '*':
                liste_double_ajout_en_queue(map, create_case(2, true));
                break;
            case '\r':
                i--;
                break;
            case EOF:
                if (i != 0)
                {
                    /**
                     * @brief Si on arrive a la fin du fichier, en ayant deja Remplissage de la liste chainee par des blocs vides pour completer les espaces vides pour que
                     le 'tableau'soit rectangulaire
                     *
                     */
                    while (i < largeur_max)
                    {
                        liste_double_ajout_en_queue(map, create_case(0, false));
                        i++;
                    }
                }
                return;
            default:
                fprintf(stderr,"Fichier corrompu |%c|%d|\n",character, character);
                exit(-1);
                break;
            }
            i++;
        }
        /**
        * @brief Remplissage de la liste chainee par des blocs vides pour completer les espaces vides pour que
        le 'tableau'soit rectangulaire
        *
        */
        while (i < largeur_max)
        {
            liste_double_ajout_en_queue(map, create_case(0, false));
            i++;
        }
    }
}
/**
 * @brief Fonction parcourant tout le niveau afin de deteriner la largeur maximale du niveau
 *
 * @param flux_entree
 * @return unsigned int largeur_max
 */
unsigned int largeur(FILE *flux_entree)
{
    unsigned long position_before_map = ftell(flux_entree);
    unsigned int largeur_max = 0;
    unsigned int a = 0;
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
/**
 * @brief enleve tous les commentaires sur le fichier source et se replace au debut
 *
 * @param flux_entree
 * @return booleen
 */
bool remove_useless(FILE *flux_entree)
{
    if (fgetc(flux_entree) == ';')
    {
        while (fgetc(flux_entree) != '\n')
        {
        }
        if (fgetc(flux_entree) != '\r')
        {
            fseek(flux_entree, -1, SEEK_CUR);
        }
        return true;
    }
    else
    {
        fseek(flux_entree, -1, SEEK_CUR);
        return false;
    }
}
/**
 * @brief Fonction permettant de lire un niveau dans le fichier source
 *
 * @param flux_entree
 * @param level
 * @return int
 */
int read_one_level(FILE *flux_entree, level_t *level)
{
    int level_number = -1;
    while (!feof(flux_entree) && fscanf(flux_entree, ";LEVEL %d", &level_number) == 0)
    {
        fgetc(flux_entree);
    }

    while (!feof(flux_entree) && fgetc(flux_entree) != '\n')
    {
    }
    if (fgetc(flux_entree) != '\r')
    {
        fseek(flux_entree, -1, SEEK_CUR);
    }
    /**
     * @brief enleve les commentaires et autre annotation inutile pour la lecture du niveau
     *
     */
    while (remove_useless(flux_entree))
    {
    }
    /**
     * @brief Lis les informations du niveau en associant le numero du niveau, la largeur max, la map du niveau
      a l'objet de classe level
     *
     */
    if (level_number == -1)
    {
        return 0;
    }

    level->lvl_number = level_number;
    int largeur_max = largeur(flux_entree);
    level->largeur = largeur_max;
    read_map(flux_entree, largeur_max,level->map);
    if (level->map->size <= 0)
    {
        fprintf(stderr,"[ERROR] map size null");
        exit(-1);
    }
    level->hauteur = level->map->size / largeur_max;
    find_human(level);
    return 1;
}
/**
 * @brief Fonction principale, permet de lire le fichier, et en utilisant les autres fonctions
 permet de retourner la liste chainee dans laquelle on a les differnets niveaux, au format desire
 *
 * @param file_name
 * @return levels, la liste chainee avec les niveaux remplis, au bon format
 */
liste_double *read_file(const char *file_name)
{
    FILE *flux_entree;
    bool end=false;
    flux_entree = fopen(file_name, "r");
    if (flux_entree == NULL)
    {
        fprintf(stderr,"Cannot open file\n");
        exit(-1);
    }
    liste_double *levels = liste_double_init();
    while(!end)
    {
        level_t *level = level_init();
        if (read_one_level(flux_entree, level) == 1)
        {
            liste_double_ajout_en_queue(levels, level);
        }
        else
        {
            level_destroy(level);
            end=true;
            break;
        }
    }
    fclose(flux_entree);
    return levels;
}

/**
 * @brief Fonction permettant la sauvegarde de la partie dans son etat actuel
 * Creer un fichier contenant les parametres qui pour chaque niveau se presente sous la forme :
 * largeur(uint)|hauteur(uint)|[map(uchar,bool)]|[coup(uchar,bool)]|numerolvl(uint)|resolu(bool) 
 *
 * @param levels
 * @param file_name
 * @return booleen accusant la sauvegarde ou non
 */
bool save_game(liste_double *levels, const char *file_name)
{
    FILE *flux_sortie;
    flux_sortie = fopen(file_name, "wb");
    if (flux_sortie == NULL)
    {
        fprintf(stderr,"Cannot open save_file\n");
        exit(-1);
    }
    liste_double_node_t *current_node = levels->first;
    while (current_node != NULL)
    {
        level_t *level = (level_t *)current_node->data;
        fwrite(&(level->largeur),sizeof(unsigned int),1,flux_sortie);
        fwrite(&(level->hauteur),sizeof(unsigned int),1,flux_sortie);
        liste_double_node_t *current_node_temp = (level->map)->first;
        while (current_node_temp != NULL)
        {
            case_t *cell = (case_t *)current_node_temp->data;
            fwrite(&(cell->bloc),sizeof(unsigned char),1,flux_sortie);
            fwrite(&(cell->cible),sizeof(bool),1,flux_sortie);
            current_node_temp = current_node_temp->next;
        }
        current_node_temp = (level->coups)->first;
        fwrite(&(level->coups->size),sizeof(unsigned int),1,flux_sortie);
        while (current_node_temp != NULL)
        {
            coup_t *coup = (coup_t *)current_node_temp->data;
            fwrite(&(coup->direction),sizeof(unsigned char),1,flux_sortie);
            fwrite(&(coup->pousse),sizeof(bool),1,flux_sortie);
            current_node_temp = current_node_temp->next;
        }
        fwrite(&(level->lvl_number),sizeof(unsigned int),1,flux_sortie);
        fwrite(&(level->solved),sizeof(bool),1,flux_sortie);
        current_node = current_node->next;
    }
    fclose(flux_sortie);
    return true;
}



/**
 * @brief Fonction lisant le fichier save.c pour reprendre la partie au point arrete.
 * Pour chaque niveau, la fonction a besoin de connaitre la largeur, la hauteur, la liste chainee contenant la specification 
   de la carte du niveau, ainsi que la liste des coups joues, le numero du niveau et un booleen pour savoir si il a etait resolu 
   ou non.
 *
 * @param file_name
 * @param levels
 * @return booleen (false si erreur de lecture du fichier ou pas de fichier, true sinon)
 */
bool read_save(const char *file_name, liste_double *levels)
{
    unsigned int i;
    unsigned char bloc=0;
    unsigned int largeur,hauteur;
    bool cible=0;
    unsigned int size_coups=0;
    FILE *flux_entree;
    level_t * level;
    flux_entree = fopen(file_name, "rb");
    liste_double_vider(levels,true);
    if (flux_entree == NULL)
    {
        printf("Cannot open save_file\n");
        exit(-1);
    }
    while (!feof(flux_entree))
    {
        level = level_init();
        if(fread(&(level->largeur), sizeof(unsigned int), 1, flux_entree)!=1){
            printf("finish read save\n");
            level_destroy(level);
            break;
        }
        fread(&(level->hauteur),sizeof(unsigned int),1,flux_entree);
        // level->largeur=largeur;
        // level->hauteur=hauteur;
        i=0;
        while (i<level->hauteur*level->largeur)
        {
            fread(&bloc,sizeof(unsigned char),1,flux_entree);
            fread(&cible,sizeof(bool),1,flux_entree);
            // printf("%d-%d\n",bloc,cible); GOOD
            liste_double_ajout_en_queue(level->map, create_case(bloc,cible));
            i++;
        }
        i=0;
        fread(&(size_coups),sizeof(unsigned int),1,flux_entree);
        while (i<size_coups)
        {
            fread(&bloc,sizeof(unsigned char),1,flux_entree);
            fread(&cible,sizeof(bool),1,flux_entree);
            liste_double_ajout_en_queue(level->coups, create_coup(bloc,cible));
            i++;
        }
        fread(&(level->lvl_number),sizeof(unsigned int),1,flux_entree);
        fread(&(level->solved),sizeof(bool),1,flux_entree);
        liste_double_ajout_en_queue(levels, level);
    }
    return true;
}

void save_coups(liste_double* coups,int level_number){
    if(coups->size==0){
        return;
    }
    FILE *flux_sortie;
    char file_name[40];
    sprintf(file_name,"data/soluce/%d.txt",level_number);
    flux_sortie = fopen(file_name, "wb");
    liste_double_node_t *current_node = coups->first;
    fprintf(flux_sortie,"Coups:%d Poussées:%d\n",coups->size,somme_poussees(coups));
    printf("Coups:%d Poussées:%d\n",coups->size,somme_poussees(coups));
    while(current_node != NULL) {
        switch (((coup_t*)current_node->data)->direction)
        {
            case HAUT:
                fprintf(flux_sortie,"HAUT\n");
                break;
            case BAS:
                fprintf(flux_sortie,"BAS\n");
                break;
            case DROITE:
                fprintf(flux_sortie,"DROITE\n");
                break;
            case GAUCHE:
                fprintf(flux_sortie,"GAUCHE\n");
                break;
            default:
                break;
        }
        current_node = current_node->next;
    }
    fclose(flux_sortie);
}
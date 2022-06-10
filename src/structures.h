#define NUMBER_TEXTURES 6
#define SIZE_TEXTURE 64
#define AIR  0
#define WALL 1
#define BOX  2
#define BODY 3

#define HAUT 0
#define BAS 1
#define DROITE 2
#define GAUCHE 3

/**
 * @brief créer la structure node_t qui permet de créer une liste chainée de avec n'importe quel type de données.
 * 
 */
typedef struct node_t
{
  void *data;
  struct node_t *prev;
  struct node_t *next;
} liste_double_node_t;

/*
 * Generic Linked liste Type: liste_double
 */
typedef struct
{
  unsigned int size;
  liste_double_node_t *first;
  liste_double_node_t *last;
} liste_double;

/**
 * @struct level_t
 * @brief Créer la structure Level qui permet de spécifier un niveau en entier.
 Spécifie la construction de la map (tout les blocs présent et où ils se trouvent)
 Spécifie aussi la liste des coups jouées sous la forme d'une liste chainée.
 Spécifie enfin le numéro du niveau, la largeur du niveau, la hauteur du niveau, si le niveau a était résolu ou non, 
 l'index du maillon ou se trouve le joueur dans la liste chainée map et les coordonnées x et y du joueur dans le niveau
 */
typedef struct Level
{
  liste_double *map; ///< liste formant la map
  liste_double *coups; ///< pile de coups
  bool solved;
  unsigned int lvl_number;
  unsigned int largeur;
  unsigned int hauteur;
  unsigned int index;
} level_t;


/**
 * @brief créer la structure Case qui spécifie le type de chaque case d'un niveau. 
Spécifie le type de bloc, la présence d'une cible ou non et le poids (sert pour le pathfinding)
 * 
 */
typedef struct Case
{
  unsigned char bloc; // 0->air 1->wall 2->box 3->body
  bool cible;
  bool weight;
} case_t;
/**
 * @brief créer la structure Coups qui spécifie le type des Coups effectués.
 Spécifie la direction du coup et si il s'agit d'une poussée ou non.
 * 
 */
typedef struct Coup
{
  unsigned char direction;
  bool pousse;
} coup_t;
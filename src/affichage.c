#ifndef AFFICHAGE_H
#include "affichage.h"
#define AFFICHAGE_H
#endif

/**
 * @brief permet l'affichage et le bon rendu des couleurs
 * 
 * @param runtime 
 * @param color 
 * @return int ; -1 si erreur, 0 sinon
 */
int renderer_set_color(runtime_t *runtime,SDL_Color color){
    if(0 != SDL_SetRenderDrawColor(runtime->renderer, color.r, color.g, color.b, color.a))
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

/**
 * @brief efface le contenu de la fenetre
 * 
 * @param runtime 
 * @return int 
 */
int renderer_clear(runtime_t *runtime){
    if(0 != SDL_RenderClear(runtime->renderer))
    {
        fprintf(stderr, "Erreur SDL_RenderClear : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

/**
 * @brief verifie que les rendus pour la fenetre est correcte
 * 
 * @param runtime 
 * @param color 
 * @return int 
 */
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

/**
 * @brief permet d'effacer les elements affiches sur une fenetre
 * 
 * @param runtime 
 * @return int 
 */
int renderer_clear_window(runtime_t *runtime)
{
    return renderer_setWindowColor(runtime, runtime->empty);
}

/**
 * @brief charge les textures pour 
 * 
 * @param file_name 
 * @param runtime 
 * @return SDL_Texture* 
 */
SDL_Texture* loadTexture( const char* file_name,runtime_t* runtime)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( file_name );
    if( loadedSurface == NULL )
    {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", file_name, IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( runtime->renderer, loadedSurface );
        if( newTexture == NULL )
        {
            fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", file_name, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

/**
 * @brief initialise tout les drivers de la SDL
 * 
 * @param runtime 
 * @return true 
 * @return false 
 */
bool affichage_init(runtime_t *runtime){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0){ //SDL_INIT_AUDIO
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return false;
    }
    runtime->win = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if(NULL == runtime->win)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return false;
    }
    runtime->renderer = SDL_CreateRenderer(runtime->win, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == runtime->renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return false;
    }
    // for(int i=0;i<NUMBER_TEXTURES;i++){
    //     runtime->textures[i] = SDL_CreateTexture(runtime->renderer, SDL_PIXELFORMAT_RGBA8888,  SDL_TEXTUREACCESS_STATIC, SIZE_TEXTURE, SIZE_TEXTURE);
    //     if(NULL == runtime->textures[i])
    //     {
    //         fprintf(stderr, "Erreur SDL_CreateTexture : %s", SDL_GetError());
    //         return false;
    //     }
    // }
    if(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)!=(IMG_INIT_PNG|IMG_INIT_JPG)){
        fprintf(stderr,"Erreur IMG_Init : %s\n", IMG_GetError());
        return false;
    }
    if(TTF_Init()){
        fprintf(stderr,"Erreur TTF_INIT : %s\n", TTF_GetError());
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        fprintf(stderr,"Erreur Mix_OpenAudio :%s\n", Mix_GetError());
        return false;
    }
    load_music(runtime,"data/sounds/8bit.mp3");
    return true;
}


/**
 * @brief arrete le rendu visuel, ferme la fenetre, arrete la musique
 * 
 * @param runtime 
 */
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
    if(NULL != runtime->musique){
        Mix_FreeMusic(runtime->musique); //Liberation de la musique
        Mix_CloseAudio(); //Fermeture de l'API
    }
    SDL_Quit();
    free(runtime);
}

/**
 * @brief charge et affiche les textures du jeu
 * 
 * @param runtime 
 * @param texture_number 
 * @param X 
 * @param Y 
 */
void affichage_texture(runtime_t *runtime,unsigned int texture_number,int X,int Y){
    SDL_Rect dest = {(int)X*SIZE_TEXTURE,(int)Y*SIZE_TEXTURE,(int)SIZE_TEXTURE,(int)SIZE_TEXTURE};
    SDL_RenderCopy(runtime->renderer, runtime->textures[texture_number], NULL, &dest);
}

/**
 * @brief charge les fichiers audio, erreur si pas de musique, et joue indefiniement la musique
 * 
 * @param runtime 
 * @param file_path 
 * @return int 
 */
int load_music(runtime_t* runtime,const char * file_path){
    runtime->musique = Mix_LoadMUS(file_path); //Chargement de la musique
    if(runtime->musique==NULL){
        printf("[ERROR] loading mp3 file %s",file_path);
        return -1;
    }
    Mix_PlayMusic(runtime->musique, -1); //Jouer infiniment la musique
    return 0;
}
/**
 * @brief ecrit du texte dans la fenetre SDL
 * 
 * @param runtime 
 * @param text 
 */
void print_text(runtime_t* runtime,char * text){
    //this opens a font style and sets a size
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 30);

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text,(SDL_Color ){0, 0, 0,255}); 

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(runtime->renderer, surfaceMessage);

    SDL_Rect Message_rect= {0,0,100,100}; //create a rect
    SDL_RenderCopy(runtime->renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

/**
 * @brief charge les differentes textures a afficher
 * 
 * @param runtime 
 */
void load_all_textures(runtime_t* runtime){
    runtime->textures[0]=loadTexture("data/textures/brick1.png",runtime);  
    runtime->textures[1]=loadTexture("data/textures/caisse3.png",runtime); 
    runtime->textures[2]=loadTexture("data/textures/perso2.png",runtime);  
    runtime->textures[3]=loadTexture("data/textures/cible2.png",runtime);  
    runtime->textures[4]=loadTexture("data/textures/caisse4.png",runtime); 
    runtime->textures[5]=loadTexture("data/textures/brick2.png",runtime);  
}

/**
 * @brief charge et affiche le plateau de jeu, et affiche les textures
 * 
 * @param runtime 
 */
void show_game(runtime_t *runtime){
    renderer_clear_window(runtime);
    int max_x,max_y;
    unsigned int index=0;
    unsigned int x,y;
    case_t * cell;
    // char title[256];
    SDL_GetWindowSize(runtime->win,&max_x,&max_y);
    max_x=(unsigned int)(max_x*1.1)/runtime->texture_size;max_y=(unsigned int)(max_y*1.1)/runtime->texture_size;
    liste_double_node_t *current_node = runtime->level->map->first;
    while(current_node != NULL) {
        x=x2x(index,runtime->level->largeur);
        y=x2y(index,runtime->level->largeur);
        if((int)x<max_x && (int)y<max_y){
            cell=(case_t*)current_node->data;
            /**
             * @brief gere les differentes textures a afficher selon la situation rencontree
             * 
             */
            switch (cell->bloc)
            {
                case WALL:
                    if(rand() % 10000 < 1){
                        affichage_texture(runtime,5,x,y);
                    }else{
                        affichage_texture(runtime,0,x,y);
                    }
                    break;
                case BOX:
                    if(cell->cible){
                        affichage_texture(runtime,4,x,y);
                    }else{
                        affichage_texture(runtime,1,x,y);
                    }
                    break;
                case BODY:
                    if(cell->cible){
                        affichage_texture(runtime,3,x,y);
                    }
                    affichage_texture(runtime,2,x,y);
                    break;
                default:
                    if(cell->cible){
                        affichage_texture(runtime,3,x,y);
                    }
                    break;
            }
        }
        index++;
        current_node = current_node->next;  
    }
    
}
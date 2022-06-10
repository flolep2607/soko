#ifndef GAME_H
#include "game.h"
#define GAME_H
#endif


/**
 * @brief Permet d'effectuer un zoom en prenant en parametre la valeur pour effectuer le rapport du zoom
 * 
 * @param zoom 
 * @return float 
 */
float zoomer(unsigned char zoom){
    return (float)zoom/SIZE_TEXTURE;
}

/**
 * @brief Change le zoom dans la fenetre en appelant la fonction "zoomer"
 * 
 * @param runtime 
 */
void update_zoom(runtime_t* runtime){
    SDL_RenderSetScale(runtime->renderer,zoomer(runtime->texture_size),zoomer(runtime->texture_size));
    show_game(runtime);
}

/**
 * @brief Reagit des qu'on agit sur une touche parmi la liste de touche : echap,+ et -.
 * 
 * @param runtime 
 * @param event 
 * @return int 
 */
static int SDLCALL quit_filter(void *runtime, SDL_Event *event)
{
    runtime_t *runtime_ = (runtime_t *)runtime;
    switch (event->type)
    {
    case SDL_WINDOWEVENT:
        if(event->window.event == SDL_WINDOWEVENT_RESIZED){
            show_game(runtime_);
            return 0;
        }
        return 1;
    case SDL_QUIT:
        runtime_->QUIT_GAME = true;
        break;
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_SPACE:
            runtime_->pathfinding = false;
            return 0;
            break;
        case SDLK_KP_PLUS:
            printf("size texture:%d\n", runtime_->texture_size);
            if (runtime_->texture_size < SIZE_TEXTURE * 2)
            {
                runtime_->texture_size++;
                update_zoom(runtime_);
            }
            printf("size texture:%d\n", runtime_->texture_size);
            return 0;
            break;
        case SDLK_KP_MINUS:
            printf("size texture:%d\n", runtime_->texture_size);
            if (runtime_->texture_size > 2)
            {
                runtime_->texture_size--;
                update_zoom(runtime_);
            }
            printf("size texture:%d\n", runtime_->texture_size);
            return 0;
            break;
        default:
            break;
        }
    default:
        break;
    }
    return 1; // let all events be added to the queue since we always return 1.
}

/**
 * @brief definie la taille des blocs pour qu'ils rentrent dans la fenetre sans etre trop grand.
 * 
 * @param runtime 
 * @return unsigned char 
 */
unsigned char ratio_finder(runtime_t* runtime){
    int h=0;
    int w=0;
    SDL_GetWindowSize(runtime->win,&w,&h);
    unsigned char a=w/runtime->level->largeur;
    unsigned char b=h/runtime->level->hauteur;
    if(a<=2 && b<=2){
        return 2;
    }
    if(a>b){
        return b;
    }
    return a;
}
void refresh_screen(runtime_t* runtime,int x,int y){
    renderer_clear_window(runtime);
    show_game(runtime);
    SDL_Rect rect = {x*SIZE_TEXTURE, y*SIZE_TEXTURE, SIZE_TEXTURE, SIZE_TEXTURE};
    renderer_set_color(runtime,(SDL_Color){255,0,0,255});
    SDL_RenderFillRect(runtime->renderer, &rect); 
    SDL_RenderPresent(runtime->renderer);
    SDL_Delay(20);
    SDL_PumpEvents();
}

/**
 * @brief Reagis aux actions des touches pendant qu'il n'y a pas d'action en cours.
 * 
 * @param levels 
 * @param level_node position dans la liste des levels
 * @param runtime 
 * @return bool
 */
bool event_handler(liste_double* levels,liste_double_node_t *level_node,runtime_t* runtime){
    SDL_Event event;
    char title[256];
    if(SDL_WaitEventTimeout(&event,20)){
        switch (event.type)
        {
        case SDL_QUIT:
            runtime->QUIT_GAME = true;
            return false;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_RIGHT){
                unsigned int x=event.button.x/runtime->texture_size;
                unsigned int y=event.button.y/runtime->texture_size;
                path_finding(runtime->level,x,y,runtime,refresh_screen);
            }
            return true;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    runtime->QUIT_GAME = true;
                    return false;
                case SDLK_z:
                case SDLK_UP:
                    move_human(runtime->level,HAUT,true,true,runtime);
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    move_human(runtime->level,BAS,true,true,runtime);
                    break;
                case SDLK_q:
                case SDLK_LEFT:
                    move_human(runtime->level,GAUCHE,true,true,runtime);
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    move_human(runtime->level,DROITE,true,true,runtime);
                    break;
                case SDLK_BACKSPACE:
                    if(!go_back(runtime->level,runtime)){
                        fprintf(stderr,"[INFO] go_back empty or error \n");
                        return false;
                    }
                    // printf("REVERSE\n");
                    break;
                case SDLK_r:
                    go_all_back(runtime->level,runtime);
                    // printf("REVERSED\n");
                    break;
                case SDLK_g:
                    save_game(levels,"data/save.bin");
                    printf("SAVED\n");
                    break;
                case SDLK_n:
                    liste_double_vider(runtime->level->coups,false);
                    runtime->level->solved=true;
                    // printf("SKIP\n");
                    break;
                case SDLK_l:
                    read_save("data/save.bin",levels);
                    level_node=levels->first;
                    runtime->level=(level_t *)level_node->data;
                    runtime->texture_size=ratio_finder(runtime);
                    sprintf(title, "Level %d", runtime->level->lvl_number);
                    SDL_SetWindowTitle(runtime->win,title);
                    update_zoom(runtime);
                    return true;
                default:
                    return false;
            }
            return true;
        default:
            return false;
        }
    }
    return false;
}

int main(void){
    SDL_Color empty = {0, 108, 248, 255};
    runtime_t* runtime = (runtime_t*)malloc(sizeof(runtime_t));
    runtime->QUIT_GAME=false;
    runtime->pathfinding=false;
    runtime->texture_size=SIZE_TEXTURE;
    runtime->empty=empty;
    runtime->direction=DROITE;
    liste_double* levels = read_file("data/levels_offficiel.lvl");//"data/hugemap.lvl");
    liste_double_node_t* level_node=levels->first;
    // level_t* level = (level_t*)level_node->data;
    runtime->level=(level_t*)level_node->data;
    char title[256];
    SDL_AddEventWatch(quit_filter, runtime);
    sprintf(title, "Level %d", runtime->level->lvl_number);
    if(!affichage_init(runtime)){
        goto Quit;
    }
    if(renderer_setWindowColor(runtime,empty)<0){
        goto Quit;
    }
    runtime->musique=NULL;
    load_all_textures(runtime);
    runtime->texture_size=ratio_finder(runtime);
    update_zoom(runtime);
    SDL_SetWindowTitle(runtime->win,title);
    while(!runtime->QUIT_GAME){
        if(event_handler(levels,level_node,runtime)){
            show_game(runtime);
        }
        SDL_RenderPresent(runtime->renderer);
        if(runtime->level->solved && level_node->next!=NULL){
            save_coups(runtime->level->coups,runtime->level->lvl_number);
            level_node=level_node->next;
            runtime->level=(level_t*)level_node->data;
            runtime->texture_size=ratio_finder(runtime);
            sprintf(title, "Level %d", runtime->level->lvl_number);
            SDL_SetWindowTitle(runtime->win,title);
            update_zoom(runtime);
        }
    }
Quit:
    levels_destroy(levels);
    affichage_quit(runtime);
    return 0;
}
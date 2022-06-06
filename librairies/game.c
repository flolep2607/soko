#ifndef GAME_H
#include "game.h"
#define GAME_H
#endif

bool QUIT_GAME=false;
void event_handler(level_t* level){
    SDL_Event event;
    if(SDL_WaitEventTimeout(&event,20)){
        switch (event.type)
        {
        case SDL_QUIT:
            QUIT_GAME = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    move_human(level,HAUT,true);
                    printf("UP\n");
                    break;
                case SDLK_DOWN:
                    move_human(level,BAS,true);
                    printf("DOWN\n");
                    break;
                case SDLK_LEFT:
                    move_human(level,GAUCHE,true);
                    printf("LEFT\n");
                    break;
                case SDLK_RIGHT:
                    move_human(level,DROITE,true);
                    printf("RIGHT\n");
                    break;
                case SDLK_BACKSPACE:
                    if(!go_back(level)){
                        printf("[INFO] go_back empty or error \n");
                    }
                    printf("REVERSE\n");
                    break;
                default:
                    break;
            }
            level->solved=is_finish(level->map);
            if(level->solved){
                for(int i=0;i<10;i++){
                    printf("WIN\n");
                }
            }
            break;
        default:
            break;
        }
    }
}
int main(void){
    SDL_Color empty = {0, 108, 248, 255};
    runtime_t* runtime = (runtime_t*)malloc(sizeof(runtime_t));
    gll_t* levels = read_file("data/levels_offficiel.lvl");
    gll_node_t* level_node=levels->first;
    level_t* level = (level_t*)level_node->data;
    if(affichage_init(runtime)<0){
        goto Quit;
    }
    if(renderer_setWindowColor(runtime,empty)<0){
        goto Quit;
    }
    if(load_music(runtime,"./data/souds/Chainaw.mp3")<0){
        goto Quit;
    }
    // SDL_RenderFillRect(runtime->renderer, &rect);
    load_all_textures(runtime);
    // for(int i=0;i<=4;i++){
    //     SDL_RenderCopy(runtime->renderer, runtime->textures[i], NULL, &dst);
    //     dst.x+=SIZE_TEXTURE_W;
    // }
    while(!QUIT_GAME){
        event_handler(level);
        renderer_setWindowColor(runtime,empty);
        show_game(runtime,level);
        SDL_RenderPresent(runtime->renderer);
        if(level->solved && level_node->next!=NULL){
            level_node=level_node->next;
            level=(level_t*)level_node->data;
        }
        // printf("refreshed renderer\n");
    }
    
    // SDL_Delay(10000);
Quit:
    affichage_quit(runtime);
    destroy_levels(levels);
    return 0;
}
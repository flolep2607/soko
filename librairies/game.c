#include "movement.c"
#include "affichage.c"

void event_handler(level_t* level){
    SDL_Event event;
    if(SDL_WaitEventTimeout(&event,20)){
        switch (event.type)
        {
        case SDL_QUIT:
            QUIT_GAME = SDL_TRUE;
            break;
        case SDL_KEYDOWN:
            unsigned char direction=0;
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    move_human(level,HAUT);
                    printf("UP\n");
                    break;
                case SDLK_DOWN:
                    move_human(level,BAS);
                    printf("DOWN\n");
                    break;
                case SDLK_LEFT:
                    move_human(level,GAUCHE);
                    printf("LEFT\n");
                    break;
                case SDLK_RIGHT:
                    move_human(level,DROITE);
                    printf("RIGHT\n");
                    break;
                default:
                    break;
            }
            
            break;
        default:
            break;
        }
    }
}
int main(void){
    SDL_Rect rect = {100, 100, 100, 100};
    SDL_Color empty = {0, 108, 248, 255};
    runtime_t* runtime = (runtime_t*)malloc(sizeof(runtime_t));
    gll_t* levels = read_file("data/levels_offficiel.lvl");
    level_t* level = (level_t*)levels->first->data;
    if(affichage_init(runtime)<0){
        goto Quit;
    }
    if(renderer_setWindowColor(runtime,empty)<0){
        goto Quit;
    }
    renderer_setWindowColor(runtime,empty);
    // SDL_RenderFillRect(runtime->renderer, &rect);
    load_all_textures(runtime);
    // for(int i=0;i<=4;i++){
    //     SDL_RenderCopy(runtime->renderer, runtime->textures[i], NULL, &dst);
    //     dst.x+=SIZE_TEXTURE_W;
    // }
    while(!QUIT_GAME){
        event_handler(level);
        show_game(runtime,level);
        SDL_RenderPresent(runtime->renderer);
        // printf("refreshed renderer\n");
    }
    
    // SDL_Delay(10000);
Quit:
    affichage_quit(runtime);
    return 0;
}
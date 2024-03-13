#include "common_func.h"
#include "BaseObject.h"
#include "game_map.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

BaseObject gBackground;
GameMap gMap;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        gWindow = SDL_CreateWindow("fireboy and watergirl", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1")) printf("Wanrning: SDL_GetError: %s\n", SDL_GetError());
        if (gWindow == NULL){
            printf("SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) printf("SDL_Error: %s\n", SDL_GetError());
            else{
                SDL_SetRenderDrawColor(gRenderer,255,255,255,0.8);
            }
            int FlagImg = IMG_INIT_JPG;
            if (!(FlagImg & IMG_Init(FlagImg))){
                printf("IMG_Error: %s\n", IMG_GetError());
                success = false;
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    gMap.LoadMap("map_demo.txt");
    gMap.LoadTiles(gRenderer);

    return success;
}
void close()
{
    gBackground.~BaseObject();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}
int main(int argc, char* args[])
{
    if (!init()) return -1;
    else{
        if (!loadMedia()) return -1;
        else{
            bool quit = false;
            SDL_Event event;
            while (!quit){
                while (SDL_PollEvent(&event) != 0){
                    if (event.type == SDL_QUIT) quit = true;
                }
                //Update screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0.8);
                SDL_RenderClear(gRenderer);
                gMap.Drawmap(gRenderer);
                SDL_RenderPresent(gRenderer);
            }

        }
    }
    close();
    return 0;
}

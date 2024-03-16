#include "common_func.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainCharact.h"
#include "timer.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

BaseObject gBackground;
GameMap gMap;
MainObject Water(0,0);
MainObject Fire(0,64);
LTimer fps_timer;

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
    gMap.LoadMap("Data/map/update_map_easy.txt");
    gBackground.loadImg("Data/photo/background/background.png",gRenderer);
    gMap.LoadTiles(gRenderer);
    Water.loadImg("Data/photo/character/water_girl_stand.png", gRenderer);
    Water.set_clips();
    Fire.loadImg("Data/photo/character/fire_boy_stand.png", gRenderer);
    Fire.set_clips();
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
                fps_timer.start();
                while (SDL_PollEvent(&event) != 0){
                    if (event.type == SDL_QUIT) quit = true;
                    Fire.HandleInputAction(event, gRenderer, FIRE_BOY);
                    Water.HandleInputAction(event, gRenderer, WATER_GIRL);

                }
                //Update screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0.8);
                SDL_RenderClear(gRenderer);
                gBackground.Render(gRenderer, NULL);
                gMap.Drawmap(gRenderer);

                Map map_data = gMap.getMap();
                Fire.DoPlayer(map_data);
                Fire.Show(gRenderer);

                Water.DoPlayer(map_data);
                Water.Show(gRenderer);
                SDL_RenderPresent(gRenderer);

                int frameTicks = fps_timer.get_ticks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME){
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
                }
                cout << "real time" << frameTicks << std::endl;
                cout << " time standard" << SCREEN_TICKS_PER_FRAME << std::endl;
            }
        }
    }
    close();
    return 0;
}

#include "header.h"
#include "character.h"
#include "game_map.h"
#include "button.h"
#include "texture.h"
#include "timer.h"
#include "object_button.h"
#include "enermy.h"
#include "text.h"
#include "select_menu.h"

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static TTF_Font* gFont = NULL;

LTexture gBackground;

GameMap gMap;

MainObject Water;
MainObject Fire;
vector<Object> obj;
vector<Enermy> enemy;

LTimer fps_timer;
Text time_count;

bool on_button = false;

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
            if (TTF_Init() == -1){
                cout << "can't init ttf\n";
                success = false;
            }
        }
    }

    //set font_renderer
    gFont = TTF_OpenFont("Data/font/Mario-Party-Hudson-Font.ttf", 30);
    if (gFont == NULL){
        success = false;
        cout << "can't open font\n";
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    //load background
    gBackground.loadFromFile("Data/photo/background/brick_background.png",gRenderer);

    //load watergirl character
    Water.loadFromFile("Data/photo/character/water_girl_stand.png", gRenderer);
    Water.set_clips();

    //load fireboy character
    Fire.loadFromFile("Data/photo/character/fire_boy_stand.png", gRenderer);
    Fire.set_clips();

    return success;
}
void close()
{
    gBackground.~LTexture();
    Fire.~LTexture();
    Water.~LTexture();


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

            int startTime = 0;

            std::stringstream timeText;

            string path_map = LevelMap(Fire, Water, obj, enemy); //set map link
            cout << path_map << std::endl;
            gMap.LoadMap(path_map);
            gMap.LoadTiles(gRenderer);
            Map map_data = gMap.getMap();

            while (!quit){
                fps_timer.start();
                while (SDL_PollEvent(&event) != 0){ //event click quit and key related to main character
                    if (event.type == SDL_QUIT) quit = true;
                    Fire.HandleInputAction(event, gRenderer, FIREBOY);
                    Water.HandleInputAction(event, gRenderer, WATERGIRL);

                }
                //time counting
                timeText.str("");
                timeText << "TIME: " << set_standard_time( SDL_GetTicks() - startTime );
                time_count.setText(timeText.str());
                //set color for time_count
                time_count.setTextColor(WHITE_TEXT);

                //Update screen
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0.8);
                SDL_RenderClear(gRenderer);

                //render background
                gBackground.render(0,0, NULL, gRenderer);
                //render map
                gMap.DrawMap(gRenderer);
                gMap.copyMap(map_data);
                //render barrier and button
                for (int i = 0; i < int(obj.size()); i++){
                    obj[i].render(gRenderer);
                }

                //main character
                Fire.DoPlayer(map_data,FIREBOY);
                SDL_Rect FireRect = Fire.getRectChar();
                Fire.Show(gRenderer);

                Water.DoPlayer(map_data,WATERGIRL);
                SDL_Rect WaterRect = Water.getRectChar();
                Water.Show(gRenderer);

                //enemy and check collision of it
                SDL_Rect enemy_rect[int(enemy.size())];
                for (int i = 0; i < int(enemy.size()); i++){
                    enemy[i].DoPlayer(map_data);
                    enemy[i].controlMoving(gRenderer, "Data/photo/character/red_slime.png", "Data/photo/character/red_slime.png");
                    enemy[i].Show(gRenderer);
                    enemy_rect[i] = enemy[i].get_current_pos();
                    if ( check_collision(FireRect, enemy_rect[i]) || check_collision(WaterRect, enemy_rect[i]) ) cout << "lose \n"; //check xem neu cham vao co lose khong
                }

                //check collision of button
                for (int i = 0; i < int(obj.size()); i++){
                    SDL_Rect button = obj[i].getButRect();

                    if (check_collision(FireRect,button) || check_collision(WaterRect,button)){
                        on_button = true;
                    }
                    else{
                        on_button = false;
                    }

                    //activity related to button, barrier and character
                    obj[i].activity(Fire,on_button);
                    obj[i].activity(Water,on_button);
                }


                //render time_count
                if ( ! time_count.CreateGameText(gFont, gRenderer, ( SCREEN_WIDTH - time_count.getWidth() ) / 2, 0 ) ) {
                    cout << "can't create time count !\n";
                }

                SDL_RenderPresent(gRenderer); //show to screen

                //set fps
                int frameTicks = fps_timer.get_ticks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME){
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);

                }

                cout << "score of fireboy: " << Fire.get_coin() << std::endl;
                cout << "score of watergirl: " << Water.get_coin() << std::endl;
            }
        }
    }
    close();
    return 0;
}

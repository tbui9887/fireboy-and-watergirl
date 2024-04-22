#include "header.h"
#include "character.h"
#include "game_map.h"
#include "texture.h"
#include "timer.h"
#include "object_button.h"
#include "enermy.h"
#include "text.h"
#include "select_menu.h"

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static TTF_Font* gFont = NULL;

Mix_Music* gMusic = NULL;
Mix_Chunk *death = NULL;

LTexture gBackground;

GameMap gMap;

MainObject Water;
MainObject Fire;
vector<Object> obj;
vector<Enemy> enemies_list;


LTimer fps_timer;
Text time_count;
Text water_coin;
Text fire_coin;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
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
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 2048) < 0){
                cout << "error in mix_openaudio: " << Mix_GetError() << std::endl;
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
    gBackground.loadFromFile("Data/photo/background/background.png",gRenderer);

    //load watergirl character
    Water.loadFromFile("Data/photo/character/water_girl_stand.png", gRenderer);
    Water.set_clips();

    //load fireboy character
    Fire.loadFromFile("Data/photo/character/fire_boy_stand.png", gRenderer);
    Fire.set_clips();

    //load music
    gMusic = Mix_LoadMUS("Data/sound/Fireboy and Watergirl Playthrough Soundtrack.mp3");
    if (gMusic == NULL){
        cout << "Error loading music: " << Mix_GetError() << endl;
        success = false;
    }
    else {
        cout << "Music loaded successfully!" << endl;
    }
    death = Mix_LoadWAV("Data/sound/Death.wav");
    if (death == NULL){
        cout << "Error loading sound effect: " << Mix_GetError() << endl;
        success = false;
    }
    else {
        cout << "Sound effect loaded successfully!" << endl;
    }

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

    //free music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;

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
            int ReturnMenu = -1;
            std::stringstream timeText;
            string path_map;
            int startTime = 0;
            SDL_Event event;
            int ret_menu = ShowMenuStartOrNot(Fire, Water, obj, enemies_list, gRenderer, event, path_map, quit);

            while (1){
                if (ReturnMenu == 1){
                    ret_menu = ShowMenuStartOrNot(Fire, Water, obj, enemies_list, gRenderer, event, path_map, quit);
                    ReturnMenu = 0;
                }
                gMap.LoadMap(path_map);
                gMap.LoadTiles(gRenderer);
                Map map_data = gMap.getMap();

                Fire.setCharacter(FIREBOY);
                Water.setCharacter(WATERGIRL); Water.SetHeight(50);
                if (Mix_PlayMusic(gMusic, -1) == -1){
                    cout << "can't play music! \n";
                }

                while (!quit){
                    fps_timer.start();
                    while (SDL_PollEvent(&event) != 0){ //event click quit and key related to main character
                        if (event.type == SDL_QUIT) quit = true;
                        Fire.HandleInputAction(event, gRenderer, FIREBOY);
                        Water.HandleInputAction(event, gRenderer, WATERGIRL);
                        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                            ReturnMenu = menu_playing(gRenderer, event, quit, obj, enemies_list, Fire, Water, path_map);
                        }
                    }

                    if (ReturnMenu == 1){
                        break;
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

                    //main character
                    Fire.DoPlayer(map_data);
                    SDL_Rect FireRect = Fire.getRectChar();
                    Fire.Show(gRenderer);

                    Water.DoPlayer(map_data);
                    SDL_Rect WaterRect = Water.getRectChar();
                    Water.Show(gRenderer);

                    //render map
                    gMap.DrawMap(gRenderer);
                    gMap.copyMap(map_data);

                    //enemy and check collision of it
                    SDL_Rect enemy_rect[int(enemies_list.size())];

                    for (int i = 0; i < int(enemies_list.size()); i++){
                        enemies_list[i].controlMoving(gRenderer, "Data/photo/character/red_slime_left.png", "Data/photo/character/red_slime_right.png");
                        enemies_list[i].DoPlayer(map_data);
                        enemies_list[i].Show(gRenderer);
                        enemy_rect[i] = enemies_list[i].get_current_pos();
                        if ( check_collision(FireRect, enemy_rect[i]) || check_collision(WaterRect, enemy_rect[i]) ){
                            Fire.setLose(true); Water.setLose(true);
                        }
                    }

                    //render barrier and button
                    for (int i = 0; i < int(obj.size()); i++){
                        obj[i].render(gRenderer);
                    }
                    //check collision of button
                    for (int i = 0; i < int(obj.size()); i++){
                        SDL_Rect button = obj[i].getButRect();

                        if (check_collision(FireRect,button) || check_collision(WaterRect,button)){
                            obj[i].setOnButton(true);
                        }
                        else{
                            obj[i].setOnButton(false);
                        }

                        //activity related to button, barrier and character
                        obj[i].activity(Fire);
                        obj[i].activity(Water);
                    }


                    //render time_count
                    if ( ! time_count.CreateGameText(gFont, gRenderer, ( SCREEN_WIDTH - time_count.getWidth() ) / 2, 0 ) ) {
                        cout << "can't create time count !\n";
                    }

                    //show coin
                    string show_f_coin = "FIRE'S COIN: " + std::to_string(Fire.get_coin()) ; fire_coin.setText(show_f_coin);
                    string show_w_coin = "WATER'S COIN: " + std::to_string(Water.get_coin()) ; water_coin.setText(show_w_coin);
                    fire_coin.setTextColor(WHITE_TEXT) ; water_coin.setTextColor(WHITE_TEXT);
                    if ( ! ( fire_coin.CreateGameText(gFont, gRenderer, 0, 0) && water_coin.CreateGameText(gFont, gRenderer, SCREEN_WIDTH - water_coin.getWidth(), 0) ) ) {
                        cout << "can't create game text of coin !\n";
                    }
                    //show to screen
                    SDL_RenderPresent(gRenderer);

                    //set fps
                    int frameTicks = fps_timer.get_ticks();
                    if (frameTicks < SCREEN_TICKS_PER_FRAME){
                        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);

                    }
                    if ( Water.getLose() || Fire.getLose() ){
                        Mix_PlayChannel(-1, death, 0);
                        cout << "LOSE";
                        SDL_Delay(2000);


                        Water.setLose(false);
                        Fire.setLose(false);
                        Water.~MainObject();
                        Fire.~MainObject();
                        obj.clear();
                        enemies_list.clear();
                        ret_menu = ShowMenuStartOrNot(Water, Fire, obj, enemies_list, gRenderer, event, path_map, quit);

                        break;
                    }

                    if ( Water.getWin() && Fire.getWin() ){
                        SDL_Delay(2000);

                        Water.setWin(false);
                        Fire.setWin(false);
                        //Water.~MainObject();
                        //Fire.~MainObject();
                        obj.clear();
                        enemies_list.clear();
                        ret_menu = ShowMenuStartOrNot(Water, Fire, obj, enemies_list, gRenderer, event, path_map, quit);

                        cout << "WIN";
                        break;
                    }
                    if (quit == true) break;
                }
            if (quit == true) break;
            }
        }
    }
    close();
    return 0;
}


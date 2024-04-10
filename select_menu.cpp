#include "select_menu.h"

int ChooseGamePlayMode()
{
    int SelectNum;
    cin >> SelectNum;
    return SelectNum;
}

int ChooseLevel()
{
    int level;
    cin >> level;
    return level;
}

int Randomlevel()
{
    srand(time(NULL));
    int level = rand() % MAX_LEVEL;
    return level;
}

string LevelMap (MainObject &player_1, MainObject &player_2, vector<Object> &obj, vector<Enermy> &enmy)
{
    int mode = ChooseGamePlayMode();
    int level;
    if (mode == CHOOSE_LEVEL){
        level = ChooseLevel();
    }
    else{
        level = Randomlevel();
    }
    string map_path;

    switch(level)
    {
    case LEVEL1:
        {
            //load background differently (not done)
           map_path = "Data/map/MapLevel1.txt";
           player_1.setXpos(64);
           player_1.setYpos(608);

           player_2.setXpos(64);
           player_2.setYpos(703);

           Enermy enemy1(266,253), enemy2(507,94) , enemy3(130,512) , enemy4(670,382);
           enmy.push_back(enemy1);
           enmy.push_back(enemy2);
           enmy.push_back(enemy3);
           enmy.push_back(enemy4);

           for (int i = 0; i < int(enmy.size()); i++){
                enmy[i].setTypeMove(MOVING_IN_SPACE);

           }
           cout << "successfully load map !\n";
           break;
        }
    }
    return map_path;
}

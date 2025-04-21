#ifndef Player_h
#define player_h

using namespace std;

#include<string>

class player
{
    private:
    string name;
    string playerclass;
    int health;
    int attack;
    int defense;

 public:
    player();
    void createplayer();
    void stats();
    void dmghit(int dmg);
    bool isalive();
    void heal(int amount);


};
#endif

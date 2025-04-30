#ifndef Player_h
#define player_h

#include <string>

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
    string inventory[5];
    int itemcount = 0;

 public:
    player();
    void createplayer();
    void stats();
    void dmghit(int dmg);
    bool isalive();
    void heal(int amount);
    void heal();
    int getattack();
    void savetofile(const string& filename);
    void additem(const string& item);
    void showinventory();


};
#endif

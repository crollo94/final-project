#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class player
{
public:
    player();

    void createplayer();
    void stats();
    void dmghit(int dmg);
    bool isalive();
    void heal(int amount);
    void heal();  // Default heal
    int getattack();
    void savetofile(const string& filename);
    void additem(const string& item);
    void showinventory();
    void useItem();
    void takeTrapDamage();
    bool solvePuzzle();  // Declare solvePuzzle function

private:
    string name;
    string playerclass;
    int health;
    int attack;
    int defense;
    string inventory[5];  // Inventory with a max of 5 items
    int itemcount = 0;    // Tracks number of items in the inventory
};

#endif // PLAYER_H

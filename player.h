#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class player
{
private:
    string name;
    string playerclass;
    int health;
    int attack;
    int defense;
    string inventory[5];
    int itemcount = 0;  // The number of items in the inventory

public:
    player();  // Constructor to initialize player

    // Player creation
    void createplayer();

    // Player stats
    void stats();

    // Damage calculation and taking damage
    void dmghit(int dmg);
    bool isalive();

    // Healing functions
    void heal(int amount);
    void heal();  // Default heal function

    // Getter for attack
    int getattack();

    // Save player data to file
    void savetofile(const string& filename);

    // Add item to inventory
    void additem(const string& item);

    // Show inventory
    void showinventory();

    // Use an item
    void useItem();

    // Take damage from a trap
    void taketrapdamage();

    // Solve a puzzle
    bool solvePuzzle();

    // Getter for the number of items in inventory
    int getItemCount() const;

    // Getter for an item in the inventory
    string getInventoryItem(int index) const;
};

#endif // PLAYER_H

#include <iostream>
#include "player.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const string loottable[] =
{
    "health potion",
    "attack potion",
    "gold coin",
    "magic scroll",
    "dagger",
    "shield",
    "torch"
};

const int lootcount = sizeof(loottable) / sizeof(loottable[0]);

// Function for entering a room
void enterroom(player& p)
{
    int outcome = rand() % 6;  // up to 6 types of rooms

    if (outcome == 0)  // Monster room
    {
        cout << "Wild monster appears!" << endl;
        int monsterhealth = rand() % 30 + 20;
        int monsterattack = rand() % 10 + 5;
        while (p.isalive() && monsterhealth > 0)
        {
            cout << "Monster health: " << monsterhealth << endl;
            cout << "Choose to attack or heal" << endl;
            cout << "1. Attack" << endl;
            cout << "2. Heal" << endl;
            cout << "Pick: ";
            int option;
            cin >> option;

            switch (option)
            {
                case 1:
                    monsterhealth -= p.getattack();
                    cout << "You attacked the monster for " << p.getattack() << " damage." << endl;
                    break;

                case 2:
                    cout << "Enter the amount to heal: ";
                    int heallimit;
                    cin >> heallimit;
                    p.heal(heallimit);
                    break;

                default:
                    cout << "Wrong pick! Try again!" << endl;
                    continue;
            }

            if (monsterhealth > 0)
            {
                cout << "The monster attacks you!" << endl;
                p.dmghit(monsterattack);
            }

            p.stats();
        }

        if (p.isalive())
        {
            cout << "You defeated the monster!" << endl;
            string randomitem = loottable[rand() % lootcount];
            cout << "You looted: " << randomitem << endl;
            p.additem(randomitem);
        }
        else
        {
            cout << "You died!" << endl;
        }
    }
    else if (outcome == 1)  // Chest room
    {
        cout << "You find a chest!" << endl;
        if (rand() % 2 == 0)
        {
            p.additem("health potion");
        }
        else
        {
            p.additem("attack potion");
        }
    }
    else if (outcome == 2)  // Empty room
    {
        cout << "The room is empty!" << endl;
    }
    else if (outcome == 3)  // Trap room
    {
        cout << "You triggered a trap!" << endl;
        p.taketrapdamage();
    }
    else if (outcome == 4)  // Puzzle room
    {
        cout << "You find a puzzle!" << endl;
        bool solved = p.solvePuzzle();
        if (!solved)
        {
            cout << "You couldn't solve the puzzle and are hurt by the magical trap!" << endl;
        }
    }
    else if (outcome == 5)  // Dark room that needs torch
    {
        cout << "You enter a dark room..." << endl;
        bool hastorch = false;

        for (int i = 0; i < p.getItemCount(); ++i)
        {
            if (p.getInventoryItem(i) == "torch")
            {
                hastorch = true;
                break;
            }
        }

        if (hastorch)
        {
            cout << "You use your torch to light up the room and find a gold coin!" << endl;
            p.additem("gold coin");
        }
        else
        {
            cout << "It's too dark to see! You stumble and get hurt." << endl;
            p.taketrapdamage();
        }
    }
}

// Function for the boss battle
void bossBattle(player& p)
{
    cout << "A mighty boss appears!" << endl;
    int bossHealth = 100;
    int bossAttack = 15;

    while (p.isalive() && bossHealth > 0)
    {
        cout << "Boss health: " << bossHealth << endl;
        cout << "Choose to attack or heal" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Heal" << endl;
        cout << "Pick: ";
        int option;
        cin >> option;

        switch (option)
        {
            case 1:
                bossHealth -= p.getattack();
                cout << "You attacked the boss for " << p.getattack() << " damage." << endl;
                break;

            case 2:
                cout << "Enter the amount to heal: ";
                int heallimit;
                cin >> heallimit;
                p.heal(heallimit);
                break;

            default:
                cout << "Wrong pick! Try again!" << endl;
                continue;
        }

        if (bossHealth > 0)
        {
            cout << "The boss attacks you!" << endl;
            p.dmghit(bossAttack);
        }

        p.stats();
    }

    if (p.isalive())
    {
        cout << "You defeated the boss!" << endl;
        p.additem("legendary sword");
    }
    else
    {
        cout << "You were defeated by the boss!" << endl;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    player p;
    cout << "Welcome to the dungeon!" << endl;
    p.createplayer();
    p.stats();

    bool enteredBossRoom = false;

    while (p.isalive())
    {
        cout << "\nYou are in a dark hallway with paths ahead." << endl;
        cout << "Choose your path:" << endl;
        cout << "1. Go left" << endl;
        cout << "2. Go right" << endl;
        cout << "3. Go forward" << endl;
        cout << "4. Exit the dungeon" << endl;
        cout << "5. Check inventory" << endl;
        cout << "6. Use item" << endl;
        cout << "Enter your option: ";

        int option;
        cin >> option;

        switch (option)
        {
            case 1:
            case 2:
            case 3:
                if (!enteredBossRoom && rand() % 10 == 0)
                {
                    cout << "You found the boss room!" << endl;
                    enteredBossRoom = true;
                    bossBattle(p);
                }
                else
                {
                    enterroom(p);
                }
                break;

            case 4:
                cout << "You have exited the dungeon." << endl;
                return 0;

            case 5:
                p.showinventory();
                break;

            case 6:
                p.useItem();
                break;

            default:
                cout << "Invalid option, try again!" << endl;
        }
    }

    if (!p.isalive())
    {
        cout << "\nGame Over." << endl;
    }

    return 0;
}

#include <iostream>
#include "player.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;


void enterroom(player& p)
{
    int outcome = rand() % 3;

    if (outcome ==0)
    {
        cout << "wild monster appears!" << endl;
        int monsterhealth = rand() % 30 + 20;
        int monsterattack = rand() % 10 + 5;
        while (p.isalive()&& monsterhealth > 0)
        {
            cout << "monster health: " << monsterhealth << endl;
            cout << "choose to attack or heal" << endl;
            cout << "1. attack" << endl;
            cout << "2. heal" << endl;
            cout << "Pick";
            int option;
            cin >> option;

            switch(option)
            {
                case 1:
                monsterhealth -= p.getattack();
                cout << "you attacked the monster for " << p.getattack() << " Damage" << endl;
                break;

                case 2: 
                cout << "enter the amount to heal";
                int heallimit;
                cin >> heallimit;
                p.heal(heallimit);
                break;


                default:
                cout <<" wrong pick! try again!" << endl;
                continue;

            }

            if(monsterhealth > 0)
            {
                cout << "the moster attacks you" << endl;
                p.dmghit(monsterattack);
            }
            p.stats();
        }

        if(p.isalive())
        {
            cout << "you defated the monster" << endl;
            //loot time?
            if(rand() % 2 ==0)
            {
                p.additem("health potion");
            }

        }
        else
        {
            cout << "death!";
        }
    }
    else if (outcome == 1)
    {
        cout << "you find a chest " << endl;
        if (rand() % 2 == 0)
        {
            p.additem("health potion");
        }
        else
        {
            p.additem("attack potion");
        }
    }
    else
    {
        cout << " the room is empty " << endl;
    }
}

int main()
{
    srand(time(0));
    player p;
    cout << "welcome to the dungen!" << endl;
    p.createplayer();
    p.stats();

    while (p.isalive())
    {
        cout << "you are in a dark hallway with paths ahead" << endl;
        cout << " choose your own path" << endl;
        cout << "1. go left" << endl;
        cout << "2. go right" << endl;
        cout << "3. go forward" << endl;
        cout << "4. exit the dungeon" << endl;
        cout << "enter your option: ";

        int option;
        cin >> option;

        switch(option)
        {
            case 1:
            case 2:
            case 3:
            enterroom(p);
            break;
            case 4:
            cout << "you have exited the dungeon." << endl;
            return 0;
            default: 
            cout << "invaild option, try again" << endl;

        }
    }

    return 0;
}    


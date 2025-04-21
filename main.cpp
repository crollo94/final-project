#include <iostream>
#include "player.h"

using namespace std;

int main()
{
    player player;

    cout << "welcome to the dungen! find a way out!" << endl;

    player.createplayer();
    player.stats();

    //going to attempt a basic encounter before diving into it

    cout << "a wild Goblin appears!" << endl;

    int monsterhealth = 30;
    int monsterattack = 8;

    while (player.isalive() && monsterhealth > 0)
    {
        cout << "pick to attack or heal" << endl;
        cout << "1. Attack " << endl;
        cout << "2. heal " << endl;
        cout << "enter option";

        int option;
        cin >> option;

        switch(option)
        {
            case 1:
                cout << "you attack the goblin!" << endl;
                monsterhealth -= 10;
                cout << "Goblin health is now at: " << monsterhealth << endl;
                break;

            case 2:
                player.heal(10);
                break;

            default:
                cout << "worng option. try again!" << endl;
                continue;
        }

        if(monsterhealth > 0 )
        {
            cout << "goblin attack you!" << endl;
            player.dmghit(monsterattack);
        }
          player.stats();
        
          if (player.isalive())
          {
            cout << " you killed the goblin" << endl;

          }
          else
          {
            cout << "you have lost " << endl;
          }
    }

    return 0 ;

}

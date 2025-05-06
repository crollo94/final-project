#include "player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

player::player()
{
    name = "";
    playerclass = "";
    health = 100;
    attack = 10;
    defense = 5;
}

void player::createplayer()
{
    cout << "Enter your name: ";
    getline(cin, name);

    bool validClass = false;

    while (!validClass)
    {
        cout << "Choose a class (Warrior, Mage, Rogue): ";
        getline(cin, playerclass);

        if (playerclass == "Warrior")
        {
            health = 120;
            attack = 15;
            defense = 10;
            validClass = true;
        }
        else if (playerclass == "Mage")
        {
            health = 80;
            attack = 20;
            defense = 3;
            validClass = true;
        }
        else if (playerclass == "Rogue")
        {
            health = 100;
            attack = 12;
            defense = 6;
            validClass = true;
        }
        else
        {
            cout << "Invalid class. Please choose again.\n";
        }
    }
}

void player::stats()
{
    cout << "\n=== Player Stats ===\n";
    cout << "Name: " << name << "\n";
    cout << "Class: " << playerclass << "\n";
    cout << "Health: " << health << "\n";
    cout << "Attack: " << attack << "\n";
    cout << "Defense: " << defense << "\n";
    cout << "====================\n";
}

void player::dmghit(int dmg)
{
    int damageTaken = dmg - defense;

    if (damageTaken < 0)
    {
        damageTaken = 0;
    }

    health -= damageTaken;
    cout << "You took " << damageTaken << " damage!" << endl;
}

bool player::isalive()
{
    return health > 0;
}

void player::heal(int amount)
{
    health += amount;
    cout << "You healed for " << amount << " HP!" << endl;
}

void player::heal()
{
    heal(5);  // Default heal
}

int player::getattack()
{
    return attack;
}

void player::savetofile(const string& filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        file << name << endl;
        file << playerclass << endl;
        file << health << endl;
        file << attack << endl;
        file << defense << endl;
        file.close();
        cout << "Game saved!" << endl;
    }
    else
    {
        cout << "Failed to open file!" << endl;
    }
}

void player::additem(const string& item)
{
    if (itemcount < 5)
    {
        inventory[itemcount++] = item;
        cout << item << " added to inventory!" << endl;
    }
    else
    {
        cout << "Your inventory is full!" << endl;
    }
}

void player::showinventory()
{
    if (itemcount == 0)
    {
        cout << "Your inventory is empty!" << endl;
    }
    else
    {
        cout << "=== Inventory ===\n";
        for (int i = 0; i < itemcount; ++i)
        {
            cout << i + 1 << ". " << inventory[i] << endl;
        }
        cout << "=================\n";
    }
}

void player::useItem()
{
    if (itemcount == 0)
    {
        cout << "Your inventory is empty!" << endl;
        return;
    }

    cout << "Select an item to use:" << endl;
    for (int i = 0; i < itemcount; ++i)
    {
        cout << i + 1 << ". " << inventory[i] << endl;
    }

    int choice;
    cout << "Enter item number to use: ";
    cin >> choice;

    if (choice < 1 || choice > itemcount)
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Use the item
    string item = inventory[choice - 1];
    if (item == "health potion")
    {
        heal(20);  // Heal for 20 HP
        cout << "You used a health potion!" << endl;
    }
    else if (item == "attack potion")
    {
        attack += 5;  // Increase attack by 5
        cout << "You used an attack potion! Attack increased!" << endl;
    }
    else if (item == "torch")
    {
        cout << "You used the torch to light the way!" << endl;
    }
    else if (item=="gold coin")
    {
        cout << "You flip your coin in the air" << endl;
        cout << "i wonder whats this is for? ";
    }
    else if (item == "magic scroll")
    {
        heal(10);
        attack +=2;
        cout << "The magic scroll fizzles and bursts! +10 hp and +2 attack!" << endl;
    }
    else if (item == "dagger")
    {
        attack += 5;
        cout << "the dagger makes you hit harder! equiping the dagger has givin you 5 more attack power!" << endl;
    }
    else if (item == "shield")
    {
        defense +=5;
        cout << "equiping the shield has applied +5 defense!" <<endl;
    }
    else 
    {
        cout << "you used" << item << "it does nothing D:" << endl;
    }

    // Remove the item from the inventory
    for (int i = choice - 1; i < itemcount - 1; ++i)
    {
        inventory[i] = inventory[i + 1];
    }
    --itemcount;
}

// messing with trap rooms 
void player::taketrapdamage()
{
    int trapDamage = rand() % 10 + 10;
    health -= trapDamage;
    cout << "You triggered a trap and took " << trapDamage << " damage!" << endl;
}

// pizzle solveing 
bool player::solvePuzzle()
{
    struct puzzle
    {
        string question;
        string answer;
    };

    puzzle multipuz[] =
    {
        {"what has keys but cant open locks?", "piano"},
        {"what runs but never walks?", "water"},
        {"what has hands but cant clap?", "clock"}
    };
    int puzzlecount = sizeof(multipuz) / sizeof(multipuz[0]);
    int index = rand() % puzzlecount;

    cout << "Solve this puzzle:" << endl;
    cout << multipuz[index].question << endl;
    cout << "Your answer: ";

    string useranswer;
    cin.ignore();
    getline(cin, useranswer);

    for (int i = 0; i < useranswer.length(); i++)
    {
        useranswer[i] = tolower(useranswer[i]);
    }

    string correctAnswer = multipuz[index].answer;
    for (int i = 0; i < correctAnswer.length(); i++)
    {
        correctAnswer[i] = tolower(correctAnswer[i]);
    }

    if (useranswer == correctAnswer)
    {
        cout << "Correct! You solved the puzzle." << endl;
        return true;
    }
    else
    {
        cout << "Incorrect! You are hurt by the magical trap!" << endl;
        taketrapdamage();
        return false;
    }
}

int player::getItemCount() const
{
    return itemcount;
}

// Getter for an item in the inventory
string player::getInventoryItem(int index) const
{
    if (index >= 0 && index < itemcount)
        return inventory[index];
    else
        return "";
}

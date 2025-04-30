#include "player.h"
#include <iostream>
#include <fstream>

using namespace std;

player::player() {
    name = "";
    playerclass = "";
    health = 100;
    attack = 10;
    defense = 5;
}

void player::createplayer() {
    cout << "Enter your name: ";
    getline(cin, name);

    bool validClass = false;

    while (!validClass) {
        cout << "Choose a class (Warrior, Mage, Rogue): ";
        getline(cin, playerclass);

        if (playerclass == "Warrior") {
            health = 120;
            attack = 15;
            defense = 10;
            validClass = true;
        } else if (playerclass == "Mage") {
            health = 80;
            attack = 20;
            defense = 3;
            validClass = true;
        } else if (playerclass == "Rogue") {
            health = 100;
            attack = 12;
            defense = 6;
            validClass = true;
        } else {
            cout << "Invalid class. Please choose again.\n";
        }
    }
}

void player::stats() {
    cout << "\n=== Player Stats ===\n";
    cout << "Name: " << name << "\n";
    cout << "Class: " << playerclass << "\n";
    cout << "Health: " << health << "\n";
    cout << "Attack: " << attack << "\n";
    cout << "Defense: " << defense << "\n";
    cout << "====================\n";
}

void player::dmghit(int dmg) {
    int damageTaken = dmg - defense;
    if (damageTaken < 0) {
        damageTaken = 0;
    }

    health -= damageTaken;
    cout << "You took " << damageTaken << " damage!" << endl;
}

bool player::isalive() {
    return health > 0;
}

void player::heal(int amount) {
    health += amount;
    cout << "You healed for " << amount << " HP!" << endl;
}

void player::heal() {
    heal(5);
}

int player::getattack() {
    return attack;
}

void player::savetofile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << name << endl;
        file << playerclass << endl;
        file << health << endl;
        file << attack << endl;
        file << defense << endl;
        file.close();
        cout << "Game saved." << endl;
    } else {
        cout << "Failed to open file." << endl;
    }
}

void player::additem(const string& item) {
    if (itemcount < 5) {
        inventory[itemcount++] = item;
        cout << item << " added to inventory." << endl;
    } else {
        cout << "Your inventory is full!" << endl;
    }
}

void player::showinventory() {
    cout << "\n=== Inventory ===" << endl;
    if (itemcount == 0) {
        cout << "Your inventory is empty." << endl;
    } else {
        for (int i = 0; i < itemcount; ++i) {
            cout << "- " << inventory[i] << endl;
        }
    }
    cout << "=================\n" << endl;
}

//  Trap damage function
void player::takeTrapDamage() {
    int trapDamage = rand() % 15 + 5;
    cout << "A trap goes off! You take " << trapDamage << " damage!" << endl;
    dmghit(trapDamage);
}

// Simple puzzle function
bool player::solvePuzzle() {
    int answer;
    cout << "You find a riddle: What is 3 + 4 * 2?" << endl;
    cout << "Your answer: ";
    cin >> answer;

    if (answer == 11) {
        cout << "Correct! You are rewarded with an item!" << endl;
        additem("gold coin");
        return true;
    } else {
        cout << "Wrong! You feel a jolt of pain from a magical trap!" << endl;
        takeTrapDamage();
        return false;
    }
}

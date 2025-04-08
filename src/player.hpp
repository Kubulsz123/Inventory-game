#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Globals.hpp"
#include "inventory.hpp"
#include "items.hpp"

#ifndef player_hpp
#define player_hpp

using namespace std;

class Player
{
    private:
        string name;
        int gold;
        int health;
        Inventory* inventory;
    public:
        Player() = delete;
        Player(string name)
        {
            this->name = name;
            this->gold = 0;
            this->health = 5;
            this->inventory = new Inventory(2,4);
        }
        int getHealth()
        {
            return this->health;
        }
        void setHealth(int health)
        {
            this->health = health;
        }
        string getName()
        {
            return this->name;
        }
        void setName(string name)
        {
            this->name = name;
        }
        int getGold()
        {
            return this->gold;
        }
        void setGold(int gold)
        {
            this->gold = gold;
        }
        void display()
        {
            cout << "Name: " << name << " ";
        }
};

#endif

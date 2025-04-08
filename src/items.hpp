#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

#include "Globals.hpp"

#ifndef items_hpp
#define items_hpp

using namespace std;

enum Types
{
    ofensive,
    defensive,
    other
};

class Item
{
    protected:
        string name;
        int price;
        Types type;
        string path;
    public:
        Item() = delete;
        Item(string name,int price,Types type,string path)
        {
            this->name = name;
            this->price = price;
            this->type = type;
            this->path = path;
        }
        string getName()
        {
            return this->name;
        }
        int getPrice()
        {
            return this->price;
        }
        Types getType()
        {
            return this->type;
        }
        string getPath()
        {
            return this->path;
        }
        void setName(string name)
        {
            this->name = name;
        }
        void setPrice(int price)
        {
            this->price = price;
        }
        void setType(Types type)
        {
            this->type = type;
        }
        void display()
        {
            cout << "Name: " << name << endl;
            cout << "Price: " << price << endl;
            cout << "Type: " << type << endl;
        }
};

#endif
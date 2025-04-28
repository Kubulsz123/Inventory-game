#ifndef ITEMS_hpp
#define ITEMS_hpp

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>
#include "Globals.hpp"

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
    string description;

public:
    Item() = delete;
    Item(string name, int price, Types type, string path, string description) : name(name), price(price), type(type), path(path), description(description)
    {}

    string getName() const 
    { 
        return name; 
    }
    int getPrice() const 
    { 
        return price; 
    }
    Types getType() const 
    { 
        return type; 
    }
    string getPath() const 
    {
        return path; 
    }
    string getDescription() const 
    { 
        return description; 
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
    void setPath(string path) 
    { 
        this->path = path; 
    }
    void setDescription(string desc) 
    { 
        this->description = desc; 
    }
    void display()
    {
        cout << "Price: " << price << endl;
        cout << "Type: " << type << endl;
    }
    virtual void inspect()
    {
        cout << "Inspecting item: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Type: " << type << endl;
    }

    virtual ~Item() = default;
};


class Magnifying_Glass : public Item {
public:
    Magnifying_Glass(string name, int price, Types type, string path)
        : Item(name, price, type, path, "A tool used to show if bullet in chamber is live or blank.") {}
};

class Handsaw : public Item {
public:
    Handsaw(string name, int price, Types type, string path) : Item(name, price, type, path, "A tool used to saw output of shotgun so it would deal double damage.") {}
};

class Beer : public Item {
public:
    Beer(string name, int price, Types type, string path) : Item(name, price, type, path, "Empty one bullet from chamber of shotgun.") {}
};

class Handcuffs : public Item {
public:
    Handcuffs(string name, int price, Types type, string path) : Item(name, price, type, path, "Stops player for one turn (he can't do anything in his turn).") {}
};

class Vodka : public Item {
public:
    Vodka(string name, int price, Types type, string path) : Item(name, price, type, path, "Moves everyone inventories to one left and removes item - vodka.") {}
};

class Sprite_Banana : public Item {
public:
    Sprite_Banana(string name, int price, Types type, string path) : Item(name, price, type, path, "Removes items from all inventories and remove this item.") {}
};

class Uno_Reverse : public Item {
public:
    Uno_Reverse(string name, int price, Types type, string path) : Item(name, price, type, path, "Swap two players' inventories and remove this item.") {}
};

class Adrenaline : public Item {
public:
    Adrenaline(string name, int price, Types type, string path): Item(name, price, type, path, "Adds 2 lives to you for only one round in which you used it.") {}
};

class Cigarettes : public Item {
public:
    Cigarettes(string name, int price, Types type, string path) : Item(name, price, type, path, "Permanently heal one life in game.") {}
};

#endif 
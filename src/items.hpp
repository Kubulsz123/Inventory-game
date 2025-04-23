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
            cout << "Price: " << price << endl;
            cout << "Type: " << type << endl;
        }
        virtual void inspect()
        {
            cout << "Inspecting item: " << name << endl;
            cout << "Price: " << price << endl;
            cout << "Type: " << type << endl;
        }
};

class Magnifying_Glass : public Item {
    private:
        string description;
        string image_path;
    public:
        Magnifying_Glass(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "A tool used to show if bullet in chamber is live or blank.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Handsaw : public Item {
    private:
        string description;
        string image_path;
    public:
        Handsaw(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "A tool used to saw output of shotgun so it would deal double damage.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Beer : public Item {
    private:
        string description;
        string image_path;
    public:

        Beer(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Empty one bullet from chamber of shotgun.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Handcuffs : public Item {
    private:
        string description;
        string image_path;
    public:

        Handcuffs(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Stops player for one turn (he cant do anything in his turn).";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Vodka : public Item {
    private:
        string description;
        string image_path;
    public:

        Vodka(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Moves everyone inventories to one left and removes item - vodka.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Sprite_Banana : public Item {
    private:
        string description;
        string image_path;
    public:

        Sprite_Banana(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Removes items from all inventories and remove this item.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Uno_Reverse : public Item {
    private:
        string description;
        string image_path;
    public:

        Uno_Reverse(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Swap two players inventories and remove this item.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Adrenaline : public Item {
    private:
        string description;
        string image_path;
    public:

        Adrenaline(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Adds 2 lives to you for only one round in which you used it.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

class Cigarettes : public Item {
    private:
        string description;
        string image_path;
    public:

        Cigarettes(string name, int price, Types type, string image_path) : Item(name, price, type, image_path) {
            this->description = "Pernamently heal one life in game.";
            this->image_path = image_path;
        }

        void inspect() override {
            cout << description << endl;
        }

        void setImagePath(string image_path) {
            this->image_path = image_path;
        }

        string getImagePath() {
            return image_path;
        }
};

#endif
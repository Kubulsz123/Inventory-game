#include <iostream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

// Temporary item class change if you want//
class Item
{
    private:
        string name;
        float price;
        int durability;

    public:
        Item()
        {
        this->name = "tempName";
        this->price = 1.50;
        this->durability = 100; 
        }
        Item(string name, float price, int durability)
        {
            this->name = name;
            this->price = price;
            this->durability = durability;
        }
        
        void display()
        { 
            cout << "Name: " << name << " Price: " << price << " Durability: " << durability << endl;
        }
        string getName()
        {
            return name;
        }
        float getPrice()
        {
            return price;
        }
        int getDurability()
        {
            return durability;
        }
        void setName(string name)
        {
            this->name = name;
        }
        void setPrice(float price)
        {
            this->price = price;
        }
        void setDurability(int durability)
        {
            this->durability = durability;
        }
};

class Inventory
{
    private:
        Item*** items;
        int cols;
        int rows;
    public:
        Inventory(int rows, int cols)
        {
            this->rows = rows;
            this->cols = cols;
            items = new Item**[rows];

            for(int i = 0; i < rows; i++)
            {
                items[i] = new Item*[cols];   
            }

            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    items[i][j] = nullptr;
                }
            }
        }
        void display()
        {
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    if(items[i][j] == nullptr)
                    {
                        cout << "[" << " " << "]";
                    }
                    else
                    {
                        cout << "[" << items[i][j]->getName()[0] << "]" << endl;
                    }
                }
                cout << endl;
            }
        }
        ~Inventory()
        {
            //some function that check if there is something in tab and remove them
            for(int i = 0;i < rows; i++)
            {
                delete[] items[i];
            }
            delete[] items;
        }
};
int main()
{
    // To see if worked // 
    //Item ok;
    //Item temp2("sword",2.5,100);
    //ok.display();
    //temp2.display();
    //Inventory templateinv(3,5);
    //templateinv.display();
    return 0;
}

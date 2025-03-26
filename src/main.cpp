#include <iostream>
#include <string>

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
    public:
        Item()
        {
            this->name = "coin";
            this->price = 1;
            this->type = other;
        }
        Item(string name,int price,Types type)
        {
            this->name = name;
            this->price = price;
            this->type = type;
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
int main()
{
    return 0;
}
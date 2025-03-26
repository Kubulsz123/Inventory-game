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

class Inventory {
private:
    Item*** items;
    int rows;
    int cols;
public:
    Inventory(int rows, int cols) : rows{rows}, cols{cols} {
        items = new Item**[rows];
        for (int i = 0; i < rows; i++) {
            items[i] = new Item*[cols];
        }
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[";
                if (items[i][j] == nullptr) {
                    cout << " ";
                }
                else {
                    cout << items[i][j]->getName()[0];
                }
                cout << "]";
            }
            cout << endl;
        }
    }


    bool addItem(Item* item) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] == nullptr) {
                    items[i][j] = item;
                    return true;
                }
            }
        }
        return false;
    }

    bool removeItem(int row, int col) {
        if ((row >= rows || row < 0) || (col < 0 || col >= cols)) {
            return false;
        }
        if (items[row][col] == nullptr) {
            return false;
        }
        else {
            delete items[row][cols];
            items[row][cols] == nullptr;

            return true;
        }
        
    }

    int getInventoryValue() {
        int total = 0;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] != nullptr) {
                    total += items[i][j]->getPrice(); 
                }
            }
        }

        return total;
    }

    void removeItems() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] != nullptr) {
                    delete items[i][j];
                    items[i][j] == nullptr;
                }
            }
        }
    }

    ~Inventory() {
        removeItems();

        for (int i = 0; i < rows; i++) {
            delete[] items[i];
        }

        delete[] items;
    }
};

int main()
{
    return 0;
}
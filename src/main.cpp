#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
            for (int j = 0; j < cols; j++) {
                items[i][j] = nullptr;
            }
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
        cout << flush; // Make sure everything prints
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
            delete items[row][col];
            items[row][col] = nullptr;

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
                    items[i][j] = nullptr;
                }
            }
        }
    }

    void inspect(Item* item) {
        if (item != nullptr) {
            cout << "Inspecting item: " << item->getName() << endl;
            item->display();
        } else {
            cout << "Item not found!" << endl;
        }
    }

    bool move(Item* item, int targetRow, int targetCol) {
        if (targetRow < 0 || targetRow >= rows || targetCol < 0 || targetCol >= cols) {
            cout << "Invalid position!" << endl;
            return false;
        }

        if (items[targetRow][targetCol] != nullptr) {
            cout << "Target position is already occupied!" << endl;
            return false;
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] == item) {
                    items[targetRow][targetCol] = item;
                    items[i][j] = nullptr;
                    cout << "Moved item to position (" << targetRow << ", " << targetCol << ")" << endl;
                    return true;
                }
            }
        }

        cout << "Item not found in inventory!" << endl;
        return false;
    }

    bool use(Item* item) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] == item) {
                    // Here you would add later on the logic to use the item in our game
                    if (item->getType() == defensive) {
                        cout << "Using item: " << item->getName() << endl;
                        removeItem(i, j);
                    }
                    else if (item->getType() == ofensive) {
                        cout << "Using item: " << item->getName() << endl;
                        removeItem(i, j);
                    }
                    else if (item->getType() == other) {
                        cout << "Using item: " << item->getName() << endl;
                        removeItem(i, j);
                    }
                    else {
                        cout << "Item is not usable!" << endl;
                    }
                    return true;
                }
            }
        }

        cout << "Item not found in inventory!" << endl;
        return false;
    }

    void sort() {
        vector<Item*> temp;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] != nullptr) {
                    temp.push_back(items[i][j]);
                    items[i][j] = nullptr;
                }
            }
        }

        std::sort(temp.begin(), temp.end(), [](Item* a, Item* b) -> bool {
            return a->getType() < b->getType();
        });

        int index = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (index < temp.size()) {
                    items[i][j] = temp[index++];
                }
            }
        }

        cout << "Inventory sorted by item types!" << endl;
    }
    void filter(char input) {
        cout << "Show items which names start with: " << input << ";" << endl;

        bool founded = false;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] != nullptr && items[i][j]->getName()[0] == input) {
                    cout << "Item found: " << items[i][j]->getName() << endl;
                    if (items[i][j] != nullptr) {
                        items[i][j]->display();
                    }
                    founded = true;
                }
            }
        }

        if (!founded) {
            cout << "No items found with the given letter!" << endl;
        }
    }

    bool expand(int& currency_amount, int& cost, int& upgrades) {
        if (upgrades >= 3) {
            cout << "Maximum number of upgrades reached!" << endl;
            return false;
        }

        if (currency_amount < cost) {
            cout << "Not enough currency to expand inventory!" << endl;
            return false;
        }

        // Deduct the cost from the currency
        currency_amount -= cost;

        if (upgrades % 2 == 0) {
            // Expand columns
            for (int i = 0; i < rows; i++) {
                Item** newRow = new Item*[cols + 1];
                for (int j = 0; j < cols; j++) {
                    newRow[j] = items[i][j];
                }
                newRow[cols] = nullptr; // Initialize the new column to nullptr
                delete[] items[i];
                items[i] = newRow;
            }
            cols++; // Increase the number of columns
            cout << "Inventory expanded: +1 column!" << endl;
        } else {
            // Expand rows
            Item*** newItems = new Item**[rows + 1];
            for (int i = 0; i < rows; i++) {
                newItems[i] = items[i];
            }
            newItems[rows] = new Item*[cols];
            for (int j = 0; j < cols; j++) {
                newItems[rows][j] = nullptr; // Initialize the new row to nullptr
            }
            delete[] items;
            items = newItems;
            rows++; // Increase the number of rows
            cout << "Inventory expanded: +1 row!" << endl;
        }

        upgrades++; // Increment the upgrade count
        cost += 50; // Increase the cost for the next upgrade
        return true;
    }

    ~Inventory() {
        removeItems();

        for (int i = 0; i < rows; i++) {
            delete[] items[i];
        }

        delete[] items;
    }
};

int main() {

    Inventory inventory(4, 2);
    Item* shotgun = new Item("shotgun", 100, defensive);
    Item* pistol = new Item("pistol", 50, defensive);
    Item* coin = new Item("coin", 1, other);
    Item* sword = new Item("sword", 150, ofensive);

    inventory.addItem(shotgun);
    inventory.addItem(pistol);
    inventory.addItem(coin);
    inventory.addItem(sword);

    inventory.display();

    // // Test the inspect function
    // cout << endl;
    // inventory.inspect(shotgun);
    // inventory.inspect(pistol);
    // inventory.inspect(nullptr); // Example of inspecting a non-existent item

    // // Test the move function
    // cout << endl;
    // inventory.move(shotgun, 2, 1); // Move shotgun to position (2, 1)
    // inventory.display();

    // inventory.move(pistol, 3, 0); // Move pistol to position (3, 0)
    // inventory.display();

    // inventory.move(coin, 2, 1); // Attempt to move coin to an occupied position
    // inventory.display();

    // // Test the use function
    // cout << endl;
    // inventory.use(shotgun); // Use the shotgun
    // inventory.display();

    // inventory.use(pistol); // Use the pistol
    // inventory.display();

    // inventory.use(coin); // Use the coin
    // inventory.display();

    // inventory.use(shotgun); // Attempt to use an already used item

    // cout << "Before sorting:" << endl;
    // inventory.display();

    // // Test the sort function
    // cout << endl << "Sorting inventory by types..." << endl;
    // inventory.sort();

    // cout << "After sorting:" << endl;
    // inventory.display();

    // // Test the filter function
    // char input;
    // cout << "Enter the first letter to filter items: ";
    // cin >> input;
    // inventory.filter(input);

    int currency_amount = 155; // Example of currency. You can change it later on
    int expansionCost = 50; // Cost to expand the inventory. You can change it later on
    int upgrades = 0; // Number of upgrades performed

    // Test the expand function
    cout << "Current currency: " << currency_amount << endl;
    if (inventory.expand(currency_amount, expansionCost, upgrades)) {
        cout << "Expansion successful!" << endl;
    } else {
        cout << "Expansion failed!" << endl;
    }

    inventory.display();

    if (inventory.expand(currency_amount, expansionCost, upgrades)) {
        cout << "Expansion successful!" << endl;
    } else {
        cout << "Expansion failed!" << endl;
    }

    inventory.display();

    if (inventory.expand(currency_amount, expansionCost, upgrades)) {
        cout << "Expansion successful!" << endl;
    } else {
        cout << "Expansion failed!" << endl;
    }

    cout << "Remaining currency: " << currency_amount << endl;
    inventory.display();

    return 0;

    return 0;
}
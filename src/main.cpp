#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
        Magnifying_Glass() : Item("magnifying glass", 5, other) {
            this->description = "A tool used to show if bullet in chamber is live or blank.";
            this->image_path = "assets/magnifying_glass.png";
        }

        Magnifying_Glass(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Handsaw() : Item("handsaw", 25, ofensive) {
            this->description = "A tool used to saw output of shotgun so it would deal double damage.";
            this->image_path = "assets/handsaw.png";
        }

        Handsaw(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Beer() : Item("beer", 10, defensive) {
            this->description = "Empty one bullet from chamber of shotgun.";
            this->image_path = "assets/beer.png";
        }

        Beer(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Handcuffs() : Item("handcuffs", 20, defensive) {
            this->description = "Stops player for one turn (he cant do anything in his turn).";
            this->image_path = "assets/handcuffs.png";
        }

        Handcuffs(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Vodka() : Item("vodka", 33, other) {
            this->description = "Moves everyone inventories to one left and removes item - vodka.";
            this->image_path = "assets/vodka.png";
        }

        Vodka(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Sprite_Banana() : Item("sprite_banana", 75, other) {
            this->description = "Removes items from all inventories and remove this item.";
            this->image_path = "assets/sprite_banana.png";
        }

        Sprite_Banana(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Uno_Reverse() : Item("uno_reverse", 32, other) {
            this->description = "Swap two players inventories and remove this item.";
            this->image_path = "assets/uno_reverse.png";
        }

        Uno_Reverse(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Adrenaline() : Item("adrenaline", 12, defensive) {
            this->description = "Adds 2 lives to you for only one round in which you used it.";
            this->image_path = "assets/adrenaline.png";
        }

        Adrenaline(string name, int price, Types type, string image_path) : Item(name, price, type) {
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
        Cigarettes() : Item("cigarettes", 12, defensive) {
            this->description = "Pernamently heal one life in game.";
            this->image_path = "assets/cigarettes.png";
        }

        Cigarettes(string name, int price, Types type, string image_path) : Item(name, price, type) {
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

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }

    Item*** getItems() {
        return items;
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

    void displayDebug() {
        cout << "Inventory Debug View:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[";
                if (items[i][j] == nullptr) {
                    cout << " ";
                } else {
                    cout << items[i][j]->getName();
                }
                cout << "]";
            }
            cout << endl;
        }
        cout << flush; // Ensure everything prints
    }

    bool addItem(Item* item) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] == nullptr) {
                    items[i][j] = item;
                    cout << "Added item: " << item->getName() << " to position (" << i << ", " << j << ")" << endl;
                    return true;
                }
            }
        }
        cout << "Inventory is full! Could not add item: " << item->getName() << endl;
        return false; // Inventory is full
    }

    bool removeItem(int row, int col) {
        if ((row >= rows || row < 0) || (col < 0 || col >= cols)) {
            cout << "Invalid position for removal!" << endl;
            return false;
        }
        if (items[row][col] == nullptr) {
            cout << "No item to remove at position (" << row << ", " << col << ")!" << endl;
            return false;
        } else {
            cout << "Removing item: " << items[row][col]->getName() << " from position (" << row << ", " << col << ")" << endl;
            delete items[row][col];
            items[row][col] = nullptr; // Set to nullptr after deletion
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
            if (item->getName() == "magnifying glass") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "beer") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "handcuffs") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "vodka") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "sprite_banana") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "uno_reverse") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "adrenaline") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "cigarettes") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            }
            else if (item->getName() == "handsaw") {
                cout << "Inspecting item: " << item->getName() << endl;
                item->inspect();
            } else {
                cout << "Inspecting item: " << item->getName() << endl;
                item->display();
            }
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
                if (items[i][j] != nullptr && !items[i][j]->getName().empty() && items[i][j]->getName()[0] == input) {
                    cout << "Item found: " << items[i][j]->getName() << endl;
                    items[i][j]->display();
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
        Inventory* getInventory()
        {
            return inventory;
        }
        void display()
        {
            cout << "Player: " << name << ", Health: " << health << endl;
        }
};

class Bullet {
    public:
        virtual bool isLive() = 0;
        virtual ~Bullet() = default;
};

class LiveBullet : public Bullet {
public:
    bool isLive() override {
        return true;
    }
};

class BlankBullet : public Bullet {
public:
    bool isLive() override {
        return false;
    }
};

class Shotgun {
private:
    vector<Bullet*> chamber;

public:
    Shotgun() {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < 5; ++i) {
            if (rand() % 2 == 0) {
                chamber.push_back(new LiveBullet());
            } else {
                chamber.push_back(new BlankBullet());
            }
        }
    }

    ~Shotgun() {
        for (Bullet* bullet : chamber) {
            delete bullet;
        }
    }

    void displayChamber() {
        cout << "Shotgun chamber state: ";
        for (size_t i = 0; i < chamber.size(); ++i) {
            if (chamber[i]->isLive()) {
                cout << "[Live]";
            } else {
                cout << "[Blank]";
            }
            if (i < chamber.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    void shootSelf(Player* player) {
        if (chamber.empty()) {
            cout << "The shotgun is empty!" << endl;
            return;
        }

        Bullet* bullet = chamber.back();
        chamber.pop_back();

        if (bullet->isLive()) {
            player->setHealth(player->getHealth() - 1);
            cout << "Bang! " << player->getName() << " shot themselves and lost 1 health!" << endl;
        } else {
            cout << "Click! It was a blank bullet. " << player->getName() << " is unharmed." << endl;
        }

        delete bullet;
    }

    void shootOther(Player* shooter, Player* target) {
        if (chamber.empty()) {
            cout << "The shotgun is empty!" << endl;
            return;
        }

        Bullet* bullet = chamber.back();
        chamber.pop_back();

        if (bullet->isLive()) {
            target->setHealth(target->getHealth() - 1);
            cout << "Bang! " << shooter->getName() << " shot " << target->getName() << " and they lost 1 health!" << endl;
        } else {
            cout << "Click! It was a blank bullet. " << target->getName() << " is unharmed." << endl;
        }

        delete bullet;
    }
};

class Merchant {
    private:
        vector<Item*> merchant_items;
    public:
    Merchant(vector<Item*> allItems) {
        srand(time(0));

        while (merchant_items.size() < 3 && !allItems.empty()) {
            int randIndex = rand() % allItems.size();
            if (randIndex >= 0 && randIndex < allItems.size()) {
                merchant_items.push_back(allItems[randIndex]);
                allItems.erase(allItems.begin() + randIndex);
            }
        }
    }

    void displayItems() {
        cout << "Merchant's items:" << endl;
        for (int i = 0; i < merchant_items.size(); i++) {
            cout << i + 1 << ". " << merchant_items[i]->getName() << " - Price: " << merchant_items[i]->getPrice() << endl;

        }
    }

    void buyItem(Player* player) {
        displayItems();
        cout << "Your gold: " << player->getGold() << endl;
        cout << "Enter the number of the item you want to buy: ";
        int choice;
        cin >> choice;

        if (choice < 1 || choice > merchant_items.size()) {
            cout << "Index out of range!" << endl;
            return;
        }

        Item* selectedItem = merchant_items[choice - 1];

        if (player->getGold() < selectedItem->getPrice()) {
            cout << "Not enough gold!" << endl;
            return;
        }

        if (player->getInventory()->addItem(selectedItem)) {
            player->setGold(player->getGold() - selectedItem->getPrice());
            cout << "You bought " << selectedItem->getName() << "!" << endl;
        } else {
            cout << "Inventory is full!" << endl;
        }
    }

    void sellItem(Player* player) {
        cout << "Your Inventory:" << endl;
        player->getInventory()->displayDebug(); // Debugging output
        cout << "Enter the row and column of the item you want to sell (e.g., 0 1): ";
        int row, col;
        cin >> row >> col;

        if (row < 0 || row >= player->getInventory()->getRows() || col < 0 || col >= player->getInventory()->getCols()) {
            cout << "Invalid position!" << endl;
            return;
        }

        Item* itemToSell = player->getInventory()->getItems()[row][col];
        if (itemToSell == nullptr) {
            cout << "No item found at the given position!" << endl;
            return;
        }

        int sellPrice = itemToSell->getPrice() / 2; // Selling price is half the item's price
        player->setGold(player->getGold() + sellPrice);

        // Remove the item from the inventory
        if (player->getInventory()->removeItem(row, col)) {
            cout << "You sold the item for " << sellPrice << " gold!" << endl;
        } else {
            cout << "Failed to remove the item from the inventory!" << endl;
        }

        player->getInventory()->displayDebug(); // Debugging output after removal
    }
};

int main() {

    // Player player("John");

    // Inventory inventory(2, 4);
    // Item* shotgun = new Item("shotgun", 100, defensive);
    // Item* pistol = new Item("pistol", 50, defensive);
    // Item* coin = new Item("coin", 1, other);
    // Item* sword = new Item("sword", 150, ofensive);
    // Magnifying_Glass* magnifyingGlass = new Magnifying_Glass();

    // player.getInventory()->addItem(shotgun);
    // player.getInventory()->addItem(pistol);
    // player.getInventory()->addItem(coin);
    // player.getInventory()->addItem(sword);
    // player.getInventory()->addItem(magnifyingGlass);

    // player.getInventory()->display();

    // player.getInventory()->displayDebug();
    // player.getInventory()->removeItem(0, 0);
    // player.getInventory()->displayDebug();

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

    // int currency_amount = 155; // Example of currency. You can change it later on
    // int expansionCost = 50; // Cost to expand the inventory. You can change it later on
    // int upgrades = 0; // Number of upgrades performed

    // // Test the expand function
    // cout << "Current currency: " << currency_amount << endl;
    // if (inventory.expand(currency_amount, expansionCost, upgrades)) {
    //     cout << "Expansion successful!" << endl;
    // } else {
    //     cout << "Expansion failed!" << endl;
    // }

    // inventory.display();

    // if (inventory.expand(currency_amount, expansionCost, upgrades)) {
    //     cout << "Expansion successful!" << endl;
    // } else {
    //     cout << "Expansion failed!" << endl;
    // }

    // inventory.display();

    // if (inventory.expand(currency_amount, expansionCost, upgrades)) {
    //     cout << "Expansion successful!" << endl;
    // } else {
    //     cout << "Expansion failed!" << endl;
    // }

    // cout << "Remaining currency: " << currency_amount << endl;
    // inventory.display();

    // // Test the inspect function with the Magnifying Glass
    // cout << endl;
    // inventory.inspect(magnifyingGlass);
    // inventory.inspect(shotgun);

    // // Create a vector of all available items
    // vector<Item*> allItems = {
    //     new Magnifying_Glass(),
    //     new Handsaw(),
    //     new Beer(),
    //     new Handcuffs(),
    //     new Vodka(),
    //     new Sprite_Banana(),
    //     new Uno_Reverse(),
    //     new Adrenaline(),
    //     new Cigarettes()
    // };

    // player.setGold(100); // Give the player some starting gold

    // Merchant merchant(allItems);

    // cout << "Welcome to the Merchant!" << endl;
    // cout << "1. Buy an item" << endl;
    // cout << "2. Sell an item" << endl;
    // cout << "Enter your choice: ";
    // int choice;
    // cin >> choice;

    // if (choice == 1) {
    //     merchant.buyItem(&player);
    // } else if (choice == 2) {
    //     merchant.sellItem(&player);
    // } else {
    //     cout << "Invalid choice!" << endl;
    // }

    // player.getInventory()->display();

    // // Clean up dynamically allocated memory
    // for (Item* item : allItems) {
    //     delete item;
    // }

    Player player1("John");
    Player player2("Jane");

    Shotgun shotgun;

    cout << "Initial player states:" << endl;
    player1.display();
    player2.display();

    cout << "\nInitial shotgun chamber:" << endl;
    shotgun.displayChamber();

    cout << "\nJohn shoots himself:" << endl;
    shotgun.shootSelf(&player1);

    cout << "\nShotgun chamber after John shoots himself:" << endl;
    shotgun.displayChamber();

    cout << "\nJane shoots John:" << endl;
    shotgun.shootOther(&player2, &player1);

    cout << "\nShotgun chamber after Jane shoots John:" << endl;
    shotgun.displayChamber();

    cout << "\nFinal player states:" << endl;
    player1.display();
    player2.display();

    return 0;
}
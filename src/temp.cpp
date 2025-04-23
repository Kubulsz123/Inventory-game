
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



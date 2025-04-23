
#include <iostream>
#include <vector>
#include "items.hpp"

using namespace std;

#ifndef shop_hpp
#define shop_hpp

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

#endif
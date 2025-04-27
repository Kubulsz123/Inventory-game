#ifndef shop_hpp
#define shop_hpp

#include <vector>
#include <string>
#include "items.hpp"
#include "texture.hpp"
#include "button.cpp"
#include "player.hpp"

using namespace std;

class Merchant {
private:
    vector<Item*> merchant_items;
    vector<Button> itemButtons;
    vector<Texture> itemImages;    // Add: store item images
    vector<Texture> itemPrices;    // Add: store item prices text
public:
    Merchant(vector<Item*> allItems) {
        srand((unsigned int)time(0));

        while (merchant_items.size() < 3 && !allItems.empty()) {
            int randIndex = rand() % allItems.size();
            merchant_items.push_back(allItems[randIndex]);
            allItems.erase(allItems.begin() + randIndex);
        }

        // Setup Buttons, Images, and Price Texts
        float startX = 100.f;
        float startY = 150.f;
        float gap = 200.f;

        for (int i = 0; i < merchant_items.size(); i++) {
            Button itemButton(100, 100);  // Bigger button for image
            itemButton.setPosition(startX + i * gap, startY);
            itemButton.isActive = true;
            itemButtons.push_back(itemButton);

            // Load Item Image
            Texture img;
            img.loadFromFile(merchant_items[i]->getPath()); // Assuming Item has getImagePath()
            itemImages.push_back(img);

            // Create price text
            Texture priceText;
            priceText.loadFromRenderedText(
                to_string(merchant_items[i]->getPrice()) + " Gold", 
                {0x00, 0x00, 0x00, 0xFF}
            );
            itemPrices.push_back(priceText);
        }
    }

    void display() 
    {
        // Render Buttons, Item Images, and Prices
        for (int i = 0; i < itemButtons.size(); i++) {
            itemButtons[i].render();
            itemImages[i].render(itemButtons[i].getPositionX() + 5.f, itemButtons[i].getPositionY() + itemButtons[i].getHeight() + 5.f); // slight offset inside button

            // Render price below the button
            itemPrices[i].render(itemButtons[i].getPositionX() + 10.f, itemButtons[i].getPositionY() + itemButtons[i].getHeight() + 5.f);
        }
    }

    void handleEvent(SDL_Event* e, Player* player) {
        for (int i = 0; i < itemButtons.size(); i++) {
            itemButtons[i].handleEvent(e);
            if (itemButtons[i].ifClicked()) {
                buyItem(player, i);
            }
        }
    }

    void buyItem(Player* player, int index) {
        if (index < 0 || index >= merchant_items.size())
            return;

        Item* selectedItem = merchant_items[index];

        if (player->getGold() < selectedItem->getPrice()) {
            SDL_Log("Not enough gold!");
            return;
        }

        if (player->getInventory()->addItem(selectedItem)) {
            player->setGold(player->getGold() - selectedItem->getPrice());
            SDL_Log("Bought: %s", selectedItem->getName().c_str());
        } else {
            SDL_Log("Inventory full!");
        }
    }

    void sellItem(Player* player, int row, int col) {
        if (row < 0 || row >= player->getInventory()->getRows() || col < 0 || col >= player->getInventory()->getCols())
            return;

        Item* itemToSell = player->getInventory()->getItem(row,col);
        if (!itemToSell)
            return;

        int sellPrice = itemToSell->getPrice() / 2;
        player->setGold(player->getGold() + sellPrice);

        player->getInventory()->removeItem(row, col);

        SDL_Log("Sold item for %d gold!", sellPrice);
    }
};

#endif
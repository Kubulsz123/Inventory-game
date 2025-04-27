class Merchant {
    private:
        vector<Item*> merchant_items;
        vector<Button> itemButtons;
        vector<Texture> itemPrices;    
    
    public:
        Merchant(vector<Item*> allItems) {
            srand((unsigned int)time(0));
    
            float startX = 300.f;
            float startY = 300.f;
    
            while (merchant_items.size() < 3 && !allItems.empty()) {
                int randIndex = rand() % allItems.size();
                
                Item* selectedItem = allItems[randIndex];
                merchant_items.push_back(selectedItem);
                SDL_Log(selectedItem->getName().c_str());
                SDL_Log(selectedItem->getPath().c_str());
    
                // Setup Button
                Button itemButton(64, 64);
                itemButton.isActive = true;
                itemButton.setPosition(startX, startY);
                itemButton.setLabelAsPNG(selectedItem->getPath());
                itemButtons.push_back(itemButton);
    
                // Setup Price Text
                Texture priceText;
                priceText.loadFromRenderedText(to_string(selectedItem->getPrice()) + " Gold", {0x00, 0x00, 0x00, 0xFF});
                itemPrices.push_back(priceText);
    
                startX += 100.f;
    
                allItems.erase(allItems.begin() + randIndex);
            }
        }
    
        void display() 
        {
            float startX = 300.f;
            float startY = 300.f;
    
            // Display buttons and prices properly
            for (int i = 0; i < itemButtons.size(); i++) 
            {
                itemButtons[i].setPosition(startX, startY);  // Ensuring position is correctly set for each button
                itemButtons[i].render();
                itemPrices[i].render(startX, startY + 70.f);  // Adjust position for price text
                startX += 100.f;  // Move X position for next button
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
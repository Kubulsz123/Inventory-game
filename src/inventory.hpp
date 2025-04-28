#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "texture.hpp"
#include "items.hpp"
#include "Globals.hpp"
#include "button.cpp"

#ifndef inventory_hpp
#define inventory_hpp

Texture gPngTexture;
Texture slotTexture; 
Texture itemTexture;

using namespace std;

class Inventory {
    private:
        Item*** items;
        int rows;
        int cols;
        Button*** slotButtons;
        bool inventoryVisible = true;
        string inspectedItemName;
        string inspectedItemCoin;
        string inspectedItemDescription;
    public:
    Item* selectedItem = nullptr;  // Currently selected item for inspection/us
        bool showInspectBox = false;
        Button* inspectButton;  // Button for inspecting item
        Button* useButton;      // Button for using item
        bool inspectionEnded = false;
        Inventory(int rows, int cols) : rows{rows}, cols{cols} 
        {
            items = new Item**[rows];
            for (int i = 0; i < rows; i++) {
                items[i] = new Item*[cols];
                for (int j = 0; j < cols; j++) 
                {
                    items[i][j] = nullptr; 
                }
            }

            // Initialize buttons for each slot
            slotButtons = new Button**[rows];
            for (int i = 0; i < rows; i++) {
                slotButtons[i] = new Button*[cols];
                for (int j = 0; j < cols; j++) 
                {
                    slotButtons[i][j] = new Button(64,64); 
                }
            }
             // Initialize the inspect and use buttons (hidden by default)
            inspectButton = new Button(100, 50);  // Size of button (you can adjust this)
            useButton = new Button(100, 50);
            inspectButton->setLabel("Inspect");
            useButton->setLabel("Use");
            inspectButton->isActive = false; // Initially not active
            useButton->isActive = false;     // Initially not active
        }
        
        void setInventoryVisibility()
        {
            inventoryVisible = !inventoryVisible;
        }

        bool getInventoryVisibility()
        {
            return inventoryVisible;
        }
        int getRows() const 
        { 
            return rows; 
        }
        int getCols() const 
        { 
            return cols; 
        }
        Item* getItem(int row, int col) 
        { 
            return items[row][col]; 
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
                inspectedItemName = item->getName();
                inspectedItemCoin = "Gold: " + to_string(item->getPrice());
                SDL_Log(inspectedItemCoin.c_str());
                inspectedItemDescription = item->getDescription();
                SDL_Log(inspectedItemDescription.c_str());
                showInspectBox = true;
                inspectionEnded = false;
        
                hideInspectUseButtons();
            } else {
                cout << "Item not found!" << endl;
            }
        }

        void renderInspectBox()
        {
            if (showInspectBox)
            {
                SDL_FRect boxRect = { 340.f, 0.f, 180.f,165.f}; 
                SDL_SetRenderDrawColor(gRenderer, 150, 75, 0, 255); 
                SDL_RenderFillRect(gRenderer, &boxRect);


                SDL_SetRenderDrawColor(gRenderer,  0, 0, 0, 200);
                SDL_RenderRect(gRenderer, &boxRect);

                Texture nameText;
                nameText.loadFromRenderedText(inspectedItemName, {0, 0, 0, 200},28);
                nameText.render(boxRect.x + 10, boxRect.y + 10);

                Texture coinText;
                coinText.loadFromRenderedText(inspectedItemCoin.c_str(), { 0, 0, 0, 200},28);
                coinText.render(boxRect.x + 10, boxRect.y + 50);

                Texture descText;
                descText.loadWrappedText(inspectedItemDescription.c_str(), { 0, 0, 0, 200},180.f,18);
                descText.render(boxRect.x + 10, boxRect.y + 90);

                nameText.destroy();
                coinText.destroy();
                descText.destroy();
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
    
        void sort() {
            vector<Item*> temp;

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) 
                    {
                        if (items[i][j] != nullptr) 
                        {
                            temp.push_back(items[i][j]);
                            items[i][j] = nullptr;
                        }
                    }
            }

            std::sort(temp.begin(), temp.end(), [](Item* a, Item* b) -> bool 
            {
                return a->getType() < b->getType();
            });

            int index = 0;
            for (int i = 0; i < rows; i++) 
            {
                for (int j = 0; j < cols; j++) 
                {
                    if (index < temp.size()) 
                    {
                        items[i][j] = temp[index++];
                    }
                }
            }

            SDL_Log("Inventory sorted by item types!");
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
        Button*** getSlotButtons()
        {
            return slotButtons;
        }
        void handleSlotButtonsEvent(SDL_Event* e)
        {
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (slotButtons[i][j] != nullptr && slotButtons[i][j]->isActive)
                    {
                        slotButtons[i][j]->handleEvent(e);
                    }
                }
            }
        }

        void handleEscape(SDL_Event* e) {
            if (e->type == SDL_EVENT_KEY_DOWN && e->key.key == SDLK_ESCAPE) {
                hideInspectUseButtons();
            }
            if (showInspectBox)
            {
                showInspectBox = false;
                inspectionEnded = true;
            }
            
        }

        void setSlotButtonsPosition(float xPosition, float yPosition)
        {
            float startX = xPosition;
            for (int i = 0; i < rows; i++)
            {
                float tempX = startX;
                for (int j = 0; j < cols; j++)
                {
                    if (slotButtons[i][j] != nullptr)
                    {
                        slotButtons[i][j]->setPosition(tempX, yPosition);
                    }
                    tempX += 100.f;
                }
                yPosition += 100.f;
            }
        }
        
        void handleItemClick(SDL_Event* e,int currentTurn) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (slotButtons[i][j] != nullptr && slotButtons[i][j]->isActive) {
                        if (slotButtons[i][j]->ifClicked()) {
                            selectedItem = items[i][j];
                            if (selectedItem != nullptr) {
                                float xPosition = slotButtons[i][j]->getPositionX();
                                float yPosition = slotButtons[i][j]->getPositionY();
        
                               
                                if (currentTurn == 1 || currentTurn == 3) {
                                   
                                    xPosition -= 120; 
                                } else {
                                
                                    xPosition += 70;  
                                }
        
                                inspectButton->setPosition(xPosition, yPosition);
                                useButton->setPosition(xPosition, yPosition + 60);  
                                
                                inspectButton->isActive = true;
                                useButton->isActive = true;
                            }
                        }
                    }
                }
            }
        }
        void renderInspectUseButtons() {
            if (inspectButton->isActive) {
                inspectButton->render();
            }
            if (useButton->isActive) {
                useButton->render();
            }
        }

        void handleInspectUseEvent(SDL_Event* e) {
            if (inspectButton->isActive && inspectButton->ifClicked()) {
                if (selectedItem != nullptr) {
                    inspect(selectedItem);
                }
            }

            if (useButton->isActive) {
                if (selectedItem != nullptr) {
                    useButton->handleEvent(e);
                }
            }
        }

        void renderSlotButtons(float xPosition, float yPosition) {
            float startX = xPosition;
            for (int i = 0; i < rows; i++) {
                float tempX = startX;
                for (int j = 0; j < cols; j++) {
                    if (slotButtons[i][j] != nullptr && slotButtons[i][j]->isActive) {
                        slotButtons[i][j]->setPosition(tempX, yPosition);
                        if (items[i][j] != nullptr) {
                            
                            slotButtons[i][j]->setLabelAsPNG(items[i][j]->getPath());
                        }
                        slotButtons[i][j]->render();
                    }
                    tempX += 100.f;
                }
                yPosition += 100.f;
            }

            renderInspectUseButtons();

            renderInspectBox();
        }

        void hideInspectUseButtons() {
            inspectButton->isActive = false;
            useButton->isActive = false;
            selectedItem = nullptr; 
        }
};
#endif

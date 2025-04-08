#include <iostream>
#include <string>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "items.hpp"
#include "Globals.hpp"
#include "texture.hpp"

#ifndef inventory_hpp
#define inventory_hpp

Texture gPngTexture;
Texture slotTexture; 
Texture itemTexture;

class Inventory {
    private:
        Item*** items;
        int rows;
        int cols;
    public:
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
        }
    
        void display() 
        {
            //for (int i = 0; i < rows; i++) {
                //for (int j = 0; j < cols; j++) {
                //    cout << "[";
                //    if (items[i][j] == nullptr) {
                //        cout << " ";
                //   }
                //    else {
                //        cout << items[i][j]->getName()[0];
                //    }
                //    cout << "]";
                //}
            //    cout << endl;
            //}
            float tempXposition = 100.f;
            float tempYposition = 50.f;
            for (int i = 0; i < rows; i++) 
            {
                for (int j = 0; j < cols; j++) 
                {
                    if(items[i][j] == nullptr)
                    {
                        slotTexture.loadFromFile("assets/emptyItem.png");
                        slotTexture.setSize(55,55);
                        slotTexture.setColor(0,0,0);
                        slotTexture.render(tempXposition,tempYposition);
                    }
                    else
                    {
                        itemTexture.loadFromFile(items[i][j]->getPath());
                        itemTexture.setSize(55,55);
                        itemTexture.render(tempXposition,tempYposition);
                    }
                    tempXposition = tempXposition + 100.f;
                }
                tempXposition = 100.f;
                tempYposition = tempYposition + 100.f;
            }
        }
        bool addItem(Item* item) 
        {
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
    
        bool removeItem(int row, int col) 
        {
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
    
        int getInventoryValue() 
        {
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
    
        void removeItems() 
        {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (items[i][j] != nullptr) {
                        delete items[i][j];
                        items[i][j] == nullptr;
                    }
                }
            }
        }
    
        ~Inventory() 
        {
            removeItems();
    
            for (int i = 0; i < rows; i++) {
                delete[] items[i];
            }
    
            delete[] items;
        }
};

#endif
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>

#include "texture.hpp"
#include "Globals.hpp"

#ifndef button_cpp
#define button_cpp

class Button
{
    private:
        SDL_FPoint position;
        Texture sharedSprite;
        int lastState = -1;
        Texture labelText;
        Texture labelPng;
        string label;

    public:
        bool isActive = true;
        int kButtonWidth;
        int kButtonHeight;
        bool buttonClicked;
        bool isHovered;
        
        Button(int width,int height) :
            kButtonWidth{width},
            kButtonHeight{height},
            position{0.f, 0.f},
            buttonClicked(false),
            isHovered(false)
        {
            if (!sharedSprite.isLoaded())
            {   
                sharedSprite.loadFromFile("assets/emptyItem.png");
                sharedSprite.setSize(kButtonWidth, kButtonHeight);
                sharedSprite.setColor(0, 0, 0);
            }
        }
        void destroy()
        {
            sharedSprite.destroy();
        }

        Texture getSprite()
        {
            return sharedSprite;
        }

        float getPositionX()
        {
            return position.x;
        }

        bool ifClicked()
        {
            if (buttonClicked)
            {
                buttonClicked = false;
                return true;
            }
            return false;
        }
        float getPositionY()
        {
            return position.y;
        }
        void setPosition(float x, float y)
        {
            position.x = x;
            position.y = y;
        }
        void setLabel(const string& text, SDL_Color color = {0, 0, 0, 255})
        {
            label = text;
            labelText.destroy();
            labelText.loadFromRenderedText(text, color);
        }
        string setLabelAsPNG(string pathfile)
        {
            labelPng.destroy();
            labelPng.loadFromFile(pathfile);
            return pathfile;
        }
        void render()
        {
            
            if (!isActive) 
                return; // Prevent rendering when inactive

            int state = buttonClicked ? 2 : (isHovered ? 1 : 0);

            if (state != lastState) {
                switch (state) {
                    case 2: 
                        sharedSprite.setColor(100, 100, 100); 
                        break;
                    case 1: 
                        sharedSprite.setColor(200, 200, 200); 
                        break;
                    default: 
                        sharedSprite.setColor(255, 255, 255);
                        break;
                }
                lastState = state;
            }

            sharedSprite.render(position.x, position.y, nullptr);
            // Render the label centered
            if (labelText.isLoaded())
            {
                float textX = position.x + (kButtonWidth - labelText.getWidth()) / 2.f;
                float textY = position.y + (kButtonHeight - labelText.getHeight()) / 2.f;
                labelText.render(textX, textY);
            }
            if (labelPng.isLoaded())
            {
                float textX = position.x + (kButtonWidth - labelPng.getWidth()) / 2.f;
                float textY = position.y + (kButtonHeight - labelPng.getHeight()) / 2.f;
                labelPng.render(textX, textY);
            }
        }
        void handleEvent(SDL_Event* e)
        {
            if (!isActive) return; // Skip handling if inactive

            float x = -1.f, y = -1.f;
            SDL_GetMouseState(&x, &y);

            bool inside = x >= position.x && x <= position.x + kButtonWidth &&
                        y >= position.y && y <= position.y + kButtonHeight;

            if (e->type == SDL_EVENT_MOUSE_MOTION)
            {
                isHovered = inside;
            }
            else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN && inside)
            {
                buttonClicked = true;
            }
        }
        ~Button()
        {
            labelPng.destroy();
            labelText.destroy();
            destroy();
        }
};

#endif
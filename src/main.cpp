
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

#include "texture.hpp"
#include "Globals.hpp"
#include "inventory.hpp"
#include "items.hpp"
#include "player.hpp"

using namespace std;
constexpr int kScreenWidth{860};
constexpr int kScreenHeight{700};
constexpr int kScreenFps{60};

Inventory inventory(4,2);

class MButton
{
    private:
        SDL_FPoint position;
        Texture sprite;

    public:
        int kButtonWidth = 100;
        int kButtonHeight = 50;
        bool buttonClicked;
        bool isHovered;
        
        MButton()
        {
            this->position = {0.f,0.f};
            this->sprite = sprite;
            sprite.loadFromFile("assets/emptyItem.png");
            sprite.setSize(kButtonWidth,kButtonHeight);
            sprite.setColor(0,0,0);
        }

        Texture getSprite()
        {
            return sprite;
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
        void render()
        {
            if (buttonClicked)
            {
                sprite.setColor(100, 100, 100);
            }
            else if (isHovered)
            {
                sprite.setColor(200, 200, 200);
            }
            else
            {
                sprite.setColor(255, 255, 255);
            }

            sprite.render(position.x, position.y, nullptr);
        }
        void handleEvent(SDL_Event* e)
        {
            float x = -1.f, y = -1.f;
            SDL_GetMouseState(&x, &y);

            bool inside = x >= position.x && x <= position.x + kButtonWidth &&y >= position.y && y <= position.y + kButtonHeight;

            if (e->type == SDL_EVENT_MOUSE_MOTION)
            {
                isHovered = inside;
            }
            else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN && inside)
            {
                buttonClicked = true;
                return;
            }
        }

};

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( !SDL_Init( SDL_INIT_VIDEO ) )
    {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window with renderer
        if( !SDL_CreateWindowAndRenderer( "HomeShot Roulette", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer ) )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
        }
        else
        {
            //Initialize PNG loading
            if(!IMG_LoadTexture)
            {
                SDL_Log( "SDL_image could not initialize! SDL_image error: %s\n", SDL_GetError() );
                success = false;
            }
        }
    }
    return success;
}

void close()
{
    gPngTexture.destroy();
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    SDL_Quit();
}

int main( int argc, char* args[] )
{
    inventory.addItem(new Item("name",1,other,"assets/handsaw.png"));
    inventory.addItem(new Item("name",1,other,"assets/handsaw.png"));
    inventory.addItem(new Item("name",1,other,"assets/handsaw.png"));
    inventory.addItem(new Item("name",1,other,"assets/handsaw.png"));
    inventory.addItem(new Item("name",1,other,"assets/handsaw.png"));
    
    int exitCode = 0;
    if(!init())
    {
        exitCode = 1;
    }
    else
    {
        MButton button;
        button.setPosition(100.f,50.f);

        bool quit = false;
        
        SDL_Event e;
        SDL_zero(e);

        while(quit == false)
        {
            while(SDL_PollEvent(&e))
            {
                if( e.type == SDL_EVENT_QUIT )
                {
                    quit = true;
                }
                button.handleEvent(&e);
            }

            SDL_SetRenderDrawColor(gRenderer, 255, 200, 255, 255);
            SDL_RenderClear(gRenderer);

            button.render();

            if (button.ifClicked())
            {
                button.setPosition(1000,1000);
                inventory.setInventoryVisibility();
            }
            inventory.display();

            
            SDL_RenderPresent(gRenderer);
        } 
    }
    close();
    return exitCode;

}
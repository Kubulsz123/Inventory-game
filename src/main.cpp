//Using SDL and STL string
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

// Screen dimension constants
constexpr int kScreenWidth{860};
constexpr int kScreenHeight{700};
constexpr int kScreenFps{60};


/* Function Implementations */
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

// Loads media
bool loadMedia(string path)
{
    //File loading flag
    bool success = true;

    //Load splash image
    if( success = gPngTexture.loadFromFile(path); !success )
    {
        SDL_Log( "Unable to load png image!\n");
    }

    return success;
}

// Frees media and shuts down SDL
void close()
{
    //Clean up texture
    gPngTexture.destroy();
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    Inventory inventory(4,2);
    inventory.addItem(new Item("name",1,other,"assets/loaded.png"));
    inventory.addItem(new Item("name",1,other,"assets/loaded.png"));
    inventory.addItem(new Item("name",1,other,"assets/loaded.png"));
    inventory.addItem(new Item("name",1,other,"assets/loaded.png"));
    inventory.addItem(new Item("name",1,other,"assets/loaded.png"));

    int exitCode = 0;
    //Initialize
    if(!init())
    {
        SDL_Log("Unable to initialize program!\n");
        exitCode = 1;
    }
    else
    {
        //The quit flag
        bool quit = false;
        
        //The event data
        SDL_Event e;
        SDL_zero(e);

        //The main loop
        while(quit == false)
        {
            //Get event data
            while(SDL_PollEvent(&e))
            {
                //If event is quit type
                if( e.type == SDL_EVENT_QUIT )
                {
                    //End the main loop
                    quit = true;
                }
            }

            //Fill the background in color
            SDL_SetRenderDrawColor(gRenderer, 255, 200, 255, 255);
            SDL_RenderClear(gRenderer);

            inventory.display();
            
            SDL_RenderPresent(gRenderer);
        } 
    }
    close();
    return exitCode;

}
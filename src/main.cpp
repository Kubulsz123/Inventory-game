#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>


#include "texture.hpp"
#include "Globals.hpp"
#include "inventory.hpp"
#include "items.hpp"
#include "shotgun.hpp"
#include "button.cpp"
//#include "shop.hpp"
#include "player.hpp"

using namespace std;
constexpr int kScreenWidth{860};
constexpr int kScreenHeight{700};
constexpr int kScreenFps{30};

SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
class Timer
{
    private:
        //The clock time when the timer started
        Uint64 mStartTicks;

        //The ticks stored when the timer was paused
        Uint64 mPausedTicks;

        //The timer status
        bool mPaused;
        bool mStarted;
    public:
        //Initializes variables
        Timer():
            mStartTicks{0},
            mPausedTicks{0},
        
            mPaused{false},
            mStarted{false}
            {
            
            }

        //The various clock actions
        void start()
        {
            //Start the timer
            mStarted = true;

            //Unpause the timer
            mPaused = false;

            //Get the current clock time
            mStartTicks = SDL_GetTicksNS();
            mPausedTicks = 0;
        }
        void stop()
        {
            //Stop the timer
            mStarted = false;
        
            //Unpause the timer
            mPaused = false;
        
            //Clear tick variables
            mStartTicks = 0;
            mPausedTicks = 0;
        }
        void pause()
        {
            //If the timer is running and isn't already paused
            if(mStarted && !mPaused)
            {
                //Pause the timer
                mPaused = true;

                //Calculate the paused ticks
                mPausedTicks = SDL_GetTicksNS() - mStartTicks;
                mStartTicks = 0;
            }
        }
        void unpause()
        {
            //If the timer is running and paused
            if(mStarted && mPaused)
            {
                //Unpause the timer
                mPaused = false;

                //Reset the starting ticks
                mStartTicks = SDL_GetTicksNS() - mPausedTicks;

                //Reset the paused ticks
                mPausedTicks = 0;
            }
        }
        //Gets the timer's time
        Uint64 getTicksNS()
        {
            //The actual timer time
            Uint64 time = 0;

            //If the timer is running
            if(mStarted)
            {
                //If the timer is paused
                if(mPaused)
                {
                    //Return the number of ticks when the timer was paused
                    time = mPausedTicks;
                }
                else
                {
                    //Return the current time minus the start time
                    time = SDL_GetTicksNS() - mStartTicks;
                }
            }
            return time;
        }
        //Checks the status of the timer
        bool isStarted()
        {
            return mStarted;
        }
        bool isPaused()
        {
            return mPaused;
        }
};
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( !SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window with renderer
        if(!SDL_CreateWindowAndRenderer("HomeShot Roulette", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer))
        {
            SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
        }
        else
        {
            //Initialize PNG loading
            if(!IMG_LoadTexture)
            {
                SDL_Log("SDL_image could not initialize! SDL_image error: %s\n", SDL_GetError());
                success = false;
            }
            //Initialize font loading
            if(!TTF_Init())
            {
                SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}
void close()
{
    TTF_CloseFont(gFont);
    gFont = nullptr;

    gPngTexture.destroy();
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    
    int exitCode = 0;
    if(!init())
    {
        exitCode = 1;
    }
    else
    {
        bool loaded = false;
        //turn meter
        int currentTurn = 0;
        Texture currentTurnText;

        Uint64 showTimeStart;
        bool shown = false;

        Shotgun shotgun;
        Button shotgunButt(140,50);
        shotgunButt.setPosition(365.f,340.f);

        Button shoot(100,50);
        shoot.setLabel("Shoot",{0x00, 0x00, 0x00, 0xFF});

        shoot.isActive = false;

        //player selection//
        int selectedPlayers = 0;
        vector<string> playerNames;
        int currentPlayerIndex = 0;
        bool nameSaved = false;

        //inventory show
        vector<Player*> players;
        bool inventoriesRendered = false;

        //Textures
        Texture menu;
        Texture title; 
        Texture optionsPlayers;
        Texture gInputTextTexture;
        Texture gPromptTextTexture;
        Texture tempGuide;

        menu.loadFromFile("assets/homeshotmenu.png");
        //buttons
        Button Player1(100,50);
        Button Player2(100,50);
        Button Player3(100,50);
        Button Player4(100,50);

        Player1.isActive = false;
        Player2.isActive = false;
        Player3.isActive = false;
        Player4.isActive = false;

        Button Startbutton(200,50);
        Button HowToPlay(200,50);
        Button BackToMenu(200,50);

        BackToMenu.isActive = false;
        BackToMenu.setPosition(330.f,600.f);
        BackToMenu.setLabel("Back to menu");

        Button Player1Name(140,50);
        Button Player2Name(140,50);
        Button Player3Name(140,50);
        Button Player4Name(140,50);

        bool shootVisible = false;
        bool targetSelection = false;

        if(!loaded)
        {
            shotgunButt.setLabelAsPNG("assets/shotgun.png");
            title.loadFromRenderedText("Homeshot Roulette",textColor);
            optionsPlayers.loadFromRenderedText("Select number of Players:",textColor);
            tempGuide.loadFromRenderedText("Temp Guide",textColor);
            loaded = true;
        }
        
        //booleans
        bool quit = false;
        bool showTitle = true;
        bool showOption = false;
        bool playerInput = false;
        bool guideVisible = false;
        bool start = true;
        bool menuVisible = true;
        bool textUndShotgun = false;

        SDL_Event e;
        SDL_zero(e);

        //Timer to cap frame rate
        Timer capTimer;
        
        string kStartingText = "";

        //The current input text
        string inputText = kStartingText;

        //Enable text input
        SDL_StartTextInput(gWindow);

        while(quit == false)
        {
            //Start frame time
            capTimer.start();

            //The rerendering text flag
            bool renderText = false;

            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_EVENT_QUIT)
                {
                    quit = true;
                }
                else if(e.type == SDL_EVENT_KEY_DOWN)
                {

                    if(e.key.key == SDLK_BACKSPACE && inputText.length() > 0)
                    {
                        inputText.pop_back();
                        renderText = true;
                    }
                    else if (e.key.key == SDLK_RETURN)
                    {
                        if (inputText.length() >= 4 && playerInput && currentPlayerIndex < selectedPlayers)
                        {
                            playerNames[currentPlayerIndex] = inputText;
                            currentPlayerIndex++;
                            inputText.clear();
                            renderText = true;

                            if (currentPlayerIndex >= selectedPlayers)
                            {
                                playerInput = false;

                                // Use playerNames[] for game setup
                                for (int i = 0; i < selectedPlayers; ++i)
                                {
                                    SDL_Log("Player %d name: %s", i + 1, playerNames[i].c_str());
                                    players.push_back(new Player(playerNames[i]));
                                }
                                shown = true;
                                showTimeStart = SDL_GetTicks();
                            }
                        }
                    }
                    else if(e.key.key == SDLK_C && SDL_GetModState() & SDL_KMOD_CTRL)
                    {
                        SDL_SetClipboardText(inputText.c_str());
                    }
                    else if(e.key.key == SDLK_V && SDL_GetModState() & SDL_KMOD_CTRL)
                    {
                        char* tempText = SDL_GetClipboardText();
                        inputText = tempText;
                        SDL_free(tempText);
                        renderText = true;
                    }
                }
                else if(e.type == SDL_EVENT_TEXT_INPUT)
                {
                    char firstChar = toupper(e.text.text[0]);
                    if(!(SDL_GetModState() & SDL_KMOD_CTRL && (firstChar == 'C' || firstChar == 'V')))
                    {
                        if (inputText.length() < 9)
                        {   
                            inputText += e.text.text;
                            renderText = true;
                        }
                    }
                }
                // Other event handling
                Startbutton.handleEvent(&e);
                HowToPlay.handleEvent(&e);
                Player1.handleEvent(&e);
                Player2.handleEvent(&e);
                Player3.handleEvent(&e);
                Player4.handleEvent(&e);
                BackToMenu.handleEvent(&e);
                shotgunButt.handleEvent(&e);

                if(shootVisible)
                {
                    shoot.handleEvent(&e);
                }

                if (targetSelection) 
                {
                    Player1Name.handleEvent(&e);
                    Player2Name.handleEvent(&e);
                    Player3Name.handleEvent(&e);
                    Player4Name.handleEvent(&e);
                }
            }
            if (renderText)
            {
                // Clear the old texture if any
                gInputTextTexture.destroy();

                if (inputText != "")
                {
                    gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
                }
                else
                {
                    gInputTextTexture.loadFromRenderedText(" ",textColor); // Render space so box isn't empty
                }
            }

            SDL_SetRenderDrawColor(gRenderer, 255, 200, 255, 255);
            SDL_RenderClear(gRenderer);

            if(menuVisible)
            {
                menu.render(0.f,0.f);
            }

            if(start)
            {
                Startbutton.setPosition(320.f,300.f);
                Startbutton.setLabel("Start");

                HowToPlay.setPosition(320.f,400.f);
                HowToPlay.setLabel("How to play?");

                Startbutton.render();
                HowToPlay.render();
            }
            if(showTitle)
            {
                title.render(300.f,200.f);
            }

            if (Startbutton.ifClicked())
            {
                Startbutton.isActive = false;
                showTitle = false;
                HowToPlay.isActive = false;
                start = false;
                
                Player1.setPosition(370.f,200.f);
                Player1.setLabel("1");

                Player2.setPosition(370.f,300.f);
                Player2.setLabel("2");

                Player3.setPosition(370.f,400.f);
                Player3.setLabel("3");

                Player4.setPosition(370.f,500.f);
                Player4.setLabel("4");

                Startbutton.isActive = false;
                showTitle = false;
                HowToPlay.isActive = false;
                showOption = true;

                Player1.isActive = true;
                Player2.isActive = true;
                Player3.isActive = true;
                Player4.isActive = true;
            }
            if(showOption)
            {
                optionsPlayers.render(255.f,100.f);
            }
            if(Player1.isActive)
            {
                Player1.render();
                Player2.render();
                Player3.render();
                Player4.render();
            }
            if (playerInput)
            {
                string prompt = "Enter name for Player " + to_string(currentPlayerIndex + 1) + " (min 4 characters):";
                gPromptTextTexture.loadFromRenderedText(prompt, textColor);
                gPromptTextTexture.render(140.f, 250.f);
                gInputTextTexture.render(370.f, 300.f);
            }

            if(HowToPlay.ifClicked())
            {
                HowToPlay.isActive = false;
                Startbutton.isActive = false;
                showTitle = false;
                guideVisible = true;
                start = false;
                BackToMenu.isActive = true;
            }
            if(guideVisible)
            {
                tempGuide.render(200.f,100.f);
            }
            if(BackToMenu.isActive)
            {
                BackToMenu.render();
            }
            if(BackToMenu.ifClicked())
            {
                Startbutton.isActive = true;
                showTitle = true;
                start = true;
                HowToPlay.isActive = true;
                guideVisible = false;
                BackToMenu.isActive = false;
            }

            if (Player1.ifClicked()) {
                selectedPlayers = 1;
                playerInput = true;
                playerNames.resize(selectedPlayers);
                
                showOption = false;
                Player1.isActive = false;
                Player2.isActive = false;
                Player3.isActive = false;
                Player4.isActive = false;
            }
            else if (Player2.ifClicked()) {
                selectedPlayers = 2;
                playerInput = true;
                playerNames.resize(selectedPlayers);

                showOption = false;
                Player1.isActive = false;
                Player2.isActive = false;
                Player3.isActive = false;
                Player4.isActive = false;
            }
            else if (Player3.ifClicked()) {
                selectedPlayers = 3;
                playerInput = true;
                playerNames.resize(selectedPlayers);

                showOption = false;
                Player1.isActive = false;
                Player2.isActive = false;
                Player3.isActive = false;
                Player4.isActive = false;
            }
            else if (Player4.ifClicked()) {
                selectedPlayers = 4;
                playerInput = true;
                playerNames.resize(selectedPlayers);

                showOption = false;
                Player1.isActive = false;
                Player2.isActive = false;
                Player3.isActive = false;
                Player4.isActive = false;
            }

            if(!playerInput && !showOption && Startbutton.isActive == false && !guideVisible)
            {
                //selectedPlayers number
                //playerNames vector of players names
                menuVisible = false;
                float tempXpositon = 10.f;
                float tempYposition = 10.f;

                if(selectedPlayers == 4)
                {
                    for(int i = 0;i < players.size(); i++)
                    {

                        if(players[i]->dirty == true)
                        {
                            players[i]->nameText.loadFromRenderedText(players[i]->getName(), {0x00, 0x00, 0x00, 0xFF});
                            players[i]->healthText.loadFromRenderedText("Health: " + to_string(players[i]->getHealth()), {0x00, 0x00, 0x00, 0xFF});
                            players[i]->coinText.loadFromRenderedText("Gold: " + to_string(players[i]->getGold()), {0x00, 0x00, 0x00, 0xFF});
                            players[i]->dirty = false;
                        }

                        if(i == 0)
                        {
                            if(players[i]->nameVisibly == true)
                            {
                                players[i]->nameText.render(tempXpositon + 180.f,tempYposition + 100.f);
                            }
                            players[i]->getInventory()->display(tempXpositon,tempYposition);
                            players[i]->healthText.render(tempXpositon + 180.f,tempYposition + 130.f);
                            players[i]->coinText.render(tempXpositon + 180.f,tempYposition + 160.f);
                        }
                        if(i == 1)
                        {
                            tempXpositon = tempXpositon + 660.f;
                            if(players[i]->nameVisibly == true)
                            {
                                players[i]->nameText.render(tempXpositon - 150.f,tempYposition + 100.f);
                            }
                            players[i]->getInventory()->display(tempXpositon,tempYposition);
                            players[i]->healthText.render(tempXpositon - 150.f,tempYposition + 130.f);
                            players[i]->coinText.render(tempXpositon - 150.f,tempYposition + 160.f);
                        }
                        if(i == 2)
                        {
                            tempXpositon = 10.f;
                            tempYposition = tempYposition + 420.f;
                            if(players[i]->nameVisibly == true)
                            {
                                players[i]->nameText.render(tempXpositon + 180.f,tempYposition + 100.f);
                            }
                            players[i]->getInventory()->display(tempXpositon,tempYposition);
                            players[i]->healthText.render(tempXpositon + 180.f,tempYposition + 130.f);
                            players[i]->coinText.render(tempXpositon + 180.f,tempYposition + 160.f);
                        }
                        if(i == 3)
                        {
                            tempXpositon = tempXpositon + 660.f;
                            if(players[i]->nameVisibly == true)
                            {
                                players[i]->nameText.render(tempXpositon - 150.f,tempYposition + 100.f);
                            }
                            players[i]->getInventory()->display(tempXpositon,tempYposition);
                            players[i]->healthText.render(tempXpositon - 150.f,tempYposition + 130.f);
                            players[i]->coinText.render(tempXpositon - 150.f,tempYposition + 160.f);
                        }
                    }
                }
                //if(selectedPlayers == 3)
                //{}
                //if(selectedPlayers == 2)
                //{}
                //if(selectedPlayers == 1)
                //{}
                shotgunButt.render();
                if (!players.empty()) 
                {
                    string turnText = players[currentTurn]->getName() + "'s Turn";
                    currentTurnText.loadFromRenderedText(turnText.c_str(), {0x00, 0x00, 0x00, 0xFF});
                    currentTurnText.render(10.f,340.f);
                }
                if (shotgunButt.ifClicked() && !shown && !shootVisible && !targetSelection) {
                    shootVisible = true;
                    shoot.isActive = true;
                    shoot.setPosition(shotgunButt.getPositionX() + 160.f, shotgunButt.getPositionY());
                }
                if (shootVisible && shoot.ifClicked()) {
                    shootVisible = false;
                    shoot.isActive = false;
                    targetSelection = true;
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->nameVisibly = false;
                    }
                
                    Player1Name.setLabel(players[0]->getName());
                    Player1Name.setPosition(190.f, 80.f);
                    Player1Name.isActive = true;
                
                    Player2Name.setLabel(players[1]->getName());
                    Player2Name.setPosition(510.f, 80.f);
                    Player2Name.isActive = true;
                
                    Player3Name.setLabel(players[2]->getName());
                    Player3Name.setPosition(190.f, 500.f);
                    Player3Name.isActive = true;
                
                    Player4Name.setLabel(players[3]->getName());
                    Player4Name.setPosition(510.f, 500.f);
                    Player4Name.isActive = true;
                }
                if (shootVisible) {
                    shoot.render();
                }
                
                if (targetSelection) {
                    Player1Name.render();
                    Player2Name.render();
                    Player3Name.render();
                    Player4Name.render();
                }
                if (Player1Name.ifClicked()) {
                    SDL_Log("Player 1 targeted!");
                    if(players[currentTurn] == players[0])
                    {
                        int tempHealth = players[currentTurn]->getHealth();
                        shotgun.shootSelf(players[currentTurn]);
                        if(tempHealth != players[currentTurn]->getHealth())
                        {
                            if(currentTurn == 3)
                            {
                                currentTurn = 0;
                            }
                            else
                            {
                                currentTurn += 1;
                            }
                        }
                    }
                    else
                    {
                        shotgun.shootOther(players[currentTurn],players[0]);
                        if(currentTurn == 3)
                        {
                            currentTurn = 0;
                        }
                        else
                        {
                            currentTurn += 1;
                        }
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->nameVisibly = true;
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->dirty = true;
                    }
                    targetSelection = false;
                    textUndShotgun = true;
                }
                if (Player2Name.ifClicked()) {
                    SDL_Log("Player 2 targeted!");
                    if(players[currentTurn] == players[1])
                    {
                        int tempHealth = players[currentTurn]->getHealth();
                        shotgun.shootSelf(players[currentTurn]);
                        if(tempHealth != players[currentTurn]->getHealth())
                        {
                            if(currentTurn == 3)
                            {
                                currentTurn = 0;
                            }
                            else
                            {
                                currentTurn += 1;
                            }
                        }
                    }
                    else
                    {
                        shotgun.shootOther(players[currentTurn],players[1]);
                        if(currentTurn == 3)
                        {
                            currentTurn = 0;
                        }
                        else
                        {
                            currentTurn += 1;
                        }
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->nameVisibly = true;
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->dirty = true;
                    }
                    textUndShotgun = true;
                    targetSelection = false;
                }
                if (Player3Name.ifClicked()) {
                    SDL_Log("Player 3 targeted!");
                    if(players[currentTurn] == players[2])
                    {
                        int tempHealth = players[currentTurn]->getHealth();
                        shotgun.shootSelf(players[currentTurn]);
                        if(tempHealth != players[currentTurn]->getHealth())
                        {
                            if(currentTurn == 3)
                            {
                                currentTurn = 0;
                            }
                            else
                            {
                                currentTurn += 1;
                            }
                        }
                    }
                    else
                    {
                        shotgun.shootOther(players[currentTurn],players[2]);
                        if(currentTurn == 3)
                        {
                            currentTurn = 0;
                        }
                        else
                        {
                            currentTurn += 1;
                        }
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->nameVisibly = true;
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->dirty = true;
                    }
                    textUndShotgun = true;
                    targetSelection = false;
                }
                if (Player4Name.ifClicked()) {
                    SDL_Log("Player 4 targeted!");
                    if(players[currentTurn] == players[3])
                    {
                        int tempHealth = players[currentTurn]->getHealth();
                        shotgun.shootSelf(players[currentTurn]);
                        if(tempHealth != players[currentTurn]->getHealth())
                        {
                            if(currentTurn == 3)
                            {
                                currentTurn = 0;
                            }
                            else
                            {
                                currentTurn += 1;
                            }
                        }
                    }
                    else
                    {
                        shotgun.shootOther(players[currentTurn],players[3]);
                        if(currentTurn == 3)
                        {
                            currentTurn = 0;
                        }
                        else
                        {
                            currentTurn += 1;
                        }
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->nameVisibly = true;
                    }
                    for(int i = 0; i < players.size(); i++)
                    {
                        players[i]->dirty = true;
                    }

                    targetSelection = false;
                    textUndShotgun = true;
                }
            }
            if(textUndShotgun)
            {
                shotgun.getText().render(365.f,400.f);
            }
            if(shown)
            {
                shotgun.displayChamber();
                SDL_Log("Showing shotgun chamber...");
                if (SDL_GetTicks() - showTimeStart > 3000) {
                    shown = false;
                    shotgun.sortBullets();
                }
            }

            SDL_RenderPresent(gRenderer);

            //Cap frame rate
            constexpr Uint64 nsPerFrame = 1000000000 / kScreenFps; 
            Uint64 frameNs = capTimer.getTicksNS();
            if(frameNs < nsPerFrame)
            {
                SDL_DelayNS(nsPerFrame - frameNs);
            }
        } 
        //Disable text input
        SDL_StopTextInput(gWindow);
    }
    close();
    return exitCode;
    
}
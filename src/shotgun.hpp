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
#include "player.hpp"

using namespace std;

#ifndef shotgun_hpp
#define shotgun_hpp

class Bullet 
{
    private:
        string pathfile;
    public:
        Texture bullet;
        virtual bool isLive() = 0;
        virtual ~Bullet() = default;
};

class LiveBullet : public Bullet 
{
    private:
        string pathfile = "assets/livebullet.png";
    public:
        LiveBullet()
        {
            bullet.loadFromFile(pathfile);
        }
        bool isLive() override {
            return true;
        }
};

class BlankBullet : public Bullet 
{
    private:
        string pathfile = "assets/blankbullet.png";
    public:
        BlankBullet()
        {
            bullet.loadFromFile(pathfile);
        }
        bool isLive() override {
            return false;
        }
};

class Shotgun {
    private:
        vector<Bullet*> chamber;
        Texture shotgun;
        string pathfile = "assets/shotgun.png";
        Texture text;

    public:
        Shotgun() {
            srand(static_cast<unsigned>(time(0)));
            for (int i = 0; i < 6; ++i) {
                if (rand() % 2 == 0) {
                    chamber.push_back(new LiveBullet());
                } else {
                    chamber.push_back(new BlankBullet());
                }
            }
            shotgun.loadFromFile(pathfile);
        }

        Texture getText()
        {
            return text;
        }
        
        void sortBullets() 
        {
            for (int i = 0; i < chamber.size(); ++i) 
            {
                int j = rand() % chamber.size();
                swap(chamber[i], chamber[j]);
            }
            for (int i = 0; i < chamber.size(); ++i) 
            {
                SDL_Log(to_string(chamber[i]->isLive()).c_str());
            }
        }

        void reload()
        {
            chamber.clear();
            for (int i = 0; i < 6; ++i) 
            {
                if (rand() % 2 == 0) 
                {
                    chamber.push_back(new LiveBullet());
                }
                else
                {
                    chamber.push_back(new BlankBullet());
                }
            }
        }

        ~Shotgun() {
            for (Bullet* bullet : chamber) {
                delete bullet;
            }
        }

        void displayChamber() {

            float x = 520.f;
            for (int i = 0; i < chamber.size(); ++i) 
            {
                chamber[i]->bullet.setSize(25,25);
                chamber[i]->bullet.render(x,360.f);
                x = x + 40.f;
            }
        }
    
        bool shootSelf(Player* player) {
            if (chamber.empty()) {
                cout << "The shotgun is empty!" << endl;
                return false;
            }
    
            Bullet* bullet = chamber.back();
            chamber.pop_back();
    
            if (bullet->isLive()) {
                player->setHealth(player->getHealth() - 1);
                text.loadFromRenderedText("Self fire!",{0x00, 0x00, 0x00, 0xFF});
            } else {
                text.loadFromRenderedText("Click",{0x00, 0x00, 0x00, 0xFF});
                player->setGold(1);
            }
    
            delete bullet;
            return true;
        }
    
        bool shootOther(Player* shooter, Player* target) {
            if (chamber.empty()) {
                return false;
            }
    
            Bullet* bullet = chamber.back();
            chamber.pop_back();
    
            if (bullet->isLive()) {
                target->setHealth(target->getHealth() - 1);
                text.loadFromRenderedText("Bang",{0x00, 0x00, 0x00, 0xFF});
                shooter->setGold(1);
            } else {
                text.loadFromRenderedText("Click",{0x00, 0x00, 0x00, 0xFF});
            }
    
            delete bullet;
            return true;
        }
};

#endif
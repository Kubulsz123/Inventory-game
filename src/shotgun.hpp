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
        bool doubleDamageEnabled = false;

        // For temporary rendering (for 5 seconds)
        Bullet* revealedBullet = nullptr;
        Uint32 revealStartTime = 0;
        bool bulletRevealed = false;

        bool chamberShow = true;

        int removedBulletsCount = 0;
        Uint32 removalStartTime = 0;
        bool bulletRemoved = false;

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

        const vector<Bullet*>& getChamber() const
        {
            return chamber;
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
            chamberShow = true;
        }

        ~Shotgun() {
            for (Bullet* bullet : chamber) {
                delete bullet;
            }
        }

        void displayChamber() {

            if(chamberShow)
            {
                float x = 520.f;
                for (int i = 0; i < chamber.size(); ++i) 
                {
                    chamber[i]->bullet.setSize(25,25);
                    chamber[i]->bullet.render(x,360.f,nullptr,270.f);
                    x = x + 40.f;
                }
                chamberShow = false;
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
                int damage = doubleDamageEnabled ? 2 : 1;
                player->setHealth(player->getHealth() - damage);
            } else {
                player->setGold(1);
            }
            
            if(doubleDamageEnabled)
            {
                doubleDamageEnabled = false;
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
                int damage = doubleDamageEnabled ? 2 : 1;
                target->setHealth(target->getHealth() - damage);
                shooter->setGold(1);
            }

            if(doubleDamageEnabled)
            {
                doubleDamageEnabled = false;
            }
    
            delete bullet;
            return true;
        }

        void revealNextBullet() {
            if (!chamber.empty()) {
                if (revealedBullet) {
                    delete revealedBullet;
                }
                if (chamber.back()->isLive()) {
                    revealedBullet = new LiveBullet();
                } else {
                    revealedBullet = new BlankBullet();
                }
                revealStartTime = SDL_GetTicks();
                bulletRevealed = true;
            }
        }
    
        void enableDoubleDamage() {
            doubleDamageEnabled = true;
        }
    
        void removeLastBullet() {
            if (!chamber.empty()) {
                Bullet* first = chamber.back();
                chamber.pop_back();
    
                removedBulletsCount++;
                removalStartTime = SDL_GetTicks();
                bulletRemoved = true;
            }
        }
    
};

#endif
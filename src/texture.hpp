#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

#include "Globals.hpp"

#ifndef texture_hpp
#define texture_hpp

using namespace std;
class Texture
{
    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
        bool loaded;
    public:
        Texture():
            mTexture{nullptr},
            mWidth{0},
            mHeight{0},
            loaded{false}
        {}
        void destroy()
        {
            if (mTexture)
            {
                SDL_DestroyTexture(mTexture);
                mTexture = nullptr;
            }
            mWidth = 0;
            mHeight = 0;
            loaded = false;
        }
        ~Texture()
        {
            destroy();
        }
        bool isLoaded() const
        {
            return loaded;
        }
        bool loadFromFile(string path)
        {
            destroy();

            loaded = false;

            SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            if (!loadedSurface)
            {
                SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
                return false;
            }

            mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
            if (!mTexture)
            {
                SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
                SDL_DestroySurface(loadedSurface);
                return false;
            }

            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
            loaded = true;

            SDL_DestroySurface(loadedSurface);
            return true;
        }
        bool loadFromRenderedText(const std::string& textureText, SDL_Color textColor)
        {
            destroy();
            string fontPath = "assets/lazy.ttf";
            if(gFont = TTF_OpenFont(fontPath.c_str(), 28); gFont == nullptr)
            {
                SDL_Log( "Could not load %s! SDL_ttf Error: %s\n", fontPath.c_str(), SDL_GetError());
            }

            SDL_Surface* textSurface = TTF_RenderText_Blended(gFont, textureText.c_str(),textureText.length(), textColor);
            if (textSurface == nullptr)
            {
                SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n", SDL_GetError());
                return false;
            }

            mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
            if (mTexture == nullptr)
            {
                SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
                SDL_DestroySurface(textSurface);
                return false;
            }

            mWidth = textSurface->w;
            mHeight = textSurface->h;
            loaded = true;

            SDL_DestroySurface(textSurface);
            return true;
        }
        void setSize(int width, int height)
        {
            this->mWidth = width;
            this->mHeight = height;
        }
        void setColor(Uint8 r, Uint8 g, Uint8 b)
        {
            SDL_SetTextureColorMod(mTexture, r, g, b);
        }

        void render(float x, float y, SDL_FRect* clip = nullptr)
        {
            //Set texture position
            SDL_FRect dstRect = {x, y, static_cast<float>(this->mWidth), static_cast<float>(this->mHeight)};

            if (clip != nullptr) 
            {
                dstRect.w = clip->w;
                dstRect.h = clip->h;
            } 
            if( mWidth > 0 )
            {
                dstRect.w = mWidth;
            }
            if( mHeight > 0 )
            {
                dstRect.h = mHeight;
            }
            SDL_RenderTexture(gRenderer,mTexture,clip,&dstRect);
        }

        int getWidth()
        {
            return mWidth;
        }
        int getHeight()
        {
            return mHeight;
        }
};


#endif
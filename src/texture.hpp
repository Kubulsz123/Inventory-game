#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
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
    public:
        //Initializes texture variables
        Texture():
            mTexture{nullptr},
            mWidth{0},
            mHeight{0}
        {

        }
        //Cleans up texture variables
        ~Texture()
        {
            destroy();
        }
        //Loads texture from disk
        bool loadFromFile(string path)
        {
            //Clean up texture if it already exists
            destroy();

            //Load surface
            if( SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr)
            {
                SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
            }
            else
            {
                //Create texture from surface
                if(mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr)
                {
                    SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
                }
                else
                {
                    //Get image dimensions
                    mWidth = loadedSurface->w;
                    mHeight = loadedSurface->h;
                }

                //Clean up loaded surface
                SDL_DestroySurface(loadedSurface);
            
            }

            //Return success if texture loaded
            return mTexture != nullptr;
        }
        //Set width and height
        void setSize(int width, int height)
        {
            this->mWidth = width;
            this->mHeight = height;
        }

        //Cleans up texture
        void destroy()
        {
            //Clean up texture
            SDL_DestroyTexture(this->mTexture);
            this->mTexture = nullptr;
            this->mWidth = 0;
            this->mHeight = 0;
        }
        void setColor(Uint8 r, Uint8 g, Uint8 b)
        {
            SDL_SetTextureColorMod(mTexture, r, g, b);
        }

        //Draws texture
        void render(float x, float y, SDL_FRect* clip = nullptr)
        {
            //Set texture position
            SDL_FRect dstRect = {x, y, static_cast<float>(this->mWidth), static_cast<float>(this->mHeight)};

            if (clip != nullptr) 
            {
                // SDL_RenderCopyF for floating-point precision rendering with SDL_FRect
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

        //Gets texture dimensions
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
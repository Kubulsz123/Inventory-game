/* Headers */
//Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{720};
constexpr int kScreenHeight{580};

/* Global Variables */
// The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

// The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

// The image we will load and show on the screen
SDL_Surface* gHelloWorld{ nullptr };

SDL_Renderer* gRenderer{ nullptr };
class LTexture
{
    private:
        //Contains texture data
        SDL_Texture* mTexture;
        //Texture dimensions
        int mWidth;
        int mHeight;
    public:
        //Initializes texture variables
        LTexture():
            mTexture{nullptr},
            mWidth{0},
            mHeight{0}
        {

        }
        //Cleans up texture variables
        ~LTexture()
        {
            destroy();
        }
        //Loads texture from disk
        bool loadFromFile( std::string path )
        {
            //Clean up texture if it already exists
            destroy();

            //Load surface
            if( SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); loadedSurface == nullptr )
            {
                SDL_Log( "Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError() );
            }
            else
            {
                //Create texture from surface
                if( mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface ); mTexture == nullptr )
                {
                    SDL_Log( "Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError() );
                }
                else
                {
                    //Get image dimensions
                    mWidth = loadedSurface->w;
                    mHeight = loadedSurface->h;
                }

                //Clean up loaded surface
                SDL_DestroySurface( loadedSurface );
            
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
            SDL_DestroyTexture( this->mTexture );
            this->mTexture = nullptr;
            this->mWidth = 0;
            this->mHeight = 0;
        }
        void setColor( Uint8 r, Uint8 g, Uint8 b )
        {
            SDL_SetTextureColorMod( mTexture, r, g, b );
        }

        //Draws texture
        void render( float x, float y, SDL_FRect* clip = nullptr)
        {
            //Set texture position
            SDL_FRect dstRect = { x, y, static_cast<float>( this->mWidth ), static_cast<float>( this->mHeight ) };

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

LTexture gPngTexture;
  
enum Types
{
    ofensive,
    defensive,
    other
};
class Item
{
    protected:
        string name;
        int price;
        Types type;
        string path;
    public:
        Item() = delete;
        Item(string name,int price,Types type,string path)
        {
            this->name = name;
            this->price = price;
            this->type = type;
            this->path = path;
        }
        string getName()
        {
            return this->name;
        }
        int getPrice()
        {
            return this->price;
        }
        Types getType()
        {
            return this->type;
        }
        string getPath()
        {
            return this->path;
        }
        void setName(string name)
        {
            this->name = name;
        }
        void setPrice(int price)
        {
            this->price = price;
        }
        void setType(Types type)
        {
            this->type = type;
        }
        void display()
        {
            cout << "Name: " << name << endl;
            cout << "Price: " << price << endl;
            cout << "Type: " << type << endl;
        }
};

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
                    LTexture slotTexture;
                    slotTexture.loadFromFile("assets/emptyItem.png");
                    slotTexture.setSize(55,55);
                    slotTexture.setColor(0,0,0);
                    slotTexture.render(tempXposition,tempYposition);
                }
                else
                {
                    LTexture itemTexture;
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
class Player
{
    private:
        string name;
        int gold;
        int health;
        Inventory* inventory;
    public:
        Player() = delete;
        Player(string name)
        {
            this->name = name;
            this->gold = 0;
            this->health = 5;
            this->inventory = new Inventory(2,4);
        }
        int getHealth()
        {
            return this->health;
        }
        void setHealth(int health)
        {
            this->health = health;
        }
        string getName()
        {
            return this->name;
        }
        void setName(string name)
        {
            this->name = name;
        }
        int getGold()
        {
            return this->gold;
        }
        void setGold(int gold)
        {
            this->gold = gold;
        }
        void display()
        {
            cout << "Name: " << name << " ";
        }
};


/* Function Implementations */
bool init()
{
    //Initialization flag
    bool success{ true };

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
            if( !IMG_LoadTexture)
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
    bool success{ true };

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
    int exitCode{ 0 };
    //Initialize
    if( !init() )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    }
    else
    {
        //The quit flag
        bool quit{ false };
        
        //The event data
        SDL_Event e;
        SDL_zero( e );

        //The main loop
        while( quit == false )
        {
            //Get event data
            while( SDL_PollEvent( &e ) )
            {
                //If event is quit type
                if( e.type == SDL_EVENT_QUIT )
                {
                    //End the main loop
                    quit = true;
                }
            }

            //Fill the background in color
            SDL_SetRenderDrawColor( gRenderer, 255, 200, 255, 255 );
            SDL_RenderClear( gRenderer );
    
            inventory.display();

            //Update screen
            SDL_RenderPresent( gRenderer );
        } 
    }

    //Clean up
    close();

    return exitCode;

}
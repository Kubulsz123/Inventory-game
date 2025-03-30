/* Headers */
//Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>
#include <string>

using namespace std;
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
    public:
        Item()
        {
            this->name = "coin";
            this->price = 1;
            this->type = other;
        }
        Item(string name,int price,Types type)
        {
            this->name = name;
            this->price = price;
            this->type = type;
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
    Inventory(int rows, int cols) : rows{rows}, cols{cols} {
        items = new Item**[rows];
        for (int i = 0; i < rows; i++) {
            items[i] = new Item*[cols];
        }
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[";
                if (items[i][j] == nullptr) {
                    cout << " ";
                }
                else {
                    cout << items[i][j]->getName()[0];
                }
                cout << "]";
            }
            cout << endl;
        }
    }


    bool addItem(Item* item) {
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

    bool removeItem(int row, int col) {
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

    int getInventoryValue() {
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

    void removeItems() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (items[i][j] != nullptr) {
                    delete items[i][j];
                    items[i][j] == nullptr;
                }
            }
        }
    }

    ~Inventory() {
        removeItems();

        for (int i = 0; i < rows; i++) {
            delete[] items[i];
        }

        delete[] items;
    }
};

/* Constants */
// Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/* Global Variables */
// The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

// The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

// The image we will load and show on the screen
SDL_Surface* gHelloWorld{ nullptr };

/* Function Prototypes */
// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

/* Function Implementations */

bool init()
{
    // Initialization flag
    bool success{ true };

    // Initialize SDL
    if( !SDL_Init( SDL_INIT_VIDEO ) )
    {
        SDL_Log( "SDL could not initialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // Create window
        if( gWindow = SDL_CreateWindow( "SDL3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0 ); gWindow == nullptr )
        {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

// Loads media
bool loadMedia()
{
    // File loading flag
    bool success{ true };

    // Load splash image
    std::string imagePath{ "assets/preview.bmp" };
    if( gHelloWorld = SDL_LoadBMP( imagePath.c_str() ); gHelloWorld == nullptr )
    {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success = false;
    }

    return success;
}

// Frees media and shuts down SDL
void close()
{
    // Clean up surface
    SDL_DestroySurface( gHelloWorld );
    gHelloWorld = nullptr;

    // Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    gScreenSurface = nullptr;

    // Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    // Final exit code
    int exitCode{ 0 };

    // Initialize
    if( !init() )
    {
        SDL_Log( "Unable to initialize program!\n" );
        exitCode = 1;
    }
    else
    {
        // Load media
        if( !loadMedia() )
        {
            SDL_Log( "Unable to load media!\n" );
            exitCode = 2;
        }
        // The quit flag
        bool quit{ false };

        // The event data
        SDL_Event e;
        SDL_zero( e );
        // The main loop
        while( quit == false )
        {
            // Get event data
            while( SDL_PollEvent( &e ) )
            {
                // If event is quit type
                if( e.type == SDL_EVENT_QUIT )
                {
                    // End the main loop
                    quit = true;
                }
            }
            // Fill the surface white
            SDL_FillSurfaceRect( gScreenSurface, nullptr, SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF ) );

            // Render image on screen
            SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr );

            // Update the surface
            SDL_UpdateWindowSurface( gWindow );
        } 
}

    // Clean up
    close();

    return exitCode;
}
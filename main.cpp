//The game ONslaught
//(c) Liam Girard 2014
//
//This program allows the user to play the game ONslaught

#include <SDL.h>
//#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Sprite
{
public:
    //Initializes variables
    Sprite();

    //Deallocates memory
    ~Sprite();

    //Loads image at specified path
    bool loadFromFile( std::string path );

    //Deallocates sprite
    void free();

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mSprite;

    //Image dimensions
    int mWidth;
    int mHeight;
};

class bullet
{
public:
    static const int WIDTH = 32;
    static const int HEIGHT = 32;

    //Initializes the variables
    bullet();
    ~bullet();

    //Moves the dot
    void move();

    //Checks input
    void check();

    //Shows the dot on the screen
    void render();

    bool inFlight = false;

    void setxy(int inputx, int inputy);

    int getX();
    int getY();

private:
    //Sprite for the bullet
    Sprite sprite;
    //The X and Y offsets of the dot
    int x, y;
};

bullet::bullet()
{
    //Load dot texture
    if( !sprite.loadFromFile( "bullet.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
    }
}

bullet::~bullet()
{
    sprite.free();
}

void bullet::render()
{
    sprite.render(x,y);
}

void bullet:: setxy(int inputx, int inputy)
{
    x = inputx;
    y = inputy;
}

void bullet::move()
{
    y = y - 3;
}

int bullet::getX()
{
    return x;
}

int bullet::getY()
{
    return y;
}

class Player
{
public:
    static const int WIDTH = 32;
    static const int HEIGHT = 32;

    //Initializes the variables
    Player();
    ~Player();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );

    //Moves the dot
    void move();

    //Checks input
    void check();

    //Get X
    int getX();

    //Get Y
    int getY();

    //Shows the dot on the screen
    void render();

private:
    //Sprite for the Player
    Sprite sprite;
    //The X and Y offsets of the dot
    int x, y;

    //The velocity of the dot
    int vx, vy;
};

Player::Player()
{
    //Initialize the offsets
    x = SCREEN_WIDTH/4;
    y = SCREEN_HEIGHT - sprite.getHeight()- 3;

    //Initialize the velocity
    vx = 0;
    vy = 0;

    //Load dot texture
    if( !sprite.loadFromFile( "player.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
    }
}

Player::~Player()
{
    sprite.free();
}

void Player::check()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_RIGHT])
    {
        vy = -5;
        vx = 5;
    }
    else if (state[SDL_SCANCODE_UP] && state[SDL_SCANCODE_LEFT])
    {
        vy = -5;
        vx = -5;
    }
    else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT])
    {
        vy = 5;
        vx = 5;
    }
    else if (state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT])
    {
        vy = 5;
        vx = -5;
    }
    else if (state[SDL_SCANCODE_UP])
    {
        vy = -5;
        vx = 0;
    }
    else if (state[SDL_SCANCODE_DOWN])
    {
        vy = 5;
        vx = 0;
    }
    else if (state[SDL_SCANCODE_RIGHT])
    {
        vx = 5;
        vy = 0;
    }
    else if (state[SDL_SCANCODE_LEFT])
    {
        vx = -5;
        vy = 0;
    }
    else
    {
        vy = 0;
        vx = 0;
    }
}

void Player::handleEvent( SDL_Event& e )
{
    /*
    //If a key was pressed
    if( e.type == SDL_KEYDOWN / *&& e.key.repeat == 0* / )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: vy = -10; vx = 0; break;
            case SDLK_DOWN: vy = 10; vx = 0; break;
            case SDLK_LEFT: vx = -10; vy = 0; break;
            case SDLK_RIGHT: vx = 10; vy = 0; break;
            case SDLK_LEFT and SDLK_UP: vx = -10; vy = 10; break;
            case SDLK_LEFT and SDLK_DOWN: vx = -10; vy = -10; break;
            case SDLK_RIGHT and SDLK_UP: vx = 10; vy = 10; break;
            case SDLK_RIGHT and SDLK_DOWN: vx = 10; vy = -10; break;
        }
    }*/
}

void Player::move()
{
    //Move the dot left or right
    x += vx;

    //If the dot went too far to the left or right
    if ( x < 0 )
    {
        vx = 0;
        x = 0;
    }
    else if( x + sprite.getWidth() > SCREEN_WIDTH )
    {
        vx = 0;
        x =  SCREEN_WIDTH - sprite.getWidth();
    }

    //Move the dot up or down
    y += vy;

    //If the dot went too far up or down
    if ( y < 0 )
    {
        vy = 0;
        y = 0;
    }
    else if( y + sprite.getHeight() > SCREEN_HEIGHT )
    {
        vy = 0;
        y =  SCREEN_HEIGHT - sprite.getHeight();
    }

}

void Player::render()
{
    sprite.render(x,y);
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


Sprite::Sprite()
{
    //Initialize
    mSprite = NULL;
    mWidth = 0;
    mHeight = 0;
}

Sprite::~Sprite()
{
    //Deallocate
    free();
}

bool Sprite::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mSprite = newTexture;
    return mSprite != NULL;
}

void Sprite::free()
{
    //Free texture if it exists
    if( mSprite != NULL )
    {
        SDL_DestroyTexture( mSprite );
        mSprite = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void Sprite::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mSprite, clip, &renderQuad, angle, center, flip );
}

int Sprite::getWidth()
{
    return mWidth;
}

int Sprite::getHeight()
{
    return mHeight;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "ONslaught", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }
    return success;
}

void close()
{
    //Free loaded images

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    int totalBullets = 0;

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        //The Player that will be moving around on the screen
        Player user;
        bullet MyBullet [20];

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                //Handle input for the Player
                //user.handleEvent( e );

                if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_SPACE:
                        if (totalBullets <= 19)
                        {
                            for (int f = 0; f <= totalBullets; f++)
                            {
                                if (!MyBullet[f].inFlight)
                                {
                                    MyBullet[f].inFlight = true;
                                    MyBullet[f].setxy(user.getX(),user.getY());
                                }
                                else if (f == totalBullets)
                                {
                                    MyBullet[f].inFlight = true;
                                    MyBullet[f].setxy(user.getX(),user.getY());
                                    totalBullets++;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            std::cout << "don't fire!";
                        }
                        break;
                    }
                }
            }

            user.check();

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            for (int f = 0; f < totalBullets - 1; f++)
            {
                if (MyBullet[f].getY() <= 0 /*or hits an enemy*/ )
                {
                    MyBullet[f].inFlight = false;
                    totalBullets--;
                }
                if (MyBullet[f].inFlight)
                {
                    MyBullet[f].move();
                    MyBullet[f].render();
                }
            }

            //Move the Player
            user.move();

            //Render objects
            user.render();

            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

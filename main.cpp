//The game ONslaught
//(c) Liam Girard 2014
//
//This program allows the user to play the game ONslaught

#include <SDL.h>
//#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <ctime>
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

void LoadBitmap(Sprite &s, const std::string& name) {
    if( !s.loadFromFile( name ) )
    {
        printf( "Failed to load dot texture!\n" );
    }
}


class Score
{
public:
    static const int WIDTH = 160;
    static const int HEIGHT = 480;

    //Initializes the variables
    Score();
    ~Score();

    //Shows the dot on the screen
    void render(int number);

    void setxy(int inputx, int inputy);

private:
    Sprite numbers[10];

    int x, y;
};

Score::Score()
{
    LoadBitmap(numbers[0],"0.bmp");
    LoadBitmap(numbers[1],"1.bmp");
    LoadBitmap(numbers[2],"2.bmp");
    LoadBitmap(numbers[3],"3.bmp");
    LoadBitmap(numbers[4],"4.bmp");
    LoadBitmap(numbers[5],"5.bmp");
    LoadBitmap(numbers[6],"6.bmp");
    LoadBitmap(numbers[7],"7.bmp");
    LoadBitmap(numbers[8],"8.bmp");
    LoadBitmap(numbers[9],"9.bmp");
}

Score::~Score()
{
    for (int i = 0; i < 10; i++)
    {
        numbers[i].free();
    }
}

void Score::setxy(int inputx,int inputy)
{
    x = inputx;
    y = inputy;
}

void Score::render(int number)
{
        numbers[number].render(x,y);
}

class ScoreBoard
{
public:
    int WIDTH = 160;
    int HEIGHT = 480;

    //Initializes the variables
    ScoreBoard();
    ~ScoreBoard();

    //Shows the dot on the screen
    void render();

private:
    //Sprite for the ScoreBoard
    Sprite sprite;

    //The X and Y offsets of the dot
    int x, y;
};

ScoreBoard::ScoreBoard()
{
    LoadBitmap(sprite,"Scoreboard.bmp");
    x=480;
    y=480;
}

ScoreBoard::~ScoreBoard()
{
    sprite.free();
}

void ScoreBoard::render()
{
        sprite.render(x,y);
}

class Enemy
{
public:
    static const int WIDTH = 22;
    static const int HEIGHT = 20;

    //Initializes the variables
    Enemy();
    ~Enemy();

    //Moves the dot
    void move();

    //Shows the dot on the screen
    void render();

    bool alive = true;

    void setxy(int inputx, int inputy);

    int getX();
    int getY();

private:
    //Sprite for the enemy
    Sprite sprite;
    //The X and Y offsets of the dot
    int x, y;
};

Enemy::Enemy()
{
    LoadBitmap(sprite,"enemy.bmp");
}

Enemy::~Enemy()
{
    sprite.free();
}

void Enemy:: setxy(int inputx, int inputy)
{
    x = inputx;
    y = inputy;
}

void Enemy::render()
{
    sprite.render(x,y);
}

void Enemy::move()
{
    y = y + 1;
}

int Enemy::getX()
{
    return x;
}

int Enemy::getY()
{
    return y;
}

class bullet
{
public:
    int WIDTH = 4;
    int HEIGHT = 17;

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
    bool enemy = false;

    void setxy(int inputx, int inputy);

    int getX();
    int getY();

private:
    //Sprite for the bullet
    Sprite sprite;
    //Sprite for the bullet
    Sprite sprite2;

    //The X and Y offsets of the dot
    int x, y;
};

bullet::bullet()
{
    LoadBitmap(sprite,"bullet.bmp");
    LoadBitmap(sprite2,"EnemyBullet.bmp");
}

bullet::~bullet()
{
    sprite.free();
}

void bullet::render()
{
    if (!enemy)
    {
        sprite.render(x,y);
    }
    else if (enemy)
    {
        sprite2.render(x,y);
    }
}

void bullet:: setxy(int inputx, int inputy)
{
    x = inputx;
    y = inputy;
}

void bullet::move()
{
    if (!enemy)
    {
        y = y - 3;
    }
    else if (enemy)
    {
        y = y + 6;
    }
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

    //Check if they can fire a bullet
    bool noBullet = false;

    //Shows the dot on the screen
    void render();

private:
    //Sprite for the Player
    Sprite sprite;
    //Sprite for the Player
    Sprite sprite2;

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
    LoadBitmap(sprite,"player.bmp");
    //Load dot texture
    LoadBitmap(sprite2,"playerNoBullet.bmp");
}

Player::~Player()
{
    sprite.free();
    sprite2.free();
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
    else if( x + sprite.getWidth() > SCREEN_WIDTH - SCREEN_WIDTH/4 )
    {
        vx = 0;
        x =  SCREEN_WIDTH - SCREEN_WIDTH/4  - sprite.getWidth();
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
    if (noBullet)
    {
        sprite2.render(x,y);
    }
    else
    {
        sprite.render(x,y);
    }
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

void gameOver()
{
    Sprite End;

    //Load end texture
    if( !End.loadFromFile( "gameOver.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
    }
}

int main( int argc, char* args[] )
{
    int totalBullets = 0;
    bool once = true;
    int score[3];
    int level = 1;
    int totalEnemies = 5;
    int coordinate, column;
    int layer = 0;
    int counter = 1;

    //For random bullet timing
    int random;
    srand(time(0));

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
        Enemy enemies [100];
        bullet EnemyBullet [20];
        Score points[5];
        ScoreBoard board;


        for (int x = 0; x < 3; x++)
        {
            score[x]=0;
        }

        //Spawn enemies
        for (int f = 0; f < totalEnemies; f++)
        {
            random = rand()%SCREEN_HEIGHT;
            column = column+1;
            coordinate = column*32;
            if (coordinate>=436)
            {
                layer = SCREEN_HEIGHT * counter;
                counter++;
                column = 0;
                coordinate = column*32;
            }
            enemies[f].setxy(coordinate,(-3*random)-layer);
        }

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
                        if (totalBullets < 7)
                        {
                            MyBullet[totalBullets].inFlight = true;
                            MyBullet[totalBullets].setxy(user.getX()+14,user.getY());
                            totalBullets++;
                        }
                        break;
                    }
                }
            }

            user.check();

            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            if (once and totalBullets == 7)
            {
                user.noBullet = true;
                once = false;
            }

            for (int f = 0; f < totalBullets; f++)
            {
                if (MyBullet[f].inFlight)
                {
                    //Move bullets
                    MyBullet[f].move();
                    //Render Bullets
                    MyBullet[f].render();
                    //Check if bullet goes off screen
                    if (MyBullet[f].getY() <= -32)
                    {
                        MyBullet[f].inFlight = false;
                        MyBullet[f].setxy(-50,-50);
                    }
                    //Check if bullet hits the enemy
                    for (int x = 0; x < 20; x++)
                    {
                        if (MyBullet[f].getX()>=enemies[x].getX() and MyBullet[f].getX()<=enemies[x].getX()+22 and MyBullet[f].getY()>=enemies[x].getY() and MyBullet[f].getY()<=enemies[x].getY()+20 and MyBullet[f].inFlight)
                        {
                            if (MyBullet[f].inFlight)
                            {
                                score[0] = score[0] + 5;
                                while (score[0] >= 10)
                                {
                                    score[1]++;
                                    score[0]= score[0]-10;
                                    while (score[1]>=10)
                                    {
                                        score[2]++;
                                        score[1] = score[1] - 10;
                                    }
                                }
                            }
                            MyBullet[f].inFlight = false;
                            enemies[x].alive = false;
                            enemies[x].setxy(-50,-50);
                        }
                    }
                }
            }

            for (int f = 0; f < totalBullets; f++)
            {
                if (MyBullet[f].inFlight)
                {
                    break;
                }
                else if (f == 6)
                {
                    totalBullets = 0;
                    user.noBullet = false;
                    once = true;
                }
            }


            //Move the Player
            user.move();

            //Render objects
            user.render();

            for (int f = 0; f < totalEnemies; f++)
            {
                if (enemies[f].alive)
                {
                    random = rand()%500;
                    if (random <= 10 and EnemyBullet[f].inFlight == false)
                    {
                        EnemyBullet[f].setxy(enemies[f].getX()+10,enemies[f].getY());
                        EnemyBullet[f].inFlight = true;
                        EnemyBullet[f].enemy = true;
                    }
                    if (EnemyBullet[f].getY() >= SCREEN_HEIGHT and EnemyBullet[f].inFlight)
                    {
                        EnemyBullet[f].inFlight = false;
                        EnemyBullet[f].setxy(-20,-20);
                    }

                    if (EnemyBullet[f].inFlight)
                    {
                        EnemyBullet[f].move();
                        EnemyBullet[f].render();

                        if (EnemyBullet[f].getX() >= user.getX() and EnemyBullet[f].getX() <= user.getX()+32 and EnemyBullet[f].getY() >= user.getY() and EnemyBullet[f].getY() <= user.getY()+32)
                        {
                            //Clear screen
                            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                            SDL_RenderClear( gRenderer );

                            gameOver();

                            for (int f = 0; f<3; f++)
                            {
                                points[f].setxy(SCREEN_WIDTH*3/4-60-f*50,SCREEN_HEIGHT*3/4+50);
                                points[f].render(score[f]);
                            }

                            quit = true;
                            break;
                        }
                    }

                    //Move the enemies
                    enemies[f].move();

                    //Render enemies
                    enemies[f].render();

                    if (enemies[f].getY() > SCREEN_HEIGHT+25)
                    {
                        enemies[f].setxy(enemies[f].getX(),-30);
                    }

                }
            }

            //Check if enemies are alive
            for (int f = 0; f < totalEnemies; f++)
            {
                //If they are leave this loop
                if (enemies[f].alive)
                {
                    break;
                }
                else if (f == totalEnemies - 1)
                {
                    //Increase the level
                    level++;
                    //Add more enemies
                    totalEnemies= totalEnemies + 5;

                    //Reset enemies
                    for (int f = 0; f < totalEnemies; f++)
                    {
                        random = rand()%SCREEN_HEIGHT;
                        column = column+1;
                        coordinate = column*32;
                        if (coordinate>=436)
                        {
                            layer = SCREEN_HEIGHT * counter;
                            counter++;
                            column = 0;
                        }
                        enemies[f].setxy(coordinate,(-3*random)-layer);
                        enemies[f].alive = true;
                        EnemyBullet[f].inFlight = false;
                    }
                }
            }

            board.render();

            for (int f = 0; f<3; f++)
            {
               // if (f == 3)
               // {
                //    points[f].setxy(SCREEN_WIDTH*3/4+50,SCREEN_HEIGHT);
                //    points[f].render(level);
                //}
               // else
               // {
                    points[f].setxy(SCREEN_WIDTH-60-f*50,50);
                    points[f].render(score[f]);
               // }
            }

            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

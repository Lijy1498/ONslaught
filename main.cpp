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
#include <windows.h>

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

void LoadBitmap(Sprite &s, const std::string& name)
{
    if( !s.loadFromFile( name ) )
    {
        printf( "Failed to load dot texture!\n" );
    }
}


class Score
{
public:
    static const int WIDTH = 40;
    static const int HEIGHT = 53;

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
    static const int WIDTH = 160;
    static const int HEIGHT = 480;

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
    y=0;
}

ScoreBoard::~ScoreBoard()
{
    sprite.free();
}

void ScoreBoard::render()
{
    sprite.render(x,y);
}

class PowerUp
{
public:
    static const int WIDTH = 32;
    static const int HEIGHT = 32;

    //Initializes the variables
    PowerUp();
    ~PowerUp();

    int i;

    bool exist = false;

    //Shows the dot on the screen
    void render();
    void setxy(int inputx, int inputy);

private:
    //Sprite for the PowerUp
    Sprite shield;
    Sprite speed;
    Sprite life;
    Sprite pulse;
    Sprite sideGun;

    int x, y;
};

PowerUp::PowerUp()
{
    LoadBitmap(shield,"PowerUpShield.bmp");
    LoadBitmap(speed,"PowerUpSpeed.bmp");
    LoadBitmap(life,"PowerUpLife.bmp");
    LoadBitmap(pulse,"PowerUpPulse.bmp");
    LoadBitmap(sideGun,"PowerUpSide.bmp");
}

PowerUp::~PowerUp()
{
    shield.free();
    speed.free();
    life.free();
    pulse.free();
    sideGun.free();
}

void PowerUp::setxy(int inputx, int inputy)
{
    x = inputx;
    y = inputy;
}

void PowerUp::render()
{
    switch(i)
    {
    case 1:
        shield.render(x,y);
        break;

    case 2:
        speed.render(x,y);
        break;

    case 3:
        life.render(x,y);
        break;

    case 4:
        pulse.render(x,y);
        break;

    case 5:
        sideGun.render(x,y);
        break;
    }
}

class Menus
{
public:
    static const int WIDTH = 160;
    static const int HEIGHT = 480;

    //Initializes the variables
    Menus();
    ~Menus();

    //Shows the dot on the screen
    void render(int menu);

private:
    //Sprite for the Menus
    Sprite gameOver;
    Sprite victory;
    Sprite menuStart;
    Sprite menuQuit;
};

Menus::Menus()
{
    LoadBitmap(gameOver,"gameOver.bmp");
    LoadBitmap(victory,"win.bmp");
    LoadBitmap(menuStart,"menuStart.bmp");
    LoadBitmap(menuQuit,"menuQuit.bmp");
}

Menus::~Menus()
{
    gameOver.free();
    victory.free();
    menuStart.free();
    menuQuit.free();
}

void Menus::render(int menu)
{
    if (menu == 0)
    {
        gameOver.render(0,0);
    }
    else if (menu == 1)
    {
        victory.render(0,0);
    }
    else if (menu == 2)
    {
        menuStart.render(0,0);
    }
    else if (menu == 3)
    {
        menuQuit.render(0,0);
    }
}

class Life
{
public:
    static const int WIDTH = 40;
    static const int HEIGHT = 45;

    //Initializes the variables
    Life();
    ~Life();

    //Shows the dot on the screen
    void render();

    void setxy(int inputx, int inputy);

private:
    //Sprite for the Life
    Sprite sprite;

    //The X and Y offsets of the dot
    int x, y;
};

Life::Life()
{
    LoadBitmap(sprite,"heart.bmp");
}

Life::~Life()
{
    sprite.free();
}

void Life::render()
{
    sprite.render(x,y);
}

void Life::setxy(int inputx,int inputy)
{
    x = inputx;
    y = inputy;
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

    void setxy(int inputx, int inputy);

    //Get X
    int getX();

    //Get Y
    int getY();

    //Check if shield is active
    bool shieldOn = false;

    //Check if they can fire a bullet
    bool Bullet = false;

    //Shows the dot on the screen
    void render();

private:
    //Sprite for the Player
    Sprite normal;
    //Sprite for the Player
    Sprite noBullet;
    //Sprite for the Player
    Sprite normalS;
    //Sprite for the Player
    Sprite noBulletS;

    //The X and Y offsets of the dot
    int x, y;

    //The velocity of the dot
    int vx, vy;
};

Player::Player()
{
    //Initialize the offsets
    x = SCREEN_WIDTH/4;
    y = SCREEN_HEIGHT - 35;

    //Initialize the velocity
    vx = 0;
    vy = 0;

    //Load dot texture
    LoadBitmap(normal,"player.bmp");
    //Load dot texture
    LoadBitmap(noBullet,"playerNoBullet.bmp");
    //Load dot texture
    LoadBitmap(normalS,"playerShield.bmp");
    //Load dot texture
    LoadBitmap(noBulletS,"playerShieldNoBullet.bmp");
}

Player::~Player()
{
    normal.free();
    noBullet.free();
    normalS.free();
    noBulletS.free();
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
    else if( x + normal.getWidth() > SCREEN_WIDTH - SCREEN_WIDTH/4 )
    {
        vx = 0;
        x =  SCREEN_WIDTH - SCREEN_WIDTH/4  - normal.getWidth();
    }

    //Move the dot up or down
    y += vy;

    //If the dot went too far up or down
    if ( y < 0 )
    {
        vy = 0;
        y = 0;
    }
    else if( y + normal.getHeight() > SCREEN_HEIGHT )
    {
        vy = 0;
        y =  SCREEN_HEIGHT - normal.getHeight();
    }

}

void Player::render()
{
    if (shieldOn)
    {
        if (Bullet)
        {
            noBulletS.render(x,y);
        }
        else
        {
            normalS.render(x,y);
        }
    }
    else
    {
        if (Bullet)
        {
            noBullet.render(x,y);
        }
        else
        {
            normal.render(x,y);
        }
    }
}

void Player::setxy(int inputx, int inputy)
{
    x = inputx;
    y = inputy;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

/*//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
*/
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
    bool once = true;
    int score[3];
    int level[2];
    int totalEnemies = 5;
    int coordinate, column;
    int layer = 0;
    int counter = 1;
    int lives = 3;
    int menu = 2;
    bool openMenu = true;
    bool restarted = false;
    int powerX, powerY;
    bool shield = false;

    level [0]=1;
    level [1]=0;

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
        Enemy enemies [95];
        bullet EnemyBullet [95];
        Score points[5];
        ScoreBoard board;
        Life hearts[3];
        Menus endGame;
        PowerUp powers;

        while (openMenu)
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_DOWN:
                        if (menu == 3)
                        {
                            menu = 2;
                        }
                        else
                        {
                            menu = 3;
                        }
                        break;

                    case SDLK_UP:
                        if (menu == 3)
                        {
                            menu = 2;
                        }
                        else
                        {
                            menu = 3;
                        }
                        break;

                    case SDLK_SPACE:
                        if (menu == 3)
                        {
                            quit = true;
                        }
                        openMenu = false;
                        break;
                    }
                }
            }
            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );

            endGame.render(menu);


            //Update screen
            SDL_RenderPresent( gRenderer );
        }

        openMenu = true;


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
        counter = 0;
        column = 0;


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


            if (powers.exist)
            {
                powers.render();
            }

            if (once and totalBullets == 7)
            {
                user.Bullet = true;
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
                    for (int x = 0; x < totalEnemies; x++)
                    {
                        if (MyBullet[f].getX()>=enemies[x].getX() and MyBullet[f].getX()<=enemies[x].getX()+22 and MyBullet[f].getY()>=enemies[x].getY() and MyBullet[f].getY()<=enemies[x].getY()+20 and MyBullet[f].inFlight)
                        {
                            if (MyBullet[f].inFlight)
                            {
                                score[0] = score[0] + 1;
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

                            random = 1;
                            if (random <= 5 and powers.exist == false)
                            {
                                powers.i = random;
                                powerX=enemies[x].getX();
                                powerY=enemies[x].getY();
                                powers.setxy(powerX,powerY);
                                powers.exist = true;
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
                    user.Bullet = false;
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
                            if (shield)
                            {
                                shield = false;
                                user.shieldOn = false;
                                EnemyBullet[f].setxy(10000,10000);
                            }
                            else
                            {
                                lives= lives - 1;
                                EnemyBullet[f].setxy(10000,10000);

                                if (lives == 0)
                                {
                                    //Clear screen
                                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                    SDL_RenderClear( gRenderer );

                                    endGame.render(0);

                                    for (int f = 0; f<3; f++)
                                    {
                                        points[f].setxy(515-f*50,325);
                                        points[f].render(score[f]);
                                    }
                                    //Update screen
                                    SDL_RenderPresent( gRenderer );
                                    while (openMenu)
                                    {
                                        //Handle events on queue
                                        while( SDL_PollEvent( &e ) != 0 )
                                        {
                                            if( e.type == SDL_KEYDOWN )
                                            {
                                                switch( e.key.keysym.sym )
                                                {
                                                case SDLK_ESCAPE:
                                                    quit = true;
                                                    openMenu = false;
                                                    break;

                                                case SDLK_SPACE:
                                                    totalBullets = 0;
                                                    once = true;
                                                    totalEnemies = 5;
                                                    layer = 0;
                                                    counter = 1;
                                                    lives = 3;
                                                    menu = 2;
                                                    level [0]=0;
                                                    level [1]=0;
                                                    restarted = true;
                                                    user.setxy(SCREEN_WIDTH/4,SCREEN_HEIGHT - 35);
                                                    user.Bullet = false;
                                                    for (int g = 0; g < 7; g++)
                                                    {
                                                        MyBullet[g].inFlight = false;
                                                        MyBullet[g].setxy(-20,-70);
                                                    }
                                                    for (int g = 0; g < totalEnemies; g++)
                                                    {
                                                        enemies[g].alive = false;
                                                        enemies[g].setxy(-20,-20);
                                                    }
                                                    for (int x = 0; x < 3; x++)
                                                    {
                                                        score[x]=0;
                                                    }

                                                    openMenu = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    openMenu = true;
                                }
                            }
                        }
                    }

                    //Move the enemies
                    enemies[f].move();

                    //Render enemies
                    enemies[f].render();

                    if (enemies[f].getX() >= user.getX() and enemies[f].getX() <= user.getX()+32 and enemies[f].getY() >= user.getY() and enemies[f].getY() <= user.getY()+32 and enemies[f].getX()+22 >= user.getX() and enemies[f].getX()+22 <= user.getX()+32 and enemies[f].getY()+20 >= user.getY() and enemies[f].getY()+20 <= user.getY()+32)
                    {
                        if (shield)
                        {
                            shield = false;
                            user.shieldOn = false;
                            enemies[f].alive = false;
                            enemies[f].setxy(-50,-50);
                            score[0] = score[0] + 1;
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
                        else
                        {
                            lives = lives - 1;
                            enemies[f].alive = false;
                            enemies[f].setxy(-50,-50);
                            score[0] = score[0] + 1;
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
                            if (lives == 0)
                            {
                                //Clear screen
                                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                                SDL_RenderClear( gRenderer );

                                endGame.render(0);

                                for (int f = 0; f<3; f++)
                                {
                                    points[f].setxy(515-f*50,325);
                                    points[f].render(score[f]);
                                }
                                //Update screen
                                SDL_RenderPresent( gRenderer );
                                while (openMenu)
                                {
                                    //Handle events on queue
                                    while( SDL_PollEvent( &e ) != 0 )
                                    {
                                        if( e.type == SDL_KEYDOWN )
                                        {
                                            switch( e.key.keysym.sym )
                                            {
                                            case SDLK_ESCAPE:
                                                quit = true;
                                                openMenu = false;
                                                break;

                                            case SDLK_SPACE:
                                                totalBullets = 0;
                                                once = true;
                                                totalEnemies = 5;
                                                layer = 0;
                                                counter = 1;
                                                lives = 3;
                                                menu = 2;
                                                level [0]=0;
                                                level [1]=0;
                                                restarted = true;
                                                user.setxy(SCREEN_WIDTH/4,SCREEN_HEIGHT - 35);
                                                user.Bullet = false;
                                                for (int g = 0; g < 7; g++)
                                                {
                                                    MyBullet[g].inFlight = false;
                                                    MyBullet[g].setxy(-20,-70);
                                                }
                                                for (int g = 0; g < totalEnemies; g++)
                                                {
                                                    enemies[g].alive = false;
                                                    enemies[g].setxy(-20,-20);
                                                }
                                                for (int x = 0; x < 3; x++)
                                                {
                                                    score[x]=0;
                                                }

                                                openMenu = false;
                                                break;
                                            }
                                        }
                                    }
                                }
                                openMenu = true;
                            }
                        }
                    }
                    if (enemies[f].getY() > SCREEN_HEIGHT+25)
                    {
                        enemies[f].setxy(enemies[f].getX(),-30);
                    }
                }
            }

            if (powerX >= user.getX() and powerX <= user.getX()+32 and powerY >= user.getY() and powerY <= user.getY()+32)
            {
                switch (powers.i)
                {
                case 1:
                    shield = true;
                    user.shieldOn = true;
                    break;

                case 2:
                    // user.speed = true;
                    break;

                case 3:
                    if (lives != 3)
                    {
                        lives++;
                    }
                    break;

                case 4:
                    // bullet.pulse = true;
                    break;

                case 5:
                    // bullet.sideGun = true;
                    break;
                }
                powers.exist = false;
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
                    level[0] = level[0] + 1;
                    while (level[0] >= 10)
                    {
                        level[1]++;
                        level[0]= level[0]-10;
                    }
                    if (level[1] == 2)
                    {
                        //Clear screen
                        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                        SDL_RenderClear( gRenderer );

                        endGame.render(1);

                        //Update screen
                        SDL_RenderPresent( gRenderer );

                        Sleep(10000);
                        quit = true;
                        break;
                    }
                    if (!restarted)
                    {
                        //Add more enemies
                        totalEnemies= totalEnemies + 5;
                    }
                    else
                    {
                        restarted = false;
                    }

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

            for (int f = 0; f < lives; f++)
            {
                hearts[f].setxy(SCREEN_WIDTH-50-f*50,187);
                hearts[f].render();
            }

            for (int f = 0; f<5; f++)
            {
                if (f >= 3)
                {
                    points[f].setxy(575-(50*(f-3)),299);
                    points[f].render(level[f-3]);
                }
                else
                {
                    points[f].setxy(SCREEN_WIDTH-50-f*50,50);
                    points[f].render(score[f]);
                }
            }

            for (int f = 7; f > totalBullets; f--)
            {
                MyBullet[f+7].setxy(SCREEN_WIDTH-(20*(f)),439);
                MyBullet[f+7].render();
            }

            //Update screen
            SDL_RenderPresent( gRenderer );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}

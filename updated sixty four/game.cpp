#include "game.hpp"
#include <cassert>
#include <iostream>


int Game::lastTime = 0;
// constructors
Game::Game(SDL_Renderer* renderer, SDL_Window* window)
{
    this->renderer = renderer;
    this->window = window;
    setRunning(true);
    setFullscreen(0);
    userInput = 0;
    active1 = 0;
    active2 = 0;
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    //setSurface(TTF_RenderText_Blended(font, "Hello", (SDL_Color){0, 0, 0, 255}));
    //fontText = SDL_CreateTextureFromSurface(renderer, image);

    initFont();

    tackle.setName("Tackle");
    tackle.setDamage(100);
    tackle.setType("Normal");

    razorLeaf.setName("Razor Leaf");
    razorLeaf.setDamage(55);
    razorLeaf.setType("Grass");

    magicalLeaf.setName("Magical Leaf");
    magicalLeaf.setDamage(60);
    magicalLeaf.setType("Grass");
    
    bodySlam.setName("Body Slam");
    bodySlam.setDamage(85);
    bodySlam.setType("Normal");

    ember.setName("Ember");
    ember.setDamage(40);
    ember.setType("Fire");

    quickAttack.setName("Quick Attack");
    quickAttack.setDamage(40);
    quickAttack.setType("Normal");

    flameWheel.setName("Flame Wheel");
    flameWheel.setDamage(60);
    flameWheel.setType("Fire");

    scratch.setName("Scratch");
    scratch.setDamage(40);
    scratch.setType("Normal");

    waterGun.setName("Water Gun");
    waterGun.setDamage(40);
    waterGun.setType("Water");

    aquaTail.setName("Aqua Tail");
    aquaTail.setDamage(90);
    aquaTail.setType("Water");

    slash.setName("Slash");
    slash.setDamage(70);
    slash.setType("Normal");

    vineWhip.setName("Vine Whip");
    vineWhip.setDamage(45);
    vineWhip.setType("Grass");

    waterPulse.setName("Water Pulse");
    waterPulse.setDamage(60);
    waterPulse.setType("Water");

    fireFang.setName("Fire Fang");
    fireFang.setDamage(65);
    fireFang.setType("Fire");

    flameThrower.setName("Flame Thrower");
    flameThrower.setDamage(90);
    flameThrower.setType("Fire");

    chikoritaMoves[0] = tackle;
    chikoritaMoves[1] = razorLeaf;
    chikoritaMoves[2] = magicalLeaf;
    chikoritaMoves[3] = bodySlam;

    totodileMoves[0] = scratch;
    totodileMoves[1] = waterGun;
    totodileMoves[2] = slash;
    totodileMoves[3] = aquaTail;

    cyndaquilMoves[0] = tackle;
    cyndaquilMoves[1] = ember;
    cyndaquilMoves[2] = quickAttack;
    cyndaquilMoves[3] = flameWheel;

    bulbasaurMoves[0] = tackle;
    bulbasaurMoves[1] = vineWhip;
    bulbasaurMoves[2] = razorLeaf;
    bulbasaurMoves[3] = magicalLeaf;

    squirtleMoves[0] = tackle;
    squirtleMoves[1] = waterGun;
    squirtleMoves[2] = waterPulse;
    squirtleMoves[3] = aquaTail;

    charmanderMoves[0] = scratch;
    charmanderMoves[1] = ember;
    charmanderMoves[2] = fireFang;
    charmanderMoves[3] = flameThrower;

    team1[0].setHP(294);
    team1[0].setMove(chikoritaMoves);
    team1[0].setName("Chikorita");
    team1[0].setPokeType("Grass");
    team1[0].setResistance("Water");

    team1[1].setHP(304);
    team1[1].setMove(totodileMoves);
    team1[1].setName("Totodile");
    team1[1].setPokeType("Water");
    team1[1].setResistance("Fire");

    team1[2].setHP(282);
    team1[2].setMove(cyndaquilMoves);
    team1[2].setName("Cyndaquil");
    team1[2].setPokeType("Fire");
    team1[2].setResistance("Grass");

    team2[0].setHP(294);
    team2[0].setMove(bulbasaurMoves);
    team2[0].setName("Bulbasaur");
    team2[0].setPokeType("Grass");
    team2[0].setResistance("Water");
    
    team2[1].setHP(292);
    team2[1].setMove(squirtleMoves);
    team2[1].setName("Squirtle");
    team2[1].setPokeType("Water");
    team2[1].setResistance("Fire");

    team2[2].setHP(282);
    team2[2].setMove(charmanderMoves);
    team2[2].setName("Charmander");
    team2[2].setPokeType("Fire");
    team2[2].setResistance("Grass");
    
    



    // Pokemon chikorita("Name", "Grass", )

    setSurface(IMG_Load("res/pokemonBattleBacground.png"));
    bgTexture = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/chikorita-back.png"));
    playerOne[0]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/totodile-back.png"));
    playerOne[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/cyndaquil-back.png"));
    playerOne[2]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/bulbasaur.png"));
    playerTwo[0] = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/squirtle.png"));
    playerTwo[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/charmander.png"));
    playerTwo[2]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/pointer_arrow.png"));
    arrowText = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/trans_menu.png"));
    menuText = SDL_CreateTextureFromSurface(renderer, image);

    
}


// getters
bool Game::getRunning()const
{
    return running;
}
bool Game::getFullscreen()const
{
    return fullscreen;
}
int Game::getFrameCount()const
{
    return frameCount;
}
int Game::getTimerFPS()const
{
    return timerFPS;
}
int Game::getLastFrame()const
{
    return lastFrame;
}
int Game::getFps()const
{
    return fps;
}
static int getLastTime() 
{
    return Game::lastTime;
}
SDL_Surface* Game::getSurface()const
{
    return image;
}
// SDL_Texture* Game::getP1Text(int loc)const    // Index for array
// {
//     return playerOne[loc];
// }
// SDL_Texture* Game::getP2Text(int loc)const    // Index for array
// {
//     return playerTwo[loc];
// }
// SDL_Texture* Game::getBGTexture()const
// {
//     return bgTexture;
// }

// setters

void Game::setRunning(bool running)
{
    this->running = running;
}
void Game::setFullscreen(bool fullscreen)
{
    this->fullscreen = fullscreen;
}
void Game::setFrameCount(int frameCount)
{
    this->frameCount = frameCount;
}
void Game::setTimerFPS(int timerFPS)
{
    this->timerFPS = timerFPS;
}
void Game::setLastFrame(int lastFrame)
{
    this->lastFrame = lastFrame;
}
void Game::setFps(int fps)
{
    this->fps = fps;
}
void Game::setSurface(SDL_Surface* image)
{
    this->image = image;

}
void Game::setP1Text(SDL_Texture* texture, int loc) // Index
{
    this->playerOne[loc] = texture;
}
void Game::setP2Text(SDL_Texture* texture, int loc)
{
    this->playerTwo[loc] = texture;
}
void Game::setBGTexture(SDL_Texture* texture)
{
    this->bgTexture = texture;
}


void Game::setLastTime(int lastTime)
{
    Game::lastTime = lastTime;
}

// member methods


void Game::update()
{
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);
    if(userInput == USER_UP) 
    {
        std::cout << "UP\n";
        
        userInput = 0;
    } 
    if(userInput == USER_DN) 
    {
        std::cout << "DOWN\n";
        userInput = 0;
    }
    if(userInput == USER_LT) 
    {
        std::cout << "LEFT\n";
        userInput = 0;
    }
    if(userInput == USER_RT) 
    {
        std::cout << "RIGHT\n";
        userInput = 0;
    }
    if(userInput == USER_EN) 
    {
        std::cout << "ENTER\n";
        userInput = 0;
    }

}
void Game::input()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT) setRunning(false);
    }
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    if(keystates[SDL_SCANCODE_ESCAPE]) running = false;
    if(keystates[SDL_SCANCODE_F11]) fullscreen = !fullscreen;
    if(keystates[SDL_SCANCODE_UP]) userInput |= USER_UP;
    if(keystates[SDL_SCANCODE_DOWN]) userInput |= USER_DN;
    if(keystates[SDL_SCANCODE_LEFT]) userInput |= USER_LT;
    if(keystates[SDL_SCANCODE_RIGHT]) userInput |= USER_RT;
    if(keystates[SDL_SCANCODE_RETURN]) userInput |= USER_EN;
    SDL_ResetKeyboard();
}
void Game::draw()
{
    SDL_Rect spriteRect1; // sprite rectangle for player 1's pokemon
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL); // background render
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // colors something

    spriteRect1.x = 0; // start at x = 0
    spriteRect1.y = 0; // start at y = 0
    spriteRect1.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
    spriteRect1.h = SPRITE_SIZE;  // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
    SDL_Rect dstrect = {(350- SPRITE_SIZE) , (500 - SPRITE_SIZE) , spriteRect1.w * 2, spriteRect1.h * 2}; // destination rectangle to position and size sprite rectangle


    SDL_RenderCopy(renderer, playerOne[active1], &spriteRect1, &dstrect); // player 1 pokemon render
    
    SDL_Rect spriteRect2; // sprite rectangle for player 2's pokemon
    
    spriteRect2.x = 0; // start at x = 0
    spriteRect2.y = 0; // start at y = 0
    spriteRect2.w = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels outward from (0, 0)
    spriteRect2.h = SPRITE_SIZE; // capture SPRITE_SIZE amount of pixels downward from (SPRITESIZE, 0)
    
    dstrect = {(800- SPRITE_SIZE) , (475 - SPRITE_SIZE) / 2, spriteRect2.w * 3, spriteRect2.h * 3}; // destination rectangle to position and size sprite rectangle

    
    
    SDL_RenderCopy(renderer, playerTwo[active2], &spriteRect2, &dstrect); // player 2 pokemon render


    // menu
    SDL_Rect menu = {0, 0, 313 + 990, 93 + 110};
    dstrect = {0, 517, menu.w, menu.h};
    SDL_RenderCopy(renderer, menuText, &menu, &dstrect);

    // text
    dstrect = {0, 0, textArr[0].w, textArr[0].h};
    SDL_RenderCopy(renderer, textArr[0].textTex, NULL, &dstrect);

    // arrow sprite
    SDL_Rect arrow = {0, 0, 750, 750};
    dstrect = {580, 555, arrow.w/12, arrow.h/9};
    SDL_RenderCopy(renderer, arrowText, &arrow, &dstrect);




    SDL_RenderPresent(renderer);

}

void Game::displayFPS()
{
    lastFrame = SDL_GetTicks();
    if(lastFrame >= (Game::lastTime + 1000))
    {
        Game::lastTime = lastFrame;
        fps = frameCount;
        frameCount = 0;
    }
    std::cout << fps << std::endl;
}
void Game::countFPS()
{
    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS <(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }
}
void Game::kill()
{
    SDL_DestroyTexture(bgTexture);
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(playerOne[i]);
    }
    for(int i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(playerTwo[i]);
    }

    for (int i = 0; i < 34; i++) {
        SDL_DestroyTexture(textArr[i].textTex);
    }
    // for(int i = 0; i < 3; i++)
    // {

    // }
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::initFont() {
    font = TTF_OpenFont("fonts/FreeSerif.ttf", 40);
    if(font == NULL) std::cout << "Error Loading Font" << TTF_GetError() << std::endl;
    
    for (int i = 0; i < 34; i++) {
        image = TTF_RenderText_Blended(font, strArr[i], (SDL_Color){0, 0, 0, 255});

        textArr[i].textTex = SDL_CreateTextureFromSurface(renderer, image);

        if (TTF_SizeText(font, strArr[i], &textArr[i].w, &textArr[i].h) != 0) {
            std::cout << "Size Fail\n";
        }  
    }
}
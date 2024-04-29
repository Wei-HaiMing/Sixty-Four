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

    setSurface(IMG_Load("res/pokemonBattleBacground.png"));
    bgTexture = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/jynx-back.png"));
    playerOne[0]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/nidorino-back.png"));
    playerOne[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/hitmonchan-back.png"));
    playerOne[2]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/abra.png"));
    playerTwo[0] = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/charmeleon.png"));
    playerTwo[1]=SDL_CreateTextureFromSurface(renderer,image);

    setSurface(IMG_Load("res/dragonair.png"));
    playerTwo[2]=SDL_CreateTextureFromSurface(renderer,image);

    



    
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

    dstrect = {0, 0, textArr[0].w, textArr[0].h};
    SDL_RenderCopy(renderer, textArr[0].textTex, NULL, &dstrect);

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
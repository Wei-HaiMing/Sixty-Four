#include "game.hpp"
#include <cassert>
#include <iostream>


int Game::lastTime = 0;
// constructors
Game::Game()
{
    
    setRunning(true);
    setFullscreen(0);
    userInput = 0;

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std:: cout << "Failed at SDL_Init()" << std:: endl;
    if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) std::cout << "Failed to initialize SDL_image for PNG files: " << IMG_GetError() << std::endl; 
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    setSurface(IMG_Load("res/pokemonBattleBacground.png"));
    texture[0] = SDL_CreateTextureFromSurface(renderer, image);

    setSurface(IMG_Load("res/abra.png"));
    texture[1] = SDL_CreateTextureFromSurface(renderer, image);


    
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
SDL_Texture* Game::getTexture(int loc)const    // Index for array
{
    return texture[loc];
}


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
void Game::setTexture(SDL_Texture* texture, int loc) // Index
{
    this->texture[loc] = texture;
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
    SDL_Rect spriteRect;
    
    spriteRect.x = 0;
    spriteRect.y = 0;
    spriteRect.w = SPRITE_SIZE;
    spriteRect.h = SPRITE_SIZE;
    SDL_Rect dstrect = {(800- SPRITE_SIZE) , (475 - SPRITE_SIZE) / 2, spriteRect.w * 3, spriteRect.h * 3};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    
    SDL_RenderCopy(renderer, texture[0], NULL, NULL);
    SDL_RenderCopy(renderer, texture[1], &spriteRect, &dstrect);
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
    SDL_DestroyTexture(texture[0]);
    SDL_DestroyTexture(texture[1]);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
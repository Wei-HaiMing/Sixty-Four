#include "game.hpp"
#include <cassert>
#include <iostream>


int Game::lastTime = 0;
// constructors
Game::Game()
{
    setRunning(true);
    setFullscreen(0);
    // setLastTime(0);

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std:: cout << "Failed at SDL_Init()" << std:: endl;
    if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) std::cout << "Failed to initialize SDL_image for PNG files: " << IMG_GetError() << std::endl; 
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    SDL_SetWindowTitle(window, "SDL2 Window");
    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    setSurface(IMG_Load("res/pokemonBattleBacground.png"));
    // setSprite(IMG_Load("aaron.png"));
    // setSurface2(IMG_Load("res/tux.png"));
    setTexture(SDL_CreateTextureFromSurface(renderer, image));
    // SDL_CreateTextureFromSurface(renderer, image);
    // setTexture2(SDL_CreateTextureFromSurface(renderer, image2));
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
SDL_Texture* Game::getTexture()const
{
    return texture;
}
SDL_Surface* Game::getSprite()const
{
    return sprite;
}

// setters
// void Game::setSurface2(SDL_Surface *image2)
// {
//     this->image2 = image2;
// }
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
void Game::setTexture(SDL_Texture* texture)
{
    this->texture = texture;
}
void Game::setSprite(SDL_Surface* sprite)
{
    this->sprite = SDL_ConvertSurface(sprite, NULL, 0);
}
// void Game::setTexture2(SDL_Texture* texture2)
// {
//     this->texture2 = texture2;
// }
void Game::setLastTime(int lastTime)
{
    Game::lastTime = lastTime;
}

// member methods
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

void Game::update()
{
    if(fullscreen) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    if(!fullscreen) SDL_SetWindowFullscreen(window, 0);

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
    

}
void Game::draw()
{
    SDL_Rect rect;

    rect.x=rect.y=0;
    rect.w=WIDTH;
    rect.h=HEIGHT;
    SDL_RenderFillRect(renderer, &rect);
    
    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS <(1000/60))
    {
        SDL_Delay((1000/60)-timerFPS);
    }

    // SDL_RenderPresent(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
void Game::kill()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
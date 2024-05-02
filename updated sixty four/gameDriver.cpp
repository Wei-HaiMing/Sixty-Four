/*
Authors: Armando, Athena, Eduardo, Gabe
*/
#include <SDL2/SDL.h>
#include "game.hpp"
#include <iostream>
#define main SDL_main
SDL_Renderer* renderer; // a struct that handles all rendering, settings to render, can only render things to the tied window
SDL_Window* window; // a window 



int main(int argv, char** args)
{

    const int FPS= 60;
    const int FrameDelay= 1000/FPS;
    Uint32 frameStart;
    int frameTime;


    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std:: cout << "Failed at SDL_Init()" << std:: endl;

    if(!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) std::cout << "Failed to initialize SDL_image for PNG files: " << IMG_GetError() << std::endl; 
    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    TTF_Init();
    
    Game pokemon(renderer, window);

    
    // Mouse mouse;
    while(pokemon.getRunning())
    {
        // pokemon.countFPS();
        // pokemon.displayFPS();
        // mouse.mouseUpdate();
        // mouse.mouseDraw();
        frameStart = SDL_GetTicks();

        pokemon.update();
        pokemon.input();
        pokemon.draw();
        frameTime= SDL_GetTicks() - frameStart;
        if(FrameDelay > frameTime)
        {
            SDL_Delay(FrameDelay - frameTime);
        }
    }
    pokemon.kill();
}
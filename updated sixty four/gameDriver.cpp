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
        pokemon.update();
        pokemon.input();
        pokemon.draw();

    }
    pokemon.kill();
}
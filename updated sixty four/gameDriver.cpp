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
    //if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    TTF_Init();
    
    Game pokemon(renderer, window);

    
    // Mouse mouse;
    float delta, acc, lastFrame, currFrame;
    acc = 0;
    lastFrame = SDL_GetTicks();
    Uint64 start, end;
    while(pokemon.getRunning())
    {
         //pokemon.countFPS();
        //pokemon.displayFPS();
        // mouse.mouseUpdate();
        // mouse.mouseDraw();

        start = SDL_GetPerformanceCounter();
        currFrame = SDL_GetTicks();
        delta = currFrame - lastFrame;
        lastFrame = currFrame;
        acc += delta;

        frameStart = SDL_GetTicks();

        

        pokemon.input();

        //while (acc > 1000.0/60.0) {
        pokemon.update();
          //  acc -= 1000.0/60.0;
        //}
        pokemon.draw();

        Uint64 end = SDL_GetPerformanceCounter();
        float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();

        // cout << "Current FPS: " << to_string(1.0f / elapsed) << endl;

    }
    pokemon.kill();
    
    return 0;
}
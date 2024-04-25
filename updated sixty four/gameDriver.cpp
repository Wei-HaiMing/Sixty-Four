/*
Authors: Armando, Athena, Eduardo, Gabe
*/
#include <SDL2/SDL.h>
#include "game.hpp"
#include <iostream>
#define main SDL_main


int main(int argv, char** args)
{
    Game pokemon;
    
    while(pokemon.getRunning())
    {
        // pokemon.countFPS();
        // pokemon.displayFPS();
        pokemon.update();
        pokemon.input();
        pokemon.draw();
    }
    pokemon.kill();
}
#include <SDL2/SDL.h>
#include "game.hpp"
#include <iostream>
#define main SDL_main
#define SPRITE_SIZE 32


int main(int argv, char** args)
{
    Game pokemon;

    while(pokemon.getRunning())
    {
        pokemon.displayFPS();
        pokemon.update();
        pokemon.input();
        pokemon.draw();
    }
    pokemon.kill();

}
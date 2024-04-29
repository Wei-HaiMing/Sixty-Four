#ifndef POKEMON_HPP
#define POKEMON_HPP
#include <string>
#include "PokemonMove.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>



class Pokemon{
    public:
        Pokemon();
        Pokemon(std::string name, std::string poketype, Move movearr[],
                    SDL_Surface* surface, double resist, int health);
        void setName(std::string name);
        void setPokeType(std::string poketype);
        void setMove(Move movearr[]);
        void setSurf(SDL_Surface* SDL_surface);
        void setResistance(double resistance);
        void setHP(int health);

        std::string getName();
        std::string getPokeType();
        Move getMove();
        SDL_Surface* getSurf();
        double getResistance();
        int getHP();

        void pokeprint()const;
        ~Pokemon();
    private:
        std::string name, poketype;
        SDL_Surface* pokeSurf;
        Move movearr[4];
        int health;
        double resistance;

};

#endif
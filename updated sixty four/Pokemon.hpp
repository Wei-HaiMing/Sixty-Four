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
                    std::string resist, int health, bool dead, bool isActive);
        void setName(std::string name);
        void setPokeType(std::string poketype);
        void setMove(Move movearr[]);
        // void setSurf(SDL_Surface* SDL_surface);
        void setResistance(std::string resistance);
        void setHP(int health);
        void setDead(bool dead);
        void setIsActive(bool isActive);

        bool getIsActive();
        std::string getName();
        std::string getPokeType();
        Move getMove(int loc);
        // SDL_Surface* getSurf();
        std::string getResistance();
        int getHP();
        bool getDead();
        void pokeprint()const;
        ~Pokemon();
    private:
        std::string name, poketype;

        // SDL_Surface* pokeSurf;
        Move movearr[4];
        int health;
        std::string resistance;
        bool dead, isActive;

};

#endif
#include <iostream>
#include "Pokemon.hpp"
using namespace std;

Pokemon::Pokemon(){
    name = "";
    poketype = "";
    movearr[3];
    movearr[0] = Move("placeholder", "placeholder", 0); 
    movearr[1] = Move("placeholder", "placeholder", 0); 
    movearr[2] = Move("placeholder", "placeholder", 0); 
    movearr[3] = Move("placeholder", "placeholder", 0); 
    // Move array initialized to empty move objects.
    // SDL_surface = "";
    resistance = 0.0;
    health = 0;
}

Pokemon::Pokemon(string name, string poketype, Move movearr[], SDL_Surface* surface, double resist, int health){
    Pokemon::setName(name);
    Pokemon::setPokeType(poketype);
    Pokemon::setMove(movearr);
    Pokemon::setSurf(surface);
    Pokemon::setResistance(resist);
    Pokemon::setHP(health);
}

Pokemon::~Pokemon()
{
    SDL_FreeSurface(pokeSurf);
    std::cout << "Pokemon Deconstructor Ran\n";
}

void Pokemon::setName(string name){
    this -> name = name;
}

void Pokemon::setPokeType(string poketype){
    this -> poketype = poketype;
}

void Pokemon::setMove(Move movearr[]){
    for(int i = 0; i < 4; i++){
        this -> movearr[i] = movearr[i];
    }
}

void Pokemon::setSurf(SDL_Surface* surface){
    this -> pokeSurf = surface;
}

void Pokemon::setResistance(double resist){
    this -> resistance = resist;
}

void Pokemon::setHP(int health){
    this -> health = health;
}

string Pokemon::getName(){
    return name;
}

string Pokemon::getPokeType(){
    return poketype;
}

Move Pokemon::getMove(){
    for(int i = 0; i < 4; i++){
        return movearr[i];
    }
}

SDL_Surface* Pokemon::getSurf(){
    return pokeSurf;
}

double Pokemon::getResistance(){
    return resistance;
}

void Pokemon::pokeprint()const{
    cout << "Name: " << name << endl;
    cout << "Type: " << poketype << endl;
    cout << "Moves: ";
    for(int i = 0; i < 4; i++){
        cout << movearr[i] << endl;
        //Overloaded operator used here definied in PokemonMove.hpp
    }
    cout << "Resistance: " << resistance << endl;
}
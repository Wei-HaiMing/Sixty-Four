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
    resistance = "";
    health = 0;
    dead = false;
    isActive = false;
    fullHealth = 0;
}

Pokemon::Pokemon(string name, string poketype, Move movearr[], string resist, int health, bool dead, bool isActive, int fullHealth){
    Pokemon::setName(name);
    Pokemon::setPokeType(poketype);
    Pokemon::setMove(movearr);
    // Pokemon::setSurf(surface);
    Pokemon::setResistance(resist);
    Pokemon::setHP(health);
    setDead(dead);
    setIsActive(isActive);
    setFullHealth(fullHealth);
}

Pokemon::~Pokemon()
{
    // SDL_FreeSurface(pokeSurf);
    std::cout << "Pokemon Deconstructor Ran\n";
}
void Pokemon::setFullHealth(int fullHealth)
{
    this->fullHealth = fullHealth;
}
void Pokemon::setIsActive(bool isActive)
{
    this->isActive = isActive;
}

void Pokemon::setDead(bool dead)
{
    this->dead = dead;
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

// void Pokemon::setSurf(SDL_Surface* surface){
//     this -> pokeSurf = surface;
// }

void Pokemon::setResistance(string resist){
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

Move Pokemon::getMove(int loc){
    
    return movearr[loc];

}
bool Pokemon::getDead()
{
    return dead;
}
int Pokemon::getHP()
{
    return health;
}
bool Pokemon::getIsActive()
{
    return isActive;
}
// SDL_Surface* Pokemon::getSurf(){
//     return pokeSurf;
// }

string Pokemon::getResistance(){
    return resistance;
}
int Pokemon::getFullHealth()
{
    return fullHealth;
}

void Pokemon::pokeprint()const{
    cout << "Name: " << name << endl;
    cout << "Type: " << poketype << endl;
    cout << "Moves: ";
    for(int i = 0; i < 4; i++){
        cout << movearr[i] << " ";
        //Overloaded operator used here definied in PokemonMove.hpp
    }
    cout << endl << "Resistance: " << resistance << endl;
    cout << "Is Active: " << isActive << endl;
}
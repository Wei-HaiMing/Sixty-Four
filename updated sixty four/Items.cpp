#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Items.hpp"
#include <iostream>

using namespace std;

Items::Items()
{
  potions = 0;
  full_restores = 0;
  soda_pops = 0;
}
Items::Items(int potions, int full_restores, int soda_pops)
{
  this->potions = potions;
  this->full_restores = full_restores;
  this->soda_pops = soda_pops;
}
void Items::setPotions(int potions)
{
  if (potions > 0) 
  {
  cout << "Used a Potion. Restored 20 HP to your Pokémon." << endl;
  } 
  else 
  {
  cout << "No more Potions left!" << endl;
  this->potions = potions;
  }
  SDL_Surface* surface = IMG_Load("potion.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
}
void Items::setFullRestores(int full_restores)
{
  if (full_restores > 0) 
  {
    cout << "Used a Full Restore. Fully restored HP and healed status conditions." << endl;
  } 
  else 
  {  
    cout << "No more Full Restores left!" << endl;
  }
  SDL_Surface* surface = IMG_Load("full-restore");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
}
void Items::setSodaPops(int soda_pops)
{
  if (soda_pops > 0) 
  {
    cout << "Used a Soda Pop. Restored 50 HP to your Pokémon." << endl;
  } 
  else 
  {
    cout << "No more Soda Pops left!" << endl;    
  }
  SDL_Surface* surface = IMG_Load("soda-pop.png");
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
}
int Items::getPotions()const
{
  return potions;
}
int Items::getFullRestores()const
{
  return full_restores;
}
int Items::getSodaPops()const
{
  return soda_pops;
}
void Items::print()const
{
  cout << "Potions: " << potions << endl;
  cout << "Full Restores: " << full_restores << endl;
  cout << "Soda Pops: " << soda_pops << endl;
}

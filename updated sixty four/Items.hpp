#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef ITEMS_HPP
#define ITEMS_HPP

class Items
{
public:
  Items();
  Items(int potions, int full_restores, int soda_pops);
  void setPotions(int potions);
  void setFullRestores(int full_restores);
  void setSodaPops(int soda_pops);
  int getPotions()const;
  int getFullRestores()const;
  int getSodaPops()const;
  void print()const;  

private:
  SDL_Renderer* renderer;
  SDL_Surface* surface;
  SDL_Texture* texture; 
  int potions;
  int full_restores;
  int soda_pops;

};
#endif // ITEMS_HPP
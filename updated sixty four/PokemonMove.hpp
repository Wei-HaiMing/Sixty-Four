#ifndef POKEMONMOVE_HPP
#define POKEMONMOVE_HPP
#include<string>
using namespace std;
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Move{

       public:
              Move();
              Move(string name, string type, int damage);
              void  setName (string name) ; 
              void setType(string type);
              void setDamage(int dmg);
              string getName();
              string getType();
              int getDamage();
              void printMove()const;

              friend ostream& operator<<(ostream& out, const Move& move) {
              out << "Name: " << move.name << std::endl << "Type: " << move.type << std::endl << "Damage: " << move.damage << std::endl;
              return out;
              }
              // void operator =(const Move& m2)
              // {      

              //        name = m2.name;
              //        type = m2.type;
              //        damage = m2.damage;

              // }
       // Added overloaded operator here for pokeprint() in Pokemon class. - Gabe

       private:
              string name, type;
              int damage;
              // struct textData{
              //        SDL_Texture* textTex;
              //        int w;
              //        int h;
              // };
};

#endif
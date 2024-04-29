#ifndef POKEMONMOVE_HPP
#define POKEMONMOVE_HPP
#include<string>
using namespace std;
#include <fstream>

class Move{

       public:
              Move();
              Move(string name, string type, int damage);
              void  setName (string name) ; 
              void setType(string type);
              void setDamage(int dmg);
              string getName() const;
              string getType()const;
              int getDamage() const;
              void printMove()const;

              friend ostream& operator<<(ostream& out, const Move& move) {
              out << "Name: " << move.getName() << std::endl << "Type: " << move.getType() << std::endl << "Damage: " << move.getDamage() << std::endl;
              return out;
              }
       // Added overloaded operator here for pokeprint() in Pokemon class. - Gabe

       private:
              string name, type;
              int damage;
};

#endif
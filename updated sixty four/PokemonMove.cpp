#include "PokemonMove.hpp"
#include <iostream>
#include <string>
#include<cassert>
using namespace std;

//Constructor for Pokemon Move class
Move::Move()
{
    
    name = "";
    type = "";
    damage=0;
}
Move::Move(string name, string type, int damage)
{
    this->name = name;
    this->type = type;
    assert(damage >= 0); //Ensure that the damage is not a negative number
    this->damage = damage;

}
void Move::setName (string name){
    this ->name = name;
}
void  Move:: setType(string type){
    this ->type = type;
}
void  Move :: setDamage(int damage){
    assert(damage >= 0);
    this ->damage = damage;
}

string Move::getName(){
    return name;
}
 
string Move::getType(){
    return type;
}
int Move:: getDamage(){
    return damage;
}
void Move::printMove()const{
    cout<<"Name: " << name << endl;
    cout<<"Type: " << type <<endl;
    cout<<"Damage: "<<damage<<endl;
}
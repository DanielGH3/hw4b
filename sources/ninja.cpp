#include "Ninja.hpp"
#include <iostream>

void Ninja::move(Character* enemy)
{
    Point* location = getPtrLocation();
    *location = Point::moveTowards(*location, enemy->getLocation(), speed);
}  

void Ninja::slash(Character* enemy)
{
    if(enemy == this)throw runtime_error("");
    if(!isAlive()) throw runtime_error("");
    if(enemy == nullptr) throw runtime_error("");
    if(!(enemy->isAlive())) throw runtime_error("");

    double dist = distance(enemy);
    if(isAlive()){
        if(dist < 1){
            enemy->hit(40);
        }else{
            //move(enemy);
        }
    }
}

void Ninja::attack(Character* enemy)
{
    slash(enemy);
}

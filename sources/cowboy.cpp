#include "Cowboy.hpp"
#include <iostream>
void Cowboy::shoot(Character* enemy)
{ 
    if(enemy == this)throw runtime_error("");
    if(!isAlive()) throw runtime_error("");
    if(enemy == nullptr) throw runtime_error("");
    if(!(enemy->isAlive())) throw runtime_error("");

    if(isAlive()){
        if(hasboolets()){
            enemy->hit(10);
            bullets --;
        }else{
            reload();
        }
    }
}

bool Cowboy::hasboolets()
{
    return bullets > 0;
}

void Cowboy::reload()
{
    if(!isAlive()) throw runtime_error("");
    bullets = 6;
}

void Cowboy::attack(Character* enemy)
{
    shoot(enemy);
}

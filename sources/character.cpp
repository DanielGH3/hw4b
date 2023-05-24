#include "Character.hpp"
#include <Point.hpp>
#include <iostream>

using namespace std;

bool Character::isAlive()
{
    return (health > 0);
}

double Character::distance(Character* cha)
{
    return location.distance(cha->location);
}

void Character::hit(int damage)
{
    if(damage < 0) throw std::invalid_argument("");

    health -= damage;
}

string Character::getName()
{
    return name;
}

Point Character::getLocation()
{
    return location;
}

int Character::getType()
{
    return type;
}

int Character::getHealth()
{
    return health;
}

string Character::print()
{
    string ret = "{";
    ret += (type == 2 ? "N" : "C");
    ret += ":" + name + ", ";
    ret += (!isAlive() ? "" : to_string(health) + ", ");
    ret += location.print() + "}";
    return  ret;
}

void Character::move(Character* enemy)
{
}

Point *Character::getPtrLocation()
{
    return &location;
}

bool* Character::getInTeam()
{
    return &inteam;
}

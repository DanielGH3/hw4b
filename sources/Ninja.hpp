#pragma once
#include "Character.hpp"
static constexpr int NINJA = 2;

class Ninja : public Character
{
    private:
        int speed;
    public:
        Ninja(int ninja_speed, string name, int health, Point location) : 
            speed(ninja_speed), Character(health, std::move(name), location, NINJA){}
        void move(Character* enemy) override;
        void slash(Character* enemy);
        void attack(Character* enemy) override;
};

const int youngspeed = 14;
const int younghealth = 100;

class YoungNinja : public Ninja
{
    public:
        YoungNinja(string name, Point location) : 
            Ninja(youngspeed,  std::move(name),younghealth, location){}
};

const int traindedspeed = 12;
const int traindhealth = 120;

class TrainedNinja : public Ninja
{
    public:
        TrainedNinja(string name, Point location) : 
            Ninja(traindedspeed, std::move(name),traindhealth,  location){}
};

const int oldspeed = 8;
const int oldhealth = 150;

class OldNinja : public Ninja
{
    public:
        OldNinja(string name, Point location) : 
            Ninja(oldspeed,  std::move(name),oldhealth, location){}
};

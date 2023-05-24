#pragma once
#include "Character.hpp"

static constexpr int COWBOY = 1;

const int cowboyhealth = 110;
const int bulletcount = 6;

class Cowboy : public Character
{
    private:
        int bullets;
    public:
        Cowboy(string name, Point location) : 
            bullets(bulletcount), Character(cowboyhealth, std::move(name), location, COWBOY) {}
        void shoot(Character* enemy);
        bool hasboolets();
        void reload();
        void attack(Character* enemy) override;
};


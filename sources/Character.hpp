#pragma once
#include "Point.hpp"
#include <string>

using namespace std;

static constexpr bool NOTINTEAM = false;
static constexpr int NONE = 3;
static constexpr int HUNDRED = 100;

class Character
{
    private:
        int health;        
        string name;
        Point location;
        int type;
        bool inteam;
    public:
        Character() : type(NONE), health(HUNDRED), inteam(NOTINTEAM), location(Point(0,0)){}
        Character(Character const &) = default;
        Character(Character &&) = default;
        Character& operator=(Character const &) = default;
        Character& operator=(Character &&) = default;
        virtual ~Character() = default;
        Character(int health, string name, Point location, int type) : 
            health(health), name(std::move(name)), location(location), type(type), inteam(NOTINTEAM) {}
        bool isAlive();
        double distance(Character* cha);
        void hit(int damage);
        virtual void attack(Character* enemy) = 0;
        string getName();
        Point getLocation();
        int getType();
        int getHealth();
        string print();
        virtual void move(Character* enemy);

        //gettersetter 
        Point* getPtrLocation();
        bool* getInTeam();
};
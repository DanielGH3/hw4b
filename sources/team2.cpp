#include "Team2.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace ariel;

Team2::Team2(Character *c)
{
    bool* inteam = c->getInTeam();
    if(*inteam) throw std::runtime_error("");
    *inteam = true;

    Character** team = getTeam();
    int* count = getCount();

    *count = 1;
    team[0] = c;
}

void Team2::attack(Team* enemyteam)
{
    if(enemyteam == nullptr) throw std::invalid_argument("");
    if((*enemyteam->getCount()) == 0) throw std::runtime_error("");
    if(enemyteam->stillAlive() == 0) throw std::runtime_error("");

    Character** team = getTeam();
    Character* leader = getLeader();
    int count = *getCount();

    //set new leader if none
    if(leader == nullptr){
        leader = team[0];
        if(leader == nullptr){
            throw runtime_error("Team is empty");
        }   

    }

    //set new leader on death
    if(!leader->isAlive()){
        int distance = 1000000;
        int tempdistance = 0;
        Character* tmp = nullptr;
        for (int i = 0; i < count; i++)
        {
            Character* newleader = team[i];
            tempdistance = leader->distance(newleader);
            if(tempdistance < distance && newleader->isAlive()){
                tmp = newleader;
                distance = tempdistance;
            }
        }
        leader = tmp;
    }

    if(leader == nullptr){
        throw runtime_error("Team is empty");
    }

    //find closest enemy
    Character* enemy = enemyteam->getClosestCharacter(leader);

    if(enemy == nullptr){
        return;
    }

    for (int i = 0; i < count; i++)
    {      
        if(!team[i]->isAlive()) continue;
        
        if(!enemy->isAlive()){
            enemy = enemyteam->getClosestCharacter(leader);
            if(enemy == nullptr){
                return;
            }
        }

        if(team[i]->getType() == NINJA)
        {
            if(team[i]->distance(enemy) < 1){
                enemy->hit(40);
            }else{
                team[i]->move(enemy);
            }
        }else{
            team[i]->attack(enemy);
        }
    }
}

string Team2::print()
{
    Character** team = getTeam();
    int count = *getCount();

    string ret = "";
    for (int i = 0; i < count; i++)
    {      
        ret += team[i]->print() + "\n";
    }
    return ret;
}

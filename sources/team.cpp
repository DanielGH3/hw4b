#include <iostream>
#include "Ninja.hpp"
#include "Cowboy.hpp"
#include "Team.hpp"

using namespace ariel;

Team::Team(Character *c)
{
    Init(c);
    *team = c;
}

void Team::Init(Character *c){
    bool* inteam = c->getInTeam();
    if(*inteam) throw std::runtime_error("");
    *inteam = true;

    count = 1;
    team = new Character*[ARRSIZE]{0};
    leader = c;
}

ariel::Team::~Team()
{
    for(int i = 0; i < count; i++){
        delete team[i];
    }

    delete[] team;
}

void Team::add(Character *c)
{
    if(count == 10) throw std::runtime_error("");

    bool* inteam = c->getInTeam();
    if(*inteam) throw std::runtime_error("");
    *inteam = true;

    if(count == 10) return;

    for(size_t i = 0; i < count; i++){
        if(team[i] == c) throw runtime_error("Cant add same player twice");
    }

    team[(size_t)(count++)] = c;
}


Character* Team::getClosestCharacter(Character* leader)
{
    Character* ret = nullptr;
    int maxdistance = 1000000;
    int tempdistance = 0;
    for (int i = 0; i < count; i++)
    {
        Character* temp = team[i];
        tempdistance = temp->distance(leader);
        if(tempdistance < maxdistance && temp->isAlive()){
            ret = temp;
            maxdistance = tempdistance;
        }
    }
    return ret;
}

Character** ariel::Team::getTeam()
{
    return team;
}

Character *ariel::Team::getLeader()
{
    return leader;
}

int *ariel::Team::getCount()
{
    return &count;
}

int Team::stillAlive()
{
    int cnt = 0;
    for (int i = 0; i < count; i++)
    {
        if(team[i]->isAlive()){
            cnt ++;
        }
    }
    return cnt;
}

void Team::attack(Team* enemyteam)
{
    if(enemyteam == nullptr) throw std::invalid_argument("");
    if((*enemyteam->getCount()) == 0) throw std::runtime_error("");
    if(enemyteam->stillAlive() == 0) throw std::runtime_error("");

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
        if(team[i]->getType() == COWBOY)
            team[i]->attack(enemy);
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
        }
    }
}

string Team::print()
{
    string ret = "";
    for (int i = 0; i < count; i++)
    {      
        if(team[i]->getType() == COWBOY)
            ret += team[i]->print() + "\n";
    }

    for (int i = 0; i < count; i++)
    {      
        if(team[i]->getType() == NINJA)
            ret += team[i]->print() + "\n";
    }
    return ret;
}

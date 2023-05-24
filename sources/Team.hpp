#pragma once
#include "Character.hpp"
#include "Ninja.hpp"
#include "Cowboy.hpp"

static constexpr int ARRSIZE = 10;

namespace ariel{
    class Team
    {
        private:
            int count;
            Character** team;
            Character* leader;
        public:
            Team() : count(0), team(new Character*[ARRSIZE]{0}), leader(nullptr){}
            Team(Character* cha);
            Team(Team const &) = default;
            Team(Team &&) = default;
            Team& operator=(Team const &) = default;
            Team& operator=(Team &&) = default;
            virtual ~Team();
            void add(Character* cha);
            Character* getClosestCharacter(Character* leader);
            virtual void attack(Team* team);
            virtual string print();
            
            void Init(Character* cha);

    
            int stillAlive();

            //getters
            Character** getTeam();
            Character* getLeader();
            int* getCount();
    };
}
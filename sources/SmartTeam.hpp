#pragma once
#include "Team.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"

namespace ariel
{
    class SmartTeam : public Team
    {
        public:
            SmartTeam(){}
            SmartTeam(Character* cha);
            SmartTeam(SmartTeam const &) = default;
            SmartTeam(SmartTeam &&) = default;
            ~SmartTeam() override = default;
            SmartTeam& operator=(SmartTeam const &) = default;
            SmartTeam& operator=(SmartTeam &&) = default;
            void attack(Team* team) override;
            string print() override;
    };     
}

#pragma once
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "SmartTeam.hpp"
#include "Team.hpp"

namespace ariel
{
    class Team2 : public Team
    {
        public:
            Team2(){}
            Team2(Character* cha);
            Team2(Team2 const &) = default;
            Team2(Team2 &&) = default;
            ~Team2() override = default;
            Team2& operator=(Team2 const &) = default;
            Team2& operator=(Team2 &&) = default;
            void attack(Team* team) override;
            string print() override;
    };     
}

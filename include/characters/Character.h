// Character.h
#pragma once

#include <string>
#include <vector>
#include "battle/Skill.h"

struct Stats
{
    int hp, atk, def, spd, lck;
};

class Character
{

public:
    std::string name;
    std::string affinity;
    std::string description;
    std::string icon;
    std::string role;

    Stats stats;
    Skill skill;

    const Stats& getStats() const { return stats;}
};

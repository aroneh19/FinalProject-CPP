#pragma once

#include <string>
#include "battle/Skill.h"
#include "game/Stats.h"  

class CharacterBase {
protected:
    std::string name;
    std::string affinity;
    Stats stats;
    Skill skill;

public:
    virtual ~CharacterBase() = default;

    const std::string& getName() const { return name; }
    const std::string& getAffinity() const { return affinity; }
    const Stats& getStats() const { return stats; }
    const Skill& getSkill() const { return skill; }

    // Optional: setters or abstract methods can go here
};

#pragma once

#include <string>
#include <vector>
#include "battle/Skill.h"
#include "characters/Character.h"

class PlayerCharacter {
public:
    std::string name;
    std::string affinity;
    std::string role;
    std::string description;
    Stats stats;
    Skill skill;

    const Stats& getStats() const { return stats; }
    const std::string& getName() const { return name; }
    const std::string& getAffinity() const { return affinity; }
    const std::string& getRole() const { return role; }
    const std::string& getDescription() const { return description; }
    const Skill& getSkill() const { return skill; }
};

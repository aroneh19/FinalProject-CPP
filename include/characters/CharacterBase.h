#pragma once

#include <string>
#include <battle/Skill.h>
#include "game/Stats.h"

class CharacterBase {
public:
    virtual ~CharacterBase() = default;

    virtual const std::string& getName() const = 0;
    virtual const std::string& getAffinity() const = 0;
    virtual const Stats& getStats() const = 0;
    virtual const Skill& getSkill() const = 0;
};

#pragma once

#include <string>

struct Skill {
    std::string name;
    std::string description;
    int cooldown;
    int currentCooldown = 0;
};
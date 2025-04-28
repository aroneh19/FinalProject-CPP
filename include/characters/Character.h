#pragma once
#include "characters/CharacterBase.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>

class Character : public CharacterBase
{
private:
    std::string role;
    int damageDealt;
    int damageThreshold;
    bool canUseSkill;

public:
    Character()
        : damageDealt(0), damageThreshold(100), canUseSkill(false) {}

    ~Character() override = default;

    int attack(CharacterBase &target) override;

    int useSkill(CharacterBase &target);

    const std::string &getRole() const { return role; }
    void setRole(const std::string &r) { role = r; }

    void increaseDamageDealt(int amount) { damageDealt += amount; }
    bool isSkillReady() const { return canUseSkill; }
    void resetSkill()
    {
        canUseSkill = false;
        damageDealt = 0;
    }
};

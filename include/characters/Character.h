#pragma once
#include "characters/CharacterBase.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>
#include "battle/Skill.h"

class Character : public CharacterBase
{
private:
    std::string role;
    Skill skill;
    int cooldown;
    int currentCooldown;
    int damageDealt;
    int damageThreshold;

public:
    Character()
        : currentCooldown(0), damageDealt(0), damageThreshold(100) {}

    ~Character() override = default;

    int attack(CharacterBase &target) override;

    int useSkill(CharacterBase &target);

    const std::string &getRole() const { return role; }
    void setRole(const std::string &r) { role = r; }

    void increaseDamageDealt(int amount) { damageDealt += amount; }
    void resetSkill()
    {
        currentCooldown = 0;
    }

    const Skill &getSkill() const { return skill; }
    void setSkill(const Skill &sk) { skill = sk; }
    int getCurrentCooldown() const { return currentCooldown; }
    void setCurrentCooldown(int cd) { currentCooldown = cd; }
    void decrementCooldown()
    {
        if (currentCooldown > 0)
            currentCooldown--;
    }

    int getSkillCooldown() const { return cooldown; }
    void setSkillCooldown(int cd) { cooldown = cd; }
};

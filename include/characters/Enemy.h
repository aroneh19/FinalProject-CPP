#pragma once
#include "characters/CharacterBase.h"
#include "characters/Character.h"
#include <vector>

class Enemy : public CharacterBase
{
    int tier;

public:
    Enemy() = default;
    Enemy(const Enemy&) = default;
    ~Enemy() override = default;

    int getTier() const { return tier; }
    void setTier(int t) { tier = t; }

    int attack(CharacterBase &target) override;

    Character* chooseTarget(std::vector<Character*>& heroes);

};

#pragma once
#include "characters/CharacterBase.h"

class Enemy : public CharacterBase
{
    int tier;

public:
    ~Enemy() override = default;

    int getTier() const { return tier; }
    void setTier(int t) { tier = t; }

    int attack(CharacterBase &target) override;
};

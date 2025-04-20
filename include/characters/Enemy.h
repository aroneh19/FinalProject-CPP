#pragma once
#include "characters/CharacterBase.h"

class Enemy : public CharacterBase {
    int tier;

public:
    int getTier() const { return tier; }
    void setTier(int t) { tier = t; }
};

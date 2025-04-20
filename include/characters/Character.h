#pragma once
#include "characters/CharacterBase.h"

class Character : public CharacterBase {
public:
    int attack(CharacterBase& target) override;
    int useSkill(CharacterBase& target) override;
    int useItem();
};

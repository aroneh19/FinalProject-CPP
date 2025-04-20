#pragma once
#include "characters/CharacterBase.h"

class Character : public CharacterBase
{
private:
    std::string role;

public:
    ~Character() override = default;
    
    int attack(CharacterBase &target) override;
    int useSkill(CharacterBase &target) override;

    const std::string &getRole() const { return role; }
    void setRole(const std::string &r) { role = r; }
};

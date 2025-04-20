#pragma once

#include "characters/CharacterBase.h"

class Character : public CharacterBase {
    std::string role;

public:
    const std::string& getRole() const { return role; }
    void setRole(const std::string& r) { role = r; }
};

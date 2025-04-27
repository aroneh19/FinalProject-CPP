#pragma once
#include <vector>
#include <characters/Character.h>

class Team
{
public:
    void addCharacter(Character character);
    const std::vector<Character> &getCharacters() const;
private:
    std::vector<Character> team;
};
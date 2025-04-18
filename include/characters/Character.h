// Character.h
#pragma once

#include <string>
#include <vector>

class Character {
public:
    std::string name;
    std::string affinity;
    int hp, atk, def, spd, lck;

    static std::vector<Character> LoadFromJson(const std::string& filePath);
};

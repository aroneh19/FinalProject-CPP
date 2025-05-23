#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>

#include "battle/Skill.h"
#include "characters/Character.h"
#include "characters/Enemy.h"

struct Affinity {
    std::string name;
    std::string code;
    std::string icon;
    std::string strong_against;
    std::string weak_against;
};

class JsonLoader {
public:
    JsonLoader();
    ~JsonLoader();

    std::vector<Character> loadCharacters(const std::string &filePath);
    std::vector<Enemy> loadEnemys(const std::string &filePath);
    std::vector<Enemy> loadBosses(const std::string &filePath);
    std::map<std::string, Affinity> loadAffinities(const std::string &filePath);

private:
    std::string readFileToString(const std::string &filePath);
    std::string extractString(const std::string &data, const std::string &key);
    int extractInt(const std::string &data, const std::string &key);
    std::vector<std::string> splitArrayEntries(const std::string &arrayStr);

    Character parseCharacter(const std::string &characterData);
    Enemy parseEnemy(const std::string &data);  
};

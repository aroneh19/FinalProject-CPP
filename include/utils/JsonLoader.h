#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>

struct Stats
{
    int hp;
    int atk;
    int def;
    int spd;
    int lck;
};

struct Skill
{
    std::string name;
    std::string description;
    int cooldown;
};

struct Character
{
    std::string name;
    std::string description;
    std::string affinity;
    std::string icon;
    std::string role;
    Stats stats;
    Skill skill;
};

struct Affinity
{
    std::string name;
    std::string code;
    std::string icon;
    std::string strong_against;
    std::string weak_against;
};

class JsonLoader
{
public:
    JsonLoader();
    ~JsonLoader();

    // Load methods for each data file
    std::vector<Character> loadPlayerFrontline(const std::string &filePath);
    std::vector<Character> loadPlayerBackline(const std::string &filePath);
    std::vector<Character> loadEnemies(const std::string &filePath);
    std::vector<Character> loadBosses(const std::string &filePath);
    std::map<std::string, Affinity> loadAffinities(const std::string &filePath);

private:
    // Helper functions for parsing
    std::string readFileToString(const std::string &filePath);
    std::string extractString(const std::string &data, const std::string &key);
    int extractInt(const std::string &data, const std::string &key);
    std::vector<std::string> splitArrayEntries(const std::string &arrayStr);
    Character parseCharacter(const std::string &characterData);
};
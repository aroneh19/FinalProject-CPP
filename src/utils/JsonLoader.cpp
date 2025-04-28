#include <utils/JsonLoader.h>
#include <iostream>
#include <fstream>
#include <sstream>

JsonLoader::JsonLoader()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

JsonLoader::~JsonLoader()
{
}

std::string JsonLoader::readFileToString(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::string JsonLoader::extractString(const std::string &data, const std::string &key)
{
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = data.find(searchKey);
    if (keyPos == std::string::npos)
        return "";
    size_t colonPos = data.find(":", keyPos);
    if (colonPos == std::string::npos)
        return "";
    size_t valueStartPos = data.find("\"", colonPos);
    if (valueStartPos == std::string::npos)
        return "";
    valueStartPos++;
    size_t valueEndPos = data.find("\"", valueStartPos);
    if (valueEndPos == std::string::npos)
        return "";
    return data.substr(valueStartPos, valueEndPos - valueStartPos);
}

int JsonLoader::extractInt(const std::string &data, const std::string &key)
{
    std::string searchKey = "\"" + key + "\"";
    size_t keyPos = data.find(searchKey);
    if (keyPos == std::string::npos)
        return 0;
    size_t colonPos = data.find(":", keyPos);
    if (colonPos == std::string::npos)
        return 0;
    size_t valueStartPos = colonPos + 1;
    while (valueStartPos < data.length() &&
           (data[valueStartPos] == ' ' || data[valueStartPos] == '\t' ||
            data[valueStartPos] == '\n' || data[valueStartPos] == '\r'))
    {
        valueStartPos++;
    }
    size_t valueEndPos = data.find_first_of(",}]", valueStartPos);
    if (valueEndPos == std::string::npos)
        return 0;
    std::string valueStr = data.substr(valueStartPos, valueEndPos - valueStartPos);
    try
    {
        return std::stoi(valueStr);
    }
    catch (const std::exception &)
    {
        return 0;
    }
}

std::vector<std::string> JsonLoader::splitArrayEntries(const std::string &arrayStr)
{
    std::vector<std::string> results;
    size_t startPos = arrayStr.find('[');
    if (startPos == std::string::npos)
        return results;
    size_t endPos = arrayStr.find_last_of(']');
    if (endPos == std::string::npos)
        return results;
    std::string contentStr = arrayStr.substr(startPos + 1, endPos - startPos - 1);
    int braceCount = 0;
    size_t itemStart = 0;
    for (size_t i = 0; i < contentStr.length(); i++)
    {
        if (contentStr[i] == '{')
            braceCount++;
        else if (contentStr[i] == '}')
            braceCount--;
        else if (contentStr[i] == ',' && braceCount == 0)
        {
            std::string item = contentStr.substr(itemStart, i - itemStart);
            results.push_back(item);
            itemStart = i + 1;
        }
    }
    if (itemStart < contentStr.length())
    {
        std::string item = contentStr.substr(itemStart);
        results.push_back(item);
    }
    return results;
}

Character JsonLoader::parseCharacter(const std::string& data) {
    Character character;
    character.setName(extractString(data, "name"));
    character.setAffinity(extractString(data, "affinity"));
    character.setRole(extractString(data, "role"));

    Stats stats;
    size_t statsStart = data.find("\"stats\"");
    if (statsStart != std::string::npos) {
        size_t blockStart = data.find("{", statsStart);
        size_t blockEnd = data.find("}", blockStart);
        if (blockStart != std::string::npos && blockEnd != std::string::npos) {
            std::string block = data.substr(blockStart, blockEnd - blockStart + 1);
            stats.hp = extractInt(block, "hp");
            stats.maxHp = stats.hp;
            stats.atk = extractInt(block, "atk");
            stats.def = extractInt(block, "def");
            stats.spd = extractInt(block, "spd");
            stats.lck = extractInt(block, "lck");
        }
    }
    character.setStats(stats);

    size_t skillsStart = data.find("\"skills\"");
    if (skillsStart == std::string::npos)
        skillsStart = data.find("\"skill\"");

    if (skillsStart != std::string::npos) {
        size_t skillBlockStart = data.find("{", skillsStart);
        size_t skillBlockEnd = data.find("}", skillBlockStart);
        if (skillBlockStart != std::string::npos && skillBlockEnd != std::string::npos) {
            std::string block = data.substr(skillBlockStart, skillBlockEnd - skillBlockStart + 1);
            Skill skill;
            skill.name = extractString(block, "name");
            skill.description = extractString(block, "description");
            skill.cooldown = extractInt(block, "cooldown");
            character.setSkill(skill);
        }
    }

    return character;
}

Enemy JsonLoader::parseEnemy(const std::string& data) {
    Enemy e;
    e.setName(extractString(data, "name"));
    e.setAffinity(extractString(data, "affinity"));

    Stats stats;
    size_t statsStart = data.find("\"stats\"");
    if (statsStart != std::string::npos) {
        size_t blockStart = data.find("{", statsStart);
        size_t blockEnd = data.find("}", blockStart);
        if (blockStart != std::string::npos && blockEnd != std::string::npos) {
            std::string block = data.substr(blockStart, blockEnd - blockStart + 1);
            stats.hp = extractInt(block, "hp");
            stats.maxHp = stats.hp;
            stats.atk = extractInt(block, "atk");
            stats.def = extractInt(block, "def");
            stats.spd = extractInt(block, "spd");
            stats.lck = extractInt(block, "lck");
        }
    }
    e.setStats(stats);
    e.setTier(extractInt(data, "tier"));

    size_t skillsStart = data.find("\"skills\"");
    if (skillsStart != std::string::npos) {
        size_t blockStart = data.find("{", skillsStart);
        size_t blockEnd = data.find("}", blockStart);
        if (blockStart != std::string::npos && blockEnd != std::string::npos) {
            std::string block = data.substr(blockStart, blockEnd - blockStart + 1);
            Skill skill;
            skill.name = extractString(block, "name");
            skill.description = extractString(block, "description");
            skill.cooldown = extractInt(block, "cooldown");
        }
    }
    return e;
}

std::vector<Character> JsonLoader::loadCharacters(const std::string &filePath)
{
    std::vector<Character> characters;
    std::string jsonData = readFileToString(filePath);
    std::vector<std::string> characterEntries = splitArrayEntries(jsonData);
    for (const auto &entry : characterEntries)
    {
        characters.push_back(parseCharacter(entry));
    }
    return characters;
}

std::vector<Enemy> JsonLoader::loadEnemys(const std::string &filePath)
{
    std::vector<Enemy> enemies;
    std::string jsonData = readFileToString(filePath);
    std::vector<std::string> entries = splitArrayEntries(jsonData);
    for (const auto &entry : entries)
    {
        enemies.push_back(parseEnemy(entry));
    }
    return enemies;
}

std::vector<Enemy> JsonLoader::loadBosses(const std::string &filePath)
{
    return loadEnemys(filePath);
}

std::map<std::string, Affinity> JsonLoader::loadAffinities(const std::string &filePath)
{
    std::map<std::string, Affinity> affinityMap;
    std::string jsonData = readFileToString(filePath);
    size_t affinitiesStart = jsonData.find("\"affinities\"");
    if (affinitiesStart == std::string::npos)
        return affinityMap;
    size_t arrayStart = jsonData.find("[", affinitiesStart);
    size_t arrayEnd = jsonData.find_last_of("]");
    if (arrayStart == std::string::npos || arrayEnd == std::string::npos)
        return affinityMap;
    std::string affinitiesArray = jsonData.substr(arrayStart, arrayEnd - arrayStart + 1);
    std::vector<std::string> affinityEntries = splitArrayEntries(affinitiesArray);
    for (const auto &entry : affinityEntries)
    {
        Affinity affinity;
        affinity.name = extractString(entry, "name");
        affinity.code = extractString(entry, "code");
        affinity.icon = extractString(entry, "icon");
        affinity.strong_against = extractString(entry, "strong_against");
        affinity.weak_against = extractString(entry, "weak_against");
        if (!affinity.code.empty())
        {
            affinityMap[affinity.code] = affinity;
        }
    }
    return affinityMap;
}

#include <utils/JsonLoader.h>
#include <iostream>
#include <fstream>
#include <sstream>

JsonLoader::JsonLoader()
{
    // Initialize random seed for any potential random operations
    srand(static_cast<unsigned int>(time(nullptr)));
}

JsonLoader::~JsonLoader()
{
    // No dynamic resources to clean up
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

    // Find the end of the value (comma or closing brace/bracket)
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

    // Count the opening and closing braces to properly parse nested objects
    int braceCount = 0;
    size_t itemStart = 0;

    for (size_t i = 0; i < contentStr.length(); i++)
    {
        if (contentStr[i] == '{')
        {
            braceCount++;
        }
        else if (contentStr[i] == '}')
        {
            braceCount--;
        }
        else if (contentStr[i] == ',' && braceCount == 0)
        {
            // Found a comma at the root level, split the item
            std::string item = contentStr.substr(itemStart, i - itemStart);
            results.push_back(item);
            itemStart = i + 1;
        }
    }

    // Add the last item
    if (itemStart < contentStr.length())
    {
        std::string item = contentStr.substr(itemStart);
        results.push_back(item);
    }

    return results;
}

Character JsonLoader::parseCharacter(const std::string &characterData)
{
    Character character;

    // Extract basic character info
    character.name = extractString(characterData, "name");
    character.description = extractString(characterData, "description");
    character.affinity = extractString(characterData, "affinity");
    character.role = extractString(characterData, "role");

    // Find stats section
    size_t statsStart = characterData.find("\"stats\"");
    if (statsStart != std::string::npos)
    {
        size_t statsBlockStart = characterData.find("{", statsStart);
        size_t statsBlockEnd = characterData.find("}", statsBlockStart);
        if (statsBlockStart != std::string::npos && statsBlockEnd != std::string::npos)
        {
            std::string statsBlock = characterData.substr(statsBlockStart, statsBlockEnd - statsBlockStart + 1);

            character.stats.hp = extractInt(statsBlock, "hp");
            character.stats.atk = extractInt(statsBlock, "atk");
            character.stats.def = extractInt(statsBlock, "def");
            character.stats.spd = extractInt(statsBlock, "spd");
            character.stats.lck = extractInt(statsBlock, "lck");
        }
    }

    // Find skills section - note: in some JSON files it's "skills", in others it might be "skill"
    size_t skillsStart = characterData.find("\"skills\"");
    if (skillsStart == std::string::npos)
    {
        skillsStart = characterData.find("\"skill\"");
    }

    if (skillsStart != std::string::npos)
    {
        size_t skillBlockStart = characterData.find("{", skillsStart);
        size_t skillBlockEnd = characterData.find("}", skillBlockStart);
        if (skillBlockStart != std::string::npos && skillBlockEnd != std::string::npos)
        {
            std::string skillBlock = characterData.substr(skillBlockStart, skillBlockEnd - skillBlockStart + 1);

            character.skill.name = extractString(skillBlock, "name");
            character.skill.description = extractString(skillBlock, "description");
            character.skill.cooldown = extractInt(skillBlock, "cooldown");
        }
    }

    return character;
}

std::vector<Character> JsonLoader::loadCharacters(const std::string &filePath)
{
    std::vector<Character> characters;
    std::string jsonData = readFileToString(filePath);

    std::vector<std::string> characterEntries = splitArrayEntries(jsonData);
    for (const auto &entry : characterEntries)
    {
        Character character = parseCharacter(entry);
        characters.push_back(character);
    }

    return characters;
}

std::vector<Character> JsonLoader::loadEnemies(const std::string &filePath)
{
    // Implementation is the same as loadCharacters
    return loadCharacters(filePath);
}

std::vector<Character> JsonLoader::loadBosses(const std::string &filePath)
{
    // Implementation is the same as loadCharacters
    return loadCharacters(filePath);
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

        // Use the code as the key for the map
        if (!affinity.code.empty())
        {
            affinityMap[affinity.code] = affinity;
        }
    }

    return affinityMap;
}

#include <iostream>
#include "ui/UiTeamSelect.h"
#include "utils/Utils.h"
#include "utils/JsonLoader.h"
#include "characters/Character.h"
#include <iomanip>
#include <vector>
#include "game/Team.h"

Team UiTeamSelect::Start()
{
    Team team;
    displayTeams("Front", team);
    displayTeams("Back", team);
    return team;
}

void UiTeamSelect::displayTeams(const std::string &role, Team &team)
{
    JsonLoader loader;
    std::vector<Character> characters = loader.loadCharacters("data/Characters.json");
    std::vector<Character> filteredCharacters;
    for (const auto &character : characters)
    {
        if (character.getRole() == role)
        {
            filteredCharacters.push_back(character);
        }
    }

    int teamCounter = 0;
    while (teamCounter < 2)
    {
        Utils::clearScreen();
        std::cout << "+----+--------------+-----+-----+-----+-----+-----+-----+\n";
        std::cout << "| Nr | Champion     | Aff | HP  | ATK | DEF | SPD | LCK |\n";
        std::cout << "+----+--------------+-----+-----+-----+-----+-----+-----+\n";

        for (size_t i = 0; i < filteredCharacters.size(); ++i)
        {
            const Character &c = filteredCharacters[i];
            const Stats &s = c.getStats();
            std::cout << "| "
                      << std::right << std::setw(2) << (i + 1) << " | "
                      << std::left << std::setw(12) << c.getName() << " |  "
                      << std::left << std::setw(3) << c.getAffinity() << " | "
                      << std::right << std::setw(3) << s.hp << " | "
                      << std::right << std::setw(3) << s.atk << " | "
                      << std::right << std::setw(3) << s.def << " | "
                      << std::right << std::setw(3) << s.spd << " | "
                      << std::right << std::setw(3) << s.lck << " |\n";
        }

        std::cout << "+----+--------------+-----+-----+-----+-----+-----+-----+\n";
        std::cout << "Select character " << (team.getCharacters().size() + 1) << " of your team: ";
        size_t firstCharacterIndex = 0;
        std::cin >> firstCharacterIndex;
        if (firstCharacterIndex < 1 || firstCharacterIndex > filteredCharacters.size())
        {
            std::cout << "Invalid selection. Please try again.\n";
            continue; 
        }
        team.addCharacter(filteredCharacters[firstCharacterIndex - 1]);
        filteredCharacters.erase(filteredCharacters.begin() + firstCharacterIndex - 1);
        teamCounter++;
    }
}

#include <iostream>
#include "ui/UiTeamSelect.h"
#include "utils/Utils.h"
#include "utils/JsonLoader.h"
#include "characters/Character.h"
#include <iomanip>
#include <vector>
#include "game/Team.h"

void UiTeamSelect::Start()
{
    Team team;
    displayTeams("F", team);
    displayTeams("B", team);
    int hallo;
    std::cin >> hallo;
}

void UiTeamSelect::displayTeams(const std::string &role, Team &team)
{
    JsonLoader loader;
    std::vector<Character> characters = loader.loadCharacters("data/Characters.json");
    std::vector<Character> filteredCharacters;
    for (const auto &character : characters)
    {
        if (character.role == role)
        {
            filteredCharacters.push_back(character);
        }
    }

    // Print header
    int teamCounter = 0;
    while (teamCounter < 2)
    {
        // Utils::clearScreen();
        std::cout << "+----+--------------+------+-----------+-----+-----+-----+-----+-----+\n";
        std::cout << "| Nr | Name         | Icon | Affinity  | HP  | ATK | DEF | SPD | LCK |\n";
        std::cout << "+----+--------------+------+-----------+-----+-----+-----+-----+-----+\n";

        // Loop through all characters
        for (size_t i = 0; i < filteredCharacters.size(); ++i)
        {
            const Character &c = filteredCharacters[i];
            const Stats &s = c.getStats();
            std::cout << "| "
                      << std::right << std::setw(2) << (i + 1) << " | "
                      << std::left << std::setw(12) << c.name << " |  "
                      << std::left << std::setw(5) << c.icon << " | "
                      << std::left << std::setw(9) << c.affinity << " | "
                      << std::right << std::setw(3) << s.hp << " | "
                      << std::right << std::setw(3) << s.atk << " | "
                      << std::right << std::setw(3) << s.def << " | "
                      << std::right << std::setw(3) << s.spd << " | "
                      << std::right << std::setw(3) << s.lck << " |\n";
        }

        std::cout << "+----+----------------+------+-----------+-----+-----+-----+-----+-----+\n";
        std::cout << "Select first character of your team: ";
        size_t firstCharacterIndex = 0;
        std::cin >> firstCharacterIndex;
        if (firstCharacterIndex < 1 || firstCharacterIndex > filteredCharacters.size())
        {
            std::cout << "Invalid selection. Please try again.\n";
            continue; // Skip to the next iteration of the while loop
        }
        team.addCharacter(filteredCharacters[firstCharacterIndex - 1]);
        filteredCharacters.erase(filteredCharacters.begin() + firstCharacterIndex - 1);
        teamCounter++;
        std::cout << "Selected character: " << team.getCharacters().back().name << "\n";
        std::cout << "Current team size: " << team.getCharacters().size() << "\n";
    }
}

void UiTeamSelect::selectTeam(Team &team)
{
    int hallo;
    std::cin >> hallo;
}
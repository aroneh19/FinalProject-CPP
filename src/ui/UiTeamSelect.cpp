#include <iostream>
#include "ui/UiTeamSelect.h"
#include "utils/Utils.h"
#include "utils/JsonLoader.h"
#include "characters/Character.h"
#include <iomanip>
#include <vector>

void UiTeamSelect::Start()
{
    std::vector<Character> team;
    displayTeams("F", team);
    displayTeams("B", team);
    int hallo;
    std::cin >> hallo;
}

void UiTeamSelect::displayTeams(const std::string &role, std::vector<Character> &team)
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
        //Utils::clearScreen();
        std::cout << "+----+----------------+------+-----------+-----+-----+-----+-----+-----+\n";
        std::cout << "| Nr | Name           | Icon | Affinity  | HP  | ATK | DEF | SPD | LCK |\n";
        std::cout << "+----+----------------+------+-----------+-----+-----+-----+-----+-----+\n";

        // Loop through all characters
        int counter = 0;
        for (size_t i = 0; i < filteredCharacters.size(); ++i)
        {
            const Character &c = filteredCharacters[i];
            const Stats &s = c.getStats();
            counter++;
            std::cout << "| "
                      << std::right << std::setw(2) << counter << " | "
                      << std::left << std::setw(14) << c.name << " | "
                      << std::left << std::setw(4) << c.icon << " | "
                      << std::left << std::setw(9) << c.affinity << " | "
                      << std::right << std::setw(3) << s.hp << " | "
                      << std::right << std::setw(3) << s.atk << " | "
                      << std::right << std::setw(3) << s.def << " | "
                      << std::right << std::setw(3) << s.spd << " | "
                      << std::right << std::setw(3) << s.lck << " |\n";
        }

        std::cout << "+----+----------------+------+-----------+-----+-----+-----+-----+-----+\n";
        std::cout << "Select first character of your team: ";
        int firstCharacterIndex = 0;
        std::cin >> firstCharacterIndex;
        if (firstCharacterIndex < 1 || firstCharacterIndex > counter)
        {
            std::cout << "Invalid selection. Please try again.\n";
            continue; // Skip to the next iteration of the while loop
        }
        team.push_back(filteredCharacters[firstCharacterIndex - 1]);
        filteredCharacters.erase(filteredCharacters.begin() + firstCharacterIndex - 1);
        teamCounter++;
        for (size_t i = 0; i < team.size(); i++)
        {
            std::cout << "Team " << i + 1 << ": " << team[i].name << "\n";
        }
    }
}

void UiTeamSelect::selectTeam(std::vector<Character> &team)
{
    int hallo;
    std::cin >> hallo;
}
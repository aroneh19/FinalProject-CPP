#include "ui/UiBattle.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <characters/Character.h>
#include <characters/Enemy.h>
#include <game/Team.h>
#include <utils/Utils.h>
#include <battle/TurnSystem.h>
#include <limits>
#include <sstream>


void UiBattle::BattleStart(Team &team, const std::vector<Enemy> &enemies, int wave, int round)
{
    Utils::clearScreen();

    std::stringstream title;
    title << "BATTLE " << wave << " - ROUND " << round;
    int totalWidth = 70;
    int padding = (totalWidth - title.str().length()) / 2;

    std::cout << "\n";
    std::cout << "╔" << std::string(totalWidth, '=') << "╗\n";
    std::cout << "║" << std::string(padding, ' ') << title.str() << std::string(totalWidth - padding - title.str().length(), ' ') << "║\n";
    std::cout << "╚" << std::string(totalWidth, '=') << "╝\n\n";

    std::cout << "Your Party\n";
    std::cout << std::string(70, '-') << "\n";

    const std::vector<Character> &heroes = team.getCharacters();
    for (const auto &hero : heroes)
    {
        const Stats &s = hero.getStats();

        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);

        std::string filledBar(filled, (char)219); // █ solid bar
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << hero.name
                  << " " << hero.affinity << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0"
                  << "\n";
    }

    std::cout << "\nEnemy Team\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto &enemy : enemies)
    {
        const Stats &s = enemy.getStats();

        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);

        std::string filledBar(filled, (char)219); // █ solid bar
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << enemy.getName()
                  << " " << enemy.getAffinity() << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0"
                  << "\n";
    }

    // Create a combined turn list
    std::vector<CharacterBase *> allActors;
    for (const auto &hero : heroes)
        allActors.push_back((CharacterBase *)&hero);
    for (const auto &enemy : enemies)
        allActors.push_back((CharacterBase *)&enemy);

    TurnSystem turnSystem(allActors);
    CharacterBase *currentActor = nullptr;

    while ((currentActor = turnSystem.getNextActor()))
    {
        Utils::clearScreen();
        std::cout << "\n=== " << currentActor->getName() << "'s Turn ===\n";
        std::cout << "Choose Action:\n";
        std::cout << "1. Regular Attack\n";
        std::cout << "2. Use Skill\n";
        std::cout << "3. Use Item\n";
        std::cout << "4. Quit\n";

        int choice;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 4)
        {
            std::cout << "Exiting battle...\n";
            break;
        }

        // For now, only proceed to next actor if valid choice
        if (choice >= 1 && choice <= 3)
        {
            std::cout << "\n" << currentActor->getName() << " does something...\n";
        }
    }
}

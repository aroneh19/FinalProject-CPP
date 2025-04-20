#include "ui/UiBattle.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <characters/Character.h>
#include <characters/Enemy.h>
#include <game/Team.h>
#include <utils/Utils.h>
#include <limits>
#include <sstream>
#include <game/TurnSystem.h>

void UiBattle::BattleStart(Team &team, const std::vector<Enemy> &enemies, int wave, int round)
{
    Utils::clearScreen();
    std::cout << "\n";
    std::cout << "╔" << std::string(70, '=') << "╗\n";
    std::cout << "╚" << std::string(70, '=') << "╝\n\n";
    std::stringstream title;
    title << "BATTLE " << wave << " - ROUND " << round;
    int totalWidth = 70;
    int padding = (totalWidth - title.str().length()) / 2;
    std::cout << "║" << std::string(padding, ' ') << title.str() << std::string(totalWidth - padding - title.str().length(), ' ') << "║\n";

    std::cout << "\nYour Party\n";
    std::cout << std::string(70, '-') << "\n";
    const std::vector<Character> &heroes = team.getCharacters();

    for (const auto &hero : heroes)
    {
        const Stats &s = hero.getStats();
        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);
        std::string filledBar(filled, '#');
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << hero.getName()
                  << " " << hero.getAffinity() << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0\n";
    }

    std::cout << "\nEnemy Team\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto &enemy : enemies)
    {
        const Stats &s = enemy.getStats();
        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);
        std::string filledBar(filled, '#');
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << enemy.getName()
                  << " " << enemy.getAffinity() << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0\n";
    }

    // Prepare turn order
    std::cout << "\n[TurnSystem] Initializing turn order...\n";
    std::vector<CharacterBase *> allCharacters;
    for (auto &hero : team.getCharacters())
    {
        std::cout << "  Player: " << hero.getName() << "\n";
        allCharacters.push_back(const_cast<Character*>(&hero));

    }
    for (auto &enemy : enemies)
    {
        std::cout << "  Enemy: " << enemy.getName() << "\n";
        allCharacters.push_back(const_cast<Enemy*>(&enemy));
    }

    TurnSystem turnSystem(allCharacters);
    std::cout << "[TurnSystem] Turn system initialized successfully.\n";

    while (true)
    {
        CharacterBase *actor = turnSystem.getNextActor();
        if (!actor)
        {
            std::cout << "[Error] Null actor encountered in turn system.\n";
            break;
        }

        std::cout << "\n" << actor->getName() << "'s turn!\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Skill\n";
        std::cout << "3. Item\n";
        std::cout << "4. Quit\n";
        std::cout << "Choose an action: ";

        int choice;
        std::cin >> choice;

        if (choice == 4)
        {
            std::cout << "Exiting battle...\n";
            break;
        }
        else
        {
            std::cout << "[Debug] You chose option " << choice << "\n";
        }
    }
}
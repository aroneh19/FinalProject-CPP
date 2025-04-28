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

void UiBattle::BattleStart(Team &team, std::vector<Enemy> enemies, int wave, int round)
{
    Utils::clearScreen();
    std::cout << "\n";
    std::cout << "╔" << std::string(70, '=') << "╗\n";

    std::stringstream title;
    title << "BATTLE " << wave << " - ROUND " << round;
    int totalWidth = 70;
    int padding = (totalWidth - title.str().length()) / 2;
    std::cout << "║" << std::string(padding, ' ') << title.str()
              << std::string(totalWidth - padding - title.str().length(), ' ') << "║\n";

    std::cout << "╚" << std::string(70, '=') << "╝\n";

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
                  << " | CD: " << hero.getSkillCooldown() - hero.getCurrentCooldown() << "\n";
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

    std::vector<CharacterBase *> allCharacters;
    for (auto &hero : team.getCharacters())
    {
        allCharacters.push_back(const_cast<Character *>(&hero));
    }
    for (auto &enemy : enemies)
    {
        allCharacters.push_back(const_cast<Enemy *>(&enemy));
    }

    TurnSystem turnSystem(allCharacters);

    while (true)
    {
        CharacterBase *actor = turnSystem.getNextActor();
        if (!actor)
        {
            break;
        }

        std::cout << "\n"
                  << actor->getName() << "'s turn!\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Skill\n";
        std::cout << "4. Quit\n";
        std::cout << "Choose an action: ";

        int choice;
        std::cin >> choice;

        if (choice == 1)
        {
            std::cout << "Choose a target:\n";
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                std::cout << i + 1 << ". " << enemies[i].getName()
                          << " (HP: " << enemies[i].getStats().hp << ")\n";
            }

            size_t targetIndex;
            std::cout << "Enter target number: ";
            std::cin >> targetIndex;

            if (targetIndex < 1 || targetIndex > static_cast<int>(enemies.size()))
            {
                std::cout << "[Error] Invalid target.\n";
                continue;
            }

            Enemy &target = enemies[targetIndex - 1];
            int damage = actor->attack(target);
            std::cout << actor->getName() << " attacked " << target.getName()
                      << " for " << damage << " damage!\n";
        }
        else if (choice == 2) // Skill
        {
            if (Character *character = dynamic_cast<Character *>(actor)) // Check if actor is of type Character
            {
                std::cout << "Choose a target:\n";
                for (size_t i = 0; i < enemies.size(); ++i)
                {
                    std::cout << i + 1 << ". " << enemies[i].getName()
                              << " (HP: " << enemies[i].getStats().hp << ")\n";
                }

                size_t targetIndex;
                std::cout << "Enter target number: ";
                std::cin >> targetIndex;

                if (targetIndex < 1 || targetIndex > enemies.size())
                {
                    std::cout << "[Error] Invalid target.\n";
                    continue;
                }

                Enemy &target = const_cast<Enemy &>(enemies[targetIndex - 1]);
                int damage = character->useSkill(target);
                std::cout << character->getName() << " used a skill on " << target.getName()
                          << " for " << damage << " damage!\n";
            }
            else
            {
                std::cout << actor->getName() << " cannot use a skill!\n";
            }
        }
        if (choice == 4)
        {
            std::cout << "Exiting battle...\n";
            break;
        }
    }
}

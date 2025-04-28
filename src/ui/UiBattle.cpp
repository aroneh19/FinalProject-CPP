#include "ui/UiBattle.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <characters/Character.h>
#include <characters/Enemy.h>
#include <game/Team.h>
#include <utils/Utils.h>
#include <sstream>
#include <thread>
#include <chrono>
#include <map>
#include <game/TurnSystem.h>

void UiBattle::BattleStart(Team &team, std::vector<Enemy> enemies, int wave, int round)
{
    Utils::clearScreen();

    std::vector<CharacterBase *> allCharacters;
    for (auto &hero : team.getCharacters())
        allCharacters.push_back(const_cast<Character *>(&hero));
    for (auto &enemy : enemies)
        allCharacters.push_back(const_cast<Enemy *>(&enemy));

    TurnSystem turnSystem(allCharacters);

    while (true)
    {
        Utils::clearScreen();
        drawBattleState(team, enemies, wave, round);

        CharacterBase *actor = turnSystem.getNextActor();
        if (!actor)
            break;

        if (actor->getStats().hp <= 0)
            continue; // Dead character, skip.

        if (Enemy *enemy = dynamic_cast<Enemy *>(actor))
        {
            std::vector<Character> livingHeroes;
            for (const auto &hero : team.getCharacters())
            {
                if (hero.getStats().hp > 0)
                    livingHeroes.push_back(hero);
            }

            if (livingHeroes.empty())
            {
                std::cout << "All heroes have fallen!\n";
                break;
            }

            Character &target = enemy->chooseTarget(livingHeroes);
            int damage = enemy->attack(target);

            std::cout << enemy->getName() << " attacks " << target.getName()
                      << " for " << damage << " damage!\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        }
        else if (Character *character = dynamic_cast<Character *>(actor))
        {
            std::cout << "\n"
                      << character->getName() << "'s turn!\n";
            std::cout << "1. Attack\n";
            std::cout << "2. Skill\n";
            std::cout << "4. Quit\n";
            std::cout << "Choose an action: ";

            int choice;
            std::cin >> choice;

            if (choice == 1)
            {
                // Attack choice
                std::map<int, Enemy *> aliveEnemies;
                int idx = 1;
                for (auto &enemy : enemies)
                {
                    if (enemy.getStats().hp > 0)
                    {
                        aliveEnemies[idx] = &enemy;
                        std::cout << idx << ". " << enemy.getName() << " (HP: " << enemy.getStats().hp << ")\n";
                        idx++;
                    }
                }

                if (aliveEnemies.empty())
                {
                    std::cout << "No enemies left!\n";
                    break;
                }

                int targetIndex;
                std::cout << "Enter target number: ";
                std::cin >> targetIndex;

                if (aliveEnemies.count(targetIndex))
                {
                    Enemy *target = aliveEnemies[targetIndex];
                    int damage = character->attack(*target);
                    std::cout << character->getName() << " attacked " << target->getName()
                              << " for " << damage << " damage!\n";
                }
                else
                {
                    std::cout << "[Error] Invalid target!\n";
                    continue;
                }
            }
            else if (choice == 2)
            {
                // Skill choice (optional future expansion)
                std::cout << character->getName() << " tries to use a skill (not implemented yet).\n";
                continue;
            }
            else if (choice == 4)
            {
                std::cout << "Exiting battle...\n";
                break;
            }
        }

        // Check if all enemies are dead
        bool allEnemiesDefeated = true;
        for (const auto &enemy : enemies)
        {
            if (enemy.getStats().hp > 0)
            {
                allEnemiesDefeated = false;
                break;
            }
        }

        if (allEnemiesDefeated)
        {
            std::cout << "\nAll enemies defeated! Moving to next round...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            break;
        }
    }
}

void UiBattle::drawBattleState(const Team &team, const std::vector<Enemy> &enemies, int wave, int round)
{
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
        int maxHp = (s.maxHp > 0) ? s.maxHp : 1;
        int filled = (s.hp * barLength) / maxHp;
        std::string filledBar(filled, '#');
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << hero.getName()
                  << " " << hero.getAffinity() << " HP [" << bar << "] "
                  << s.hp << "/" << maxHp
                  << " | CD: " << hero.getSkillCooldown() - hero.getCurrentCooldown() << "\n";
    }

    std::cout << "\nEnemy Team\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto &enemy : enemies)
    {
        const Stats &s = enemy.getStats();
        int barLength = 15;
        int maxHp = (s.maxHp > 0) ? s.maxHp : 1;
        int filled = (s.hp * barLength) / maxHp;
        std::string filledBar(filled, '#');
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << enemy.getName()
                  << " " << enemy.getAffinity() << " HP [" << bar << "] "
                  << s.hp << "/" << maxHp << "\n";
    }
}

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

void UiBattle::BattleStart(Team &team, const std::vector<Enemy> &enemies, int wave, int round)
{
    Utils::clearScreen();

    std::cout << "\n";
    std::cout << "╔" << std::string(70, '=') << "╗\n";

    std::stringstream title;
    title << "BATTLE " << wave << " - ROUND " << round;
    int totalWidth = 70;
    int padding = (totalWidth - title.str().length()) / 2;

    std::cout << "║"
              << std::string(padding, ' ')
              << title.str()
              << std::string(totalWidth - padding - title.str().length(), ' ')
              << "║\n";

    std::cout << "╚" << std::string(70, '=') << "╝\n\n";

    std::cout << "Your Party\n";
    std::cout << std::string(70, '-') << "\n";

    const std::vector<Character> &heroes = team.getCharacters();
    for (const auto &hero : heroes)
    {
        const Stats &s = hero.getStats();
        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);

        std::string filledBar;
        for (int i = 0; i < filled; ++i)
            filledBar += "■";
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << std::setw(12) << std::left << hero.name
                  << " " << hero.affinity << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0"
                  << "\n";
    }

    std::cout << "\nEnemy Team\n";
    std::cout << std::string(70, '-') << "\n";

    for (size_t i = 0; i < enemies.size(); ++i)
    {
        const Enemy &enemy = enemies[i];
        const Stats &s = enemy.getStats();

        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1;
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);

        std::string filledBar;
        for (int j = 0; j < filled; ++j)
            filledBar += "■";
        std::string emptyBar(barLength - filled, '-');
        std::string bar = filledBar + emptyBar;

        std::cout << i + 1 << ". " << std::setw(15) << std::left << enemy.getName()
                  << enemy.getAffinity() << " HP [" << bar << "] " << s.hp << "/" << maxHp << "\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

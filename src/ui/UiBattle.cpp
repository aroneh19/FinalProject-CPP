#include "ui/UiBattle.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <characters/Character.h>
#include <game/Team.h>
#include <utils/Utils.h>
#include <limits>

void UiBattle::BattleStart(Team &team)
{
    int round = 1;
    int wave = 1;

    Utils::clearScreen();
    std::cout << "\n";
    std::cout << "╔" << std::string(70, '=') << "╗\n";
    std::cout << "║" << std::setw(40) << std::right << "⚔️  BATTLE " << round << " - WAVE " << wave << std::setw(30) << std::left << " ║\n";
    std::cout << "╚" << std::string(70, '=') << "╝\n\n";

    std::cout << "Your Party\n";
    std::cout << std::string(70, '-') << "\n";

    const std::vector<Character> &heroes = team.getCharacters();

    for (const auto &hero : heroes)
    {
        const Stats &s = hero.getStats();

        int barLength = 15;
        int maxHp = s.hp > 0 ? s.hp : 1; // fallback to avoid division by 0
        int filled = static_cast<int>((static_cast<float>(s.hp) / maxHp) * barLength);
        std::string bar = std::string(filled, '#') + std::string(barLength - filled, '-');

        std::cout << std::setw(12) << std::left << hero.name
                  << " " << hero.affinity << " HP [" << bar << "] " << s.hp << "/" << maxHp
                  << " | CD: 0"
                  << "\n";
    }

    std::cout << "\n";
    std::cout << "(Enemies will be implemented here...)\n";

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
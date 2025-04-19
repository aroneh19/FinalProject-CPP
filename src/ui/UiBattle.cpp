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
    
    std::string title = "⚔️  BATTLE " + std::to_string(round) + " - WAVE " + std::to_string(wave);
    int width = 70;
    int padding = (width - title.length()) / 2;

    std::cout << "╔" << std::string(width, '=') << "╗\n";
    std::cout << "║" << std::string(padding, ' ') << title << std::string(width - padding - title.length(), ' ') << "║\n";
    std::cout << "╚" << std::string(width, '=') << "╝\n\n";


    std::cout << "Your Party\n";
    std::cout << std::string(70, '-') << "\n";

    const std::vector<Character> &heroes = team.getCharacters();

    for (const auto &hero : heroes)
    {
        const Stats &s = hero.getStats();

        int barLength = 15;
        int currentHp = s.hp;
        int maxHp = s.hp > 0 ? s.hp : 1; // fallback to avoid division by 0
    
        int filled = static_cast<int>((static_cast<float>(currentHp) / maxHp) * barLength);
    
        // Build filled green squares
        std::string filledBar = "";
        for (int i = 0; i < filled; ++i)
            filledBar += "\033[32m■\033[0m"; // green square
    
        // Build empty gray dashes
        std::string emptyBar(barLength - filled, '-');
    
        std::string bar = filledBar + emptyBar;

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

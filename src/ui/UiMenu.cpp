#include <iostream>
#include <ui/UiMenu.h>
#include <battle/Skill.h>
#include <utils/Utils.h>
#include <utils/JsonLoader.h>
#include <iomanip>
#include <vector>
#include "ui/UiTeamSelect.h"
#include <limits>
#include "ui/UiBattle.h"
#include "battle/BattleManager.h"  

void UiMenu::Start()
{
    ShowMainMenu();
}

void UiMenu::ShowMainMenu()
{
    int choice = -1;

    while (choice != 3)
    {
        Utils::clearScreen();
        std::cout << "=== Heroes of the Abyss ===\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. View Characters\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        HandleInput(choice);
    }
}

void UiMenu::HandleInput(int choice)
{
    switch (choice)
    {
    case 1:
        StartNewGame();
        break;
    case 2:
        ViewCharacters();
        break;
    case 3:
        ExitGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void UiMenu::StartNewGame()
{
    UiTeamSelect teamSelect;
    Team team = teamSelect.Start();

    BattleManager manager;
    manager.startAllWaves(team);
}

void UiMenu::ViewCharacters()
{
    Utils::clearScreen();
    JsonLoader loader;
    std::vector<Character> characters = loader.loadCharacters("data/Characters.json");

    // Print header
    std::cout << "+----+----------------+-------+-----+-----------+-----+-----+-----+\n";
    std::cout << "| Nr | Champion       | Role  | Aff | HP  | ATK | DEF | SPD | LCK |\n";
    std::cout << "+----+----------------+-------+-----+-----------+-----+-----+-----+\n";

    // Loop through all characters
    for (size_t i = 0; i < characters.size(); ++i)
    {
        const Character &c = characters[i];
        const Stats &s = c.getStats();

        std::cout << "| "
                  << std::right << std::setw(2) << i + 1 << " | "
                  << std::left << std::setw(14) << c.getName() << " | "
                  << std::left << std::setw(5) << c.getRole() << " | "
                  << std::left << std::setw(3) << c.getAffinity() << " | "
                  << std::right << std::setw(3) << s.hp << " | "
                  << std::right << std::setw(3) << s.atk << " | "
                  << std::right << std::setw(3) << s.def << " | "
                  << std::right << std::setw(3) << s.spd << " | "
                  << std::right << std::setw(3) << s.lck << " |\n";
    }

    std::cout << "+----+----------------+-------+-----+-----------+-----+-----+-----+\n";

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear leftover '\n'
    std::string temp;
    std::getline(std::cin, temp);
}

void UiMenu::ExitGame()
{
    std::cout << "Thanks for playing!\n";
    exit(0);
}
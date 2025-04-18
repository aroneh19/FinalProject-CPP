#include <iostream>
#include <ui/UiMenu.h>
#include <characters/PlayerCharacter.h>
#include <battle/Skill.h>
#include <utils/Utils.h>
#include <utils/JsonLoader.h>
#include <iomanip>
#include <vector>
#include "ui/UiTeamSelect.h"

void UiMenu::Start()
{
    ShowMainMenu();
}

void UiMenu::ShowMainMenu()
{
    int choice = -1;

    while (choice != 5)
    {
        Utils::clearScreen();
        std::cout << "=== Heroes of the Abyss ===\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. View Characters\n";
        std::cout << "4. How to Play\n";
        std::cout << "5. Exit\n";
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
        LoadGame();
        break;
    case 3:
        ViewCharacters();
        break;
    case 4:
        HowToPlay();
        break;
    case 5:
        ExitGame();
        break;
    default:
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void UiMenu::StartNewGame()
{
    UiTeamSelect teamSelect;
    teamSelect.Start();
}

void UiMenu::LoadGame()
{
    std::cout << "Loading game...\n";
}

void UiMenu::ViewCharacters()
{
    Utils::clearScreen();
    JsonLoader loader;
    std::vector<Character> characters = loader.loadCharacters("data/Characters.json");

    // Print header
    std::cout << "+----+----------------+------+------+-----------+-----+-----+-----+-----+-----+\n";
    std::cout << "| Nr | Name           | Icon | Role | Affinity  | HP  | ATK | DEF | SPD | LCK |\n";
    std::cout << "+----+----------------+------+------+-----------+-----+-----+-----+-----+-----+\n";

    // Loop through all characters
    for (size_t i = 0; i < characters.size(); ++i)
    {
        const Character &c = characters[i];
        const Stats &s = c.getStats();

        std::cout << "| "
                  << std::right << std::setw(2) << i + 1 << " | "
                  << std::left << std::setw(14) << c.name << " | "
                  << std::left << std::setw(4) << c.icon << " | "
                  << std::left << std::setw(4) << c.role << " | "
                  << std::left << std::setw(9) << c.affinity << " | "
                  << std::right << std::setw(3) << s.hp << " | "
                  << std::right << std::setw(3) << s.atk << " | "
                  << std::right << std::setw(3) << s.def << " | "
                  << std::right << std::setw(3) << s.spd << " | "
                  << std::right << std::setw(3) << s.lck << " |\n";
    }

    std::cout << "+----+----------------+------+------+-----------+-----+-----+-----+-----+-----+\n";

    // Ask user for a character to see description
    std::string inputName;
    std::cout << "\nEnter the name of a character to view their description: ";
    std::getline(std::cin, inputName);

    // Search and print the description
    bool found = false;
    for (const auto &c : characters)
    {
        if (c.name == inputName)
        {
            std::cout << "\nDescription for " << c.name << ": " << c.description << "\n";
            found = true;
            break;
        }
    }

    if (!found)
    {
        std::cout << "Character '" << inputName << "' not found.\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::string temp;
    std::getline(std::cin, temp);
}

void UiMenu::HowToPlay()
{
    Utils::clearScreen();
    std::cout << "How to play:\n";
    std::cout << "1. Use arrow keys to navigate.\n";
    std::cout << "2. Press Enter to select.\n";
    std::cout << "3. Follow the on-screen instructions.\n";
    std::cout << "4. Have fun!\n";
    std::cin >> std::ws;
}

void UiMenu::ExitGame()
{
    std::cout << "Thanks for playing!\n";
    exit(0);
}
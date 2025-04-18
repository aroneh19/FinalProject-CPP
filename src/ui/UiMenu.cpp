#include <iostream>
#include <ui/UiMenu.h>
#include <characters/PlayerCharacter.h>
#include <battle/Skill.h>

void UiMenu::Start()
{
    ShowMainMenu();
}

void UiMenu::ShowMainMenu()
{
    std::cout << "WELCOME TO DUNGEON WARS JRPG\n";

    int choice = -1;

    while (choice != 5)
    {
        std::cout << "\n=== Heroes of the Abyss ===\n";
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
    //UiTeamSelect teamSelect;
    //teamSelect.Start();
}

void UiMenu::LoadGame()
{
    std::cout << "Loading game...\n";
}

void UiMenu::ViewCharacters()
{
    std::cout << "Viewing characters...\n";
}

void UiMenu::HowToPlay()
{
    std::cout << "How to play:\n";
    std::cout << "1. Use arrow keys to navigate.\n";
    std::cout << "2. Press Enter to select.\n";
    std::cout << "3. Follow the on-screen instructions.\n";
    std::cout << "4. Have fun!\n";
}

void UiMenu::ExitGame()
{
    std::cout << "Thanks for playing!\n";
    exit(0);
}
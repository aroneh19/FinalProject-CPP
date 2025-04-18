#include <iostream>
#include <../../include/characters/PlayerCharacter.h>
#include <../../include/battle/Skill.h>

void view_characters(const std::vector<Character>& characters) {
    

    std::cout << "Displaying characters...\n";
}

void how_to_play() {
    std::cout << "Instructions on how to play the game...\n";
}

int main() {
    std::cout << "WELCOME TO DUNGEON WARS JRPG\n";

    int choice;

    std::cout << "1. Start Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. View Characters\n";
    std::cout << "4. How to Play\n";
    std::cout << "5. Exit\n";

    std::cout << "Select an option: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
    
}
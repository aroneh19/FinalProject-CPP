#include "game/TurnSystem.h"
#include "characters/CharacterBase.h"
#include <algorithm>
#include <iostream>

TurnSystem::TurnSystem(const std::vector<CharacterBase*>& allCharacters)
    : currentIndex(0)
{
    std::cout << "[TurnSystem] Initializing turn order...\n";
    turnOrder.clear();

    for (CharacterBase* c : allCharacters) {
        if (c == nullptr) {
            std::cout << "[TurnSystem] Warning: Null character pointer detected, skipping.\n";
            continue;
        }

        Stats s = c->getStats();
        int score = s.spd * 2 + s.lck;

        std::cout << "  -> " << c->getName() 
                  << " | SPD: " << s.spd 
                  << " | LCK: " << s.lck 
                  << " | Score: " << score << "\n";

        turnOrder.push_back({ c, score });
    }

    std::sort(turnOrder.begin(), turnOrder.end(), [](const TurnEntry& a, const TurnEntry& b) {
        return a.turnScore > b.turnScore;
    });

    std::cout << "[TurnSystem] Turn order initialized with " << turnOrder.size() << " characters.\n";
}

CharacterBase* TurnSystem::getNextActor() {
    if (turnOrder.empty()) {
        std::cout << "[TurnSystem] Error: Turn order is empty!\n";
        return nullptr;
    }

    if (currentIndex >= static_cast<int>(turnOrder.size())) {
        std::cout << "[TurnSystem] Warning: currentIndex overflow, resetting to 0\n";
        currentIndex = 0;
    }

    CharacterBase* actor = turnOrder[currentIndex].actor;
    if (!actor) {
        std::cout << "[TurnSystem] Error: Null actor found at index " << currentIndex << "\n";
        return nullptr;
    }

    std::cout << "[TurnSystem] " << actor->getName() << "'s turn (index " << currentIndex << ").\n";
    currentIndex = (currentIndex + 1) % turnOrder.size();
    return actor;
}

CharacterBase* TurnSystem::peekCurrentActor() const {
    if (turnOrder.empty()) return nullptr;
    return turnOrder[currentIndex].actor;
}

void TurnSystem::reset() {
    currentIndex = 0;
    std::cout << "[TurnSystem] Turn system reset.\n";
}

void TurnSystem::printTurnOrder() const {
    std::cout << "[TurnSystem] Current Turn Order:\n";
    for (size_t i = 0; i < turnOrder.size(); ++i) {
        auto* actor = turnOrder[i].actor;
        if (actor) {
            std::cout << "  " << i + 1 << ". " << actor->getName()
                      << " (SPD: " << actor->getStats().spd
                      << ", LCK: " << actor->getStats().lck
                      << ", Score: " << turnOrder[i].turnScore << ")\n";
        } else {
            std::cout << "  " << i + 1 << ". [Null Actor]\n";
        }
    }
}

#include "game/TurnSystem.h"
#include "characters/CharacterBase.h"
#include <algorithm>
#include <iostream>

TurnSystem::TurnSystem(const std::vector<CharacterBase*>& allCharacters)
    : currentIndex(0)
{
    turnOrder.clear();

    for (CharacterBase* c : allCharacters) {
        if (c == nullptr) {
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
}

CharacterBase* TurnSystem::getNextActor() {
    if (turnOrder.empty()) {
        return nullptr;
    }

    if (currentIndex >= static_cast<int>(turnOrder.size())) {
        currentIndex = 0;
    }

    CharacterBase* actor = turnOrder[currentIndex].actor;
    if (!actor) {
        return nullptr;
    }

    currentIndex = (currentIndex + 1) % turnOrder.size();
    return actor;
}

CharacterBase* TurnSystem::peekCurrentActor() const {
    if (turnOrder.empty()) return nullptr;
    return turnOrder[currentIndex].actor;
}

void TurnSystem::reset() {
    currentIndex = 0;
}

// void TurnSystem::printTurnOrder() const {
//     for (size_t i = 0; i < turnOrder.size(); ++i) {
//         auto* actor = turnOrder[i].actor;
//         if (actor) {
//                       << " (SPD: " << actor->getStats().spd
//                       << ", LCK: " << actor->getStats().lck
//                       << ", Score: " << turnOrder[i].turnScore << ")\n";
//         } else {
//             std::cout << "  " << i + 1 << ". [Null Actor]\n";
//         }
//     }
// }

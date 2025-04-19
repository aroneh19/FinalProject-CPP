#include "battle/TurnSystem.h"
#include <algorithm>
#include <cstdlib>

TurnSystem::TurnSystem(const std::vector<CharacterBase*>& allCharacters) : currentIndex(0) {
    for (auto* c : allCharacters) {
        int score = c->getStats().spd * 2 + rand() % (c->getStats().lck + 1);
        turnOrder.push_back({ c, score });
    }

    std::sort(turnOrder.begin(), turnOrder.end(), [](const TurnEntry& a, const TurnEntry& b) {
        return a.turnScore > b.turnScore;
    });
}

CharacterBase* TurnSystem::getNextActor() {
    if (currentIndex >= turnOrder.size()) return nullptr;
    return turnOrder[currentIndex++].actor;
}

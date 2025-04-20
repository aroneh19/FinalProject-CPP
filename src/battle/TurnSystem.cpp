#include "battle/TurnSystem.h"
#include "characters/CharacterBase.h" // Needed for full definition
#include <algorithm>


TurnSystem::TurnSystem(const std::vector<CharacterBase*>& allCharacters)
    : currentIndex(0) {
    turnOrder = allCharacters;

    std::sort(turnOrder.begin(), turnOrder.end(), [](CharacterBase* a, CharacterBase* b) {
        if (a->getStats().spd != b->getStats().spd)
            return a->getStats().spd > b->getStats().spd;
        return a->getStats().lck > b->getStats().lck;
    });    
}

CharacterBase* TurnSystem::getNextActor() {
    if (turnOrder.empty()) return nullptr;

    CharacterBase* actor = turnOrder[currentIndex];
    currentIndex = (currentIndex + 1) % turnOrder.size();
    return actor;
}

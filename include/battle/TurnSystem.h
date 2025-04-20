#pragma once

#include <vector>

class CharacterBase;  // Forward declaration

class TurnSystem {
public:
    TurnSystem(const std::vector<CharacterBase*>& allCharacters);
    CharacterBase* getNextActor();

private:
    std::vector<CharacterBase*> turnOrder;
    size_t currentIndex;
};

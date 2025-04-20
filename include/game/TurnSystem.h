#pragma once

#include <vector>
#include "characters/CharacterBase.h"

struct TurnEntry {
    CharacterBase* actor;
    int turnScore;
};

class TurnSystem {
public:
    TurnSystem(const std::vector<CharacterBase*>& allCharacters);

    CharacterBase* getNextActor();
    CharacterBase* peekCurrentActor() const;
    void reset();
    void printTurnOrder() const;

private:
    std::vector<TurnEntry> turnOrder;
    int currentIndex;
};

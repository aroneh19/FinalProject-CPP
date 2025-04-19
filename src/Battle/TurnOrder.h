#pragma once
#include <vector>
#include <characters/CharacterBase.h> // abstract or base class for both PlayerCharacter and EnemyCharacter

struct TurnEntry {
    CharacterBase* actor;
    int turnScore;
};

class TurnSystem {
public:
    TurnSystem(const std::vector<CharacterBase*>& allCharacters);

    void calculateTurnOrder();
    CharacterBase* getNextActor();

private:
    std::vector<TurnEntry> turnOrder;
    int currentIndex;
};

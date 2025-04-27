#pragma once

#include <vector>
#include <characters/CharacterBase.h>
#include <characters/Enemy.h>
#include <game/Team.h>

class UiBattle {
public:
    void BattleStart(Team &team, std::vector<Enemy> enemies, int wave, int round);

private:
    void DisplayParty(const std::vector<CharacterBase*>& party);
    void DisplayEnemies(const std::vector<Enemy>& enemies);
    void DisplayTurnOptions(CharacterBase* actor);
    void HandleTurn(CharacterBase* actor);  
};

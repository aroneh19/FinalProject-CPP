#pragma once

#include <vector>
#include <characters/CharacterBase.h>
#include <characters/Character.h>
#include <characters/Enemy.h>
#include <game/Team.h>

class UiBattle {
public:
    void BattleStart(Team& team, std::vector<Enemy> enemies, int wave, int round);

private:
    void drawBattleState(const Team& team, const std::vector<Enemy>& enemies, int wave, int round);
};
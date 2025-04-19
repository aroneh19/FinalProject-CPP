// UiBattle.h
#pragma once

#include <vector>
#include <characters/Character.h>
#include <characters/EnemyCharacter.h>
#include <game/Team.h>

class UiBattle {
public:
    void BattleStart(Team& team, const std::vector<EnemyCharacter>& enemies, int wave, int round);
};

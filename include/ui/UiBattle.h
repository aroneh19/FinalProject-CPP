// UiBattle.h
#pragma once

#include <vector>
#include <characters/Character.h>
#include <characters/Enemy.h>
#include <game/Team.h>

class UiBattle
{
public:
    void BattleStart(Team &team, const std::vector<Enemy> &enemies, int wave, int round);
};

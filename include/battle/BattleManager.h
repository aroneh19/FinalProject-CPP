#pragma once

#include <vector>
#include <characters/Enemy.h>
#include <game/Team.h>

class BattleManager
{
public:
    void startAllWaves(Team &team);

private:
    void runWave(int waveNumber, Team &team);
    std::vector<Enemy> generateEnemiesForRound(int waveNumber, int roundNumber);
    std::vector<Enemy> generateBossForWave(int waveNumber);
};

#pragma once

#include <vector>
#include <characters/EnemyCharacter.h>
#include <game/Team.h>

class BattleManager {
public:
    void startAllWaves(Team& team);

private:
    void runWave(int waveNumber, Team& team);
    std::vector<EnemyCharacter> generateEnemiesForRound(int waveNumber, int roundNumber);
    std::vector<EnemyCharacter> generateBossForWave(int waveNumber);
};

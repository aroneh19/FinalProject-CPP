#include "battle/WaveManager.h"

WaveManager::WaveManager()
{
    currentWave = 1;
    currentRound = 1;
}

void WaveManager::startNextWave()
{
    currentWave++;
    currentRound = 1;
}

void WaveManager::advanceRound()
{
    currentRound++;
}

int WaveManager::getWave() const
{
    return currentWave;
}

int WaveManager::getRound() const
{
    return currentRound;
}

bool WaveManager::isBossRound() const
{
    return currentRound == 5;
}

bool WaveManager::isWaveComplete() const
{
    return currentRound > 5;
}

// Example: Tier is equal to wave number (1–3)
int WaveManager::getEnemyTier() const
{
    return currentWave;
}

void WaveManager::reset()
{
    currentWave = 1;
    currentRound = 1;
}

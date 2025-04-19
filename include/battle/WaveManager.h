#pragma once

class WaveManager
{
private:
    int currentWave;
    int currentRound;

public:
    WaveManager();

    void startNextWave();
    void advanceRound();

    int getWave() const;
    int getRound() const;
    bool isBossRound() const;
    int getEnemyTier() const;
    bool isWaveComplete() const;

    void reset();
};

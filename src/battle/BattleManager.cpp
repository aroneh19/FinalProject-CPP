#include "battle/BattleManager.h"
#include "ui/UiBattle.h"
#include "utils/JsonLoader.h"
#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <ctime>     // for std::time

void BattleManager::startAllWaves(Team& team) {
    for (int wave = 1; wave <= 3; ++wave) {
        runWave(wave, team);
    }
}

void BattleManager::runWave(int waveNumber, Team& team) {
    for (int round = 1; round <= 5; ++round) {
        std::vector<EnemyCharacter> enemies;

        if (round < 5) {
            enemies = generateEnemiesForRound(waveNumber, round);
        } else {
            enemies = generateBossForWave(waveNumber);
        }

        UiBattle ui;
        ui.BattleStart(team, enemies, waveNumber, round);
    }
}

std::vector<EnemyCharacter> BattleManager::generateEnemiesForRound(int waveNumber, int roundNumber) {
    JsonLoader loader;
    std::vector<EnemyCharacter> allEnemies = loader.loadEnemyCharacters("data/Enemies.json");

    std::vector<EnemyCharacter> filtered;

    // Add enemies based on round rules for this wave
    int numEnemies = 3;
    int maxTier = waveNumber;

    if (waveNumber == 1) {
        switch (roundNumber) {
            case 1: numEnemies = 2; break;
            case 2: numEnemies = 3; break;
            case 3: numEnemies = 2; maxTier = 2; break;
            case 4: numEnemies = 4; break;
        }
    } else if (waveNumber == 2) {
        switch (roundNumber) {
            case 1: numEnemies = 3; break;
            case 2: numEnemies = 3; break;
            case 3: numEnemies = 3; maxTier = 2; break;
            case 4: numEnemies = 4; maxTier = 2; break;
        }
    } else if (waveNumber == 3) {
        switch (roundNumber) {
            case 1: numEnemies = 3; maxTier = 2; break;
            case 2: numEnemies = 4; maxTier = 2; break;
            case 3: numEnemies = 3; maxTier = 3; break;
            case 4: numEnemies = 4; maxTier = 3; break;
        }
    }

    for (const auto& e : allEnemies) {
        if (e.getTier() <= maxTier) {
            filtered.push_back(e);
        }
    }

    std::shuffle(filtered.begin(), filtered.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    if (numEnemies > static_cast<int>(filtered.size())) {
        numEnemies = static_cast<int>(filtered.size());
    }

    return std::vector<EnemyCharacter>(filtered.begin(), filtered.begin() + numEnemies);
}

std::vector<EnemyCharacter> BattleManager::generateBossForWave(int waveNumber) {
    JsonLoader loader;
    std::vector<EnemyCharacter> allBosses = loader.loadEnemyCharacters("data/Bosses.json");
    std::vector<EnemyCharacter> filtered;

    for (const auto& e : allBosses) {
        if (e.getTier() == waveNumber) {
            filtered.push_back(e);
        }
    }

    std::shuffle(filtered.begin(), filtered.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    return filtered.empty() ? std::vector<EnemyCharacter>{} : std::vector<EnemyCharacter>{filtered.front()};
}

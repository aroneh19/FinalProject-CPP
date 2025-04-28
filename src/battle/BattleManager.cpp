#include "battle/BattleManager.h"
#include "ui/UiBattle.h"
#include "utils/JsonLoader.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <characters/Enemy.h>

void BattleManager::startAllWaves(Team &team)
{
    for (int wave = 1; wave <= 5; ++wave)
    {
        runWave(wave, team);
    }

    std::cout << "\nCongratulations! You completed all 5 waves!\n";
    std::cout << "Press Enter to exit the game...\n";
    std::cin.ignore();
    std::cin.get();

    std::exit(0);
}


void BattleManager::runWave(int waveNumber, Team &team)
{
    for (int round = 1; round <= 5; ++round)  // <-- 5 rounds per wave
    {
        std::vector<Enemy> enemies;
        if (round < 5)
        {
            enemies = generateEnemiesForRound(waveNumber, round);
        }
        else
        {
            enemies = generateBossForWave(waveNumber);
        }

        UiBattle ui;
        ui.BattleStart(team, enemies, waveNumber, round);
    }
}


std::vector<Enemy> BattleManager::generateEnemiesForRound(int waveNumber, int roundNumber)
{
    JsonLoader loader;
    std::vector<Enemy> allEnemies = loader.loadEnemys("data/Enemies.json");

    std::vector<Enemy> filtered;

    int numEnemies = 3;
    int maxTier = waveNumber;

    if (waveNumber == 1)
    {
        switch (roundNumber)
        {
        case 1:
            numEnemies = 2;
            break;
        case 2:
            numEnemies = 3;
            break;
        case 3:
            numEnemies = 2;
            maxTier = 2;
            break;
        case 4:
            numEnemies = 4;
            break;
        }
    }
    else if (waveNumber == 2)
    {
        switch (roundNumber)
        {
        case 1:
        case 2:
        case 3:
            numEnemies = 3;
            maxTier = (roundNumber == 3) ? 2 : 1;
            break;
        case 4:
            numEnemies = 4;
            maxTier = 2;
            break;
        }
    }
    else if (waveNumber == 3)
    {
        switch (roundNumber)
        {
        case 1:
        case 2:
            numEnemies = (roundNumber == 1) ? 3 : 4;
            maxTier = 2;
            break;
        case 3:
        case 4:
            numEnemies = (roundNumber == 3) ? 3 : 4;
            maxTier = 3;
            break;
        }
    }

    for (const auto &e : allEnemies)
    {
        if (e.getTier() <= maxTier)
        {
            filtered.push_back(e);
        }
    }

    std::shuffle(filtered.begin(), filtered.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    if (numEnemies > static_cast<int>(filtered.size()))
    {
        numEnemies = static_cast<int>(filtered.size());
    }

    return std::vector<Enemy>(filtered.begin(), filtered.begin() + numEnemies);
}

std::vector<Enemy> BattleManager::generateBossForWave(int waveNumber)
{
    JsonLoader loader;
    std::vector<Enemy> allBosses = loader.loadBosses("data/Bosses.json"); // <<< FIX HERE
    std::vector<Enemy> filtered;

    for (const auto &e : allBosses) {
        if (e.getTier() == waveNumber) {
            filtered.push_back(e);
        }
    }

    std::shuffle(filtered.begin(), filtered.end(), std::default_random_engine(static_cast<unsigned>(std::time(nullptr))));

    return filtered.empty() ? std::vector<Enemy>{} : std::vector<Enemy>{filtered.front()};
}
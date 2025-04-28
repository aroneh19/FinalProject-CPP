#include "characters/Enemy.h"
#include "game/AffinitySystem.h"
#include <limits>

Character *Enemy::chooseTarget(std::vector<Character *> &heroes)
{
    Character *bestTarget = nullptr;
    int bestScore = std::numeric_limits<int>::min();

    for (auto *hero : heroes)
    {
        int score = 0;
        float affinityMultiplier = AffinitySystem::getAffinityMultiplier(this->getAffinity(), hero->getAffinity());
        if (affinityMultiplier > 1.0f)
        {
            score += 10;
        }
        if (hero->getStats().hp < 0.3 * hero->getStats().maxHp)
        {
            score += 5;
        }
        score += (1000 - hero->getStats().hp);

        if (score > bestScore)
        {
            bestScore = score;
            bestTarget = hero;
        }
    }

    if (!bestTarget && !heroes.empty())
    {
        return heroes[0];
    }
    return bestTarget;
}

int Enemy::attack(CharacterBase &target)
{
    int damage = (stats.atk * 3 / 2) - target.getStats().def;
    if (damage < stats.atk / 2)
        damage = stats.atk / 2;

    Stats targetStats = target.getStats();
    targetStats.hp -= damage;
    if (targetStats.hp < 0)
        targetStats.hp = 0;

    target.setStats(targetStats);

    return damage;
}

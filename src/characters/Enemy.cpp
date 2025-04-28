#include "characters/Enemy.h"
#include "utils/AffinityUtils.h"
#include <limits>

Character& Enemy::chooseTarget(std::vector<Character>& heroes) {
    Character* bestTarget = nullptr;
    int bestScore = std::numeric_limits<int>::min(); 

    for (auto& hero : heroes) {
        int score = 0;

        if (AffinityUtils::isWeakAgainst(hero.getAffinity(), this->getAffinity())) {
            score += 10;
        }

        if (hero.getStats().hp < 0.3 * 100) { // Assume average HP, tweak later if needed
            score += 5;
        }

        score += (1000 - hero.getStats().hp);

        if (score > bestScore) {
            bestScore = score;
            bestTarget = &hero;
        }
    }

    if (!bestTarget) {
        return heroes[0];
    }
    return *bestTarget;
}

int Enemy::attack(CharacterBase& target) {
    int damage = stats.atk - target.getStats().def;
    if (damage < stats.atk / 3)
        damage = stats.atk / 3;

    Stats targetStats = target.getStats();
    targetStats.hp -= damage;
    if (targetStats.hp < 0)
        targetStats.hp = 0;

    target.setStats(targetStats);

    return damage;
}

// int Enemy::useSkill(CharacterBase& target) {
//     return attack(target); 
// }

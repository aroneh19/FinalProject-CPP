#include "characters/Character.h"

int Character::attack(CharacterBase &target)
{
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

int Character::useSkill(CharacterBase &target)
{
    // Implement skill usage logic here
    return 0;
}
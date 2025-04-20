#include "characters/Character.h"

int Character::attack(Character &target)
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

int Character::useSkill(Character &target)
{
    // Dont know how the skills will work
}

int Character::useItem()
{
    // Implement item usage logic here
}
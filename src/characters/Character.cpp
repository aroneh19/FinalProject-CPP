#include "characters/Character.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cmath>

int Character::attack(CharacterBase &target)
{
    int damage = stats.atk * stats.atk / target.getStats().def;

    Stats targetStats = target.getStats();
    targetStats.hp -= damage;
    if (targetStats.hp < 0)
        targetStats.hp = 0;

    target.setStats(targetStats);

    return damage;
}

int Character::useSkill(CharacterBase &target)
{
    if (!canUseSkill)
    {
        std::cout << getName() << " cannot use skill yet!\n";
        return 0;
    }

    std::cout << getName() << " uses skill: " << skill.name << "!\n";
    std::cout << "  Description: " << skill.description << "\n";

    int damage = 0;
    int heal = 0;
    Stats targetStats = target.getStats();
    int maxHp = this->stats.hp;

    if (skill.name == "Double Shot")
    {
        int hits = 2;
        std::cout << "  Hitting " << hits << " times!\n";
        for (int i = 0; i < hits; ++i)
        {
            int singleHit = std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
            targetStats.hp -= singleHit;
            damage += singleHit;
            std::cout << "  Hit " << (i + 1) << " deals " << singleHit << " damage.\n";
        }
    }
    else if (skill.name == "Shadow Step")
    {
        int critChance = this->stats.lck + 30;
        bool isCrit = (rand() % 100) < critChance;
        int critMultiplier = isCrit ? 2 : 1;
        damage = critMultiplier * std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
        if (isCrit)
        {
            std::cout << "  Critical Hit!\n";
        }
        targetStats.hp -= damage;
    }
    else if (skill.name == "Battle Hymn")
    {
        std::cout << "  Boosting team SPD for 2 turns! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Rage Strike")
    {
        double hpPercent = static_cast<double>(this->stats.hp) / maxHp;
        double damageMultiplier = 1.0 + (1.0 - hpPercent) * 1.5;
        damage = static_cast<int>(damageMultiplier * std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def)));
        std::cout << "  Damage multiplied by " << damageMultiplier << " due to low HP!\n";
        targetStats.hp -= damage;
    }
    else if (skill.name == "Soulfire Blade")
    {
        damage = this->stats.atk + 10;
        std::cout << "  Dealing " << damage << " true damage, ignoring DEF!\n";
        targetStats.hp -= damage;
    }
    else if (skill.name == "Rejuvenation")
    {
        std::cout << "  Applying Heal over Time to all allies! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Frozen Guard")
    {
        std::cout << "  Reducing incoming critical hit chance! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Arena Smash")
    {
        damage = std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
        targetStats.hp -= damage;
        std::cout << "  Applying minor bleed! (Needs implementation)\n";
    }
    else if (skill.name == "Divine Light")
    {
        heal = this->stats.atk * 3 + 20;
        std::cout << "  Restoring " << heal << " HP to " << target.getName() << "!\n";
        targetStats.hp += heal;
        damage = 0;
    }
    else if (skill.name == "Frostbind")
    {
        damage = std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
        targetStats.hp -= damage;
        int freezeChance = 30 + this->stats.lck;
        if ((rand() % 100) < freezeChance)
        {
            std::cout << "  Target is Frozen! (Needs implementation)\n";
        }
        else
        {
            std::cout << "  Freeze attempt failed.\n";
        }
    }
    else if (skill.name == "Stone Slam")
    {
        std::cout << "  Hitting all enemies with an AoE slam! (Applying to single target)\n";
        damage = static_cast<int>(this->stats.atk * 1.2);
        targetStats.hp -= damage;
    }
    else if (skill.name == "Shield Bash")
    {
        damage = std::max(1, (this->stats.atk / 2 + this->stats.def) * this->stats.atk / std::max(1, targetStats.def));
        targetStats.hp -= damage;
        int stunChance = 20 + this->stats.lck;
        if ((rand() % 100) < stunChance)
        {
            std::cout << "  Target is Stunned! (Needs implementation)\n";
        }
        else
        {
            std::cout << "  Stun attempt failed.\n";
        }
    }
    else if (skill.name == "Arcane Storm")
    {
        std::cout << "  Hitting all enemies with an AoE blast! (Applying to single target)\n";
        damage = static_cast<int>(this->stats.atk * 1.5);
        damage = std::max(1, damage / std::max(1, targetStats.def / 2));
        targetStats.hp -= damage;
    }
    else if (skill.name == "Chi Barrier")
    {
        std::cout << "  Boosting team DEF! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Divine Shield")
    {
        std::cout << "  Reducing incoming damage for 2 turns! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Inferno")
    {
        damage = std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
        targetStats.hp -= damage;
        std::cout << "  Target is Burning for 3 turns! (Needs implementation)\n";
    }
    else if (skill.name == "Spell Reflect")
    {
        std::cout << "  Reflecting 25% of incoming damage for 2 turns! (Needs implementation)\n";
        damage = 0;
    }
    else if (skill.name == "Headshot")
    {
        int critChance = this->stats.lck + 40;
        bool isCrit = (rand() % 100) < critChance;
        int critMultiplier = isCrit ? 2.5 : 1;
        damage = static_cast<int>(critMultiplier * std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def)));

        if (isCrit)
        {
            std::cout << "  Critical Headshot!\n";
            targetStats.hp -= damage;
        }
        else
        {
            targetStats.hp -= damage;
        }
    }
    else if (skill.name == "Heaven's Wrath")
    {
        std::cout << "  Hitting all frontline enemies! (Applying to single target)\n";
        damage = static_cast<int>(this->stats.atk * 1.3);
        damage = std::max(1, damage * damage / std::max(1, targetStats.def));
        targetStats.hp -= damage;
    }
    else if (skill.name == "Curse of Weakness")
    {
        std::cout << "  Debuffing target ATK! (Needs implementation)\n";
        damage = this->stats.atk / 2;
        targetStats.hp -= damage;
    }
    else
    {
        std::cout << "  Using a basic skill attack!\n";
        damage = std::max(1, this->stats.atk * this->stats.atk / std::max(1, targetStats.def));
        targetStats.hp -= damage;
    }

    if (targetStats.hp < 0)
        targetStats.hp = 0;

    target.setStats(targetStats);

    resetSkill();

    if (heal > 0)
    {
        return -heal;
    }
    else
    {
        return damage;
    }
}

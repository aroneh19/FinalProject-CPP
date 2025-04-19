#pragma once
#include <vector>
#include <characters/Character.h>
#include <items/Item.h>

class Team
{
public:
    void addCharacter(Character character);
    void addItem(Item item);
    const std::vector<Character> &getCharacters() const;
    const std::vector<Item> &getItems() const;

private:
    std::vector<Character> team;
    std::vector<Item> items;
};
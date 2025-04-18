#pragma once
#include <vector>
#include <characters/Character.h>
#include <items/Item.h>


class Team {
    public:
        void addCharacter(Character character);
        void addItem(Item item);
    private:
        std::vector<Character> characters;
        std::vector<Item> items;
};
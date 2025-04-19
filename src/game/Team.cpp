#include "game/Team.h"

void Team::addCharacter(Character character) {
    team.push_back(character);
}

void Team::addItem(Item item) {
    items.push_back(item);
}

const std::vector<Character>& Team::getCharacters() const {
    return team;
}

const std::vector<Item>& Team::getItems() const {
    return items;
}

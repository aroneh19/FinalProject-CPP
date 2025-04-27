#include "game/Team.h"

void Team::addCharacter(Character character) {
    team.push_back(character);
}

const std::vector<Character>& Team::getCharacters() const {
    return team;
}

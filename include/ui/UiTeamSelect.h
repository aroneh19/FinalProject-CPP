#pragma once

#include <string>
#include <vector>
#include "characters/Character.h"

class UiTeamSelect
{
public:
    void Start();
    void displayTeams(const std::string &role, std::vector<Character> &team);    
    void selectTeam(std::vector<Character> &team);
};

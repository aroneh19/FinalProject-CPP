#pragma once

#include <string>
#include <vector>
#include "characters/Character.h"
#include "game/Team.h"

class UiTeamSelect
{
public:
    void Start();
    void displayTeams(const std::string &role, Team &team);    
    void selectTeam(Team &team);
};

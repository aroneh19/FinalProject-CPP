#pragma once
#include <vector>
#include <string>

class UiMenu
{
public:
    void Start();

private:
    void ShowMainMenu();
    void HandleInput(int choice);

    void StartNewGame();
    void LoadGame();
    void ViewCharacters();
    void HowToPlay();
    void ExitGame();
};
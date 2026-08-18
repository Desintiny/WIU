#pragma once
class Game
{
    bool gameRunning;
    char mapGrid[12][12];

public: 
    Game();
    ~Game();

    void Start();
    void MainMenu();
    void ClassSelection();
    void DisplayGame();
};


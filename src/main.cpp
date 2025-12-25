#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
    auto& game = Game::GetInstance();
    game.Init("GhostEscape", 1280, 720);
    
    game.Run();
    game.Clean();
    return 0;
}
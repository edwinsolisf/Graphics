//
//  main.cpp
//  Graphics
//
//  Created by Edwin Solis on 10/5/20.
//

#include <iostream>
#include "Application.h"

int main(int argc, const char * argv[])
{
    Application* game = new Application();
    
    game->Setup();
    
    while(game->IsRunning())
    {
        game->Process();
        game->Render();
    }
    
    game->Close();
    delete game;
    return 0;
}

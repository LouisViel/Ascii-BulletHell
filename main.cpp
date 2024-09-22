#include "./include/Game.h"
#include <iostream>

int main()
{
    // Game Loop
    Game game{};
    while (GameSettings::running) {

        // Perform Frame Processing
        game.update();
        game.checkResize();
        game.render();
        game.postRender();

        // Sleep before next frame
        Sleep(15);
    }

    // Wait for user input before close terminal
    system("pause");
    system("pause");

    // End Program
    return 0;
}
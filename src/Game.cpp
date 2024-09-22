#include "../include/Game.h"
#include "../include/Random.h"
#include "../include/GameLoader.h"

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Initialize Game Settings
unsigned int GameSettings::currentScreenWidth = GameSettings::SCREEN_WIDTH;
unsigned int GameSettings::currentScreenHeight = GameSettings::SCREEN_HEIGHT;
bool GameSettings::running = true;

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

Game::Game()
{
    // Initialize Random
    Random::init();

    // Init Console Render Settings
    csbiInfo = new CONSOLE_SCREEN_BUFFER_INFO();
    hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    Game::checkResize();

    // Allocate Render Buffer + Render Data Buffer
    renderBuffer = new CHAR_INFO[GameSettings::SCREEN_HEIGHT * GameSettings::SCREEN_WIDTH];
    renderDataBuffer = new RenderData*[GameSettings::SCREEN_HEIGHT];
    for (unsigned int iRow{ 0 }; iRow < GameSettings::SCREEN_HEIGHT; ++iRow) {
        renderDataBuffer[iRow] = new RenderData[GameSettings::SCREEN_WIDTH];
    }

    // Allocate Managers
    clock = new Clock();
    inputHandler = new InputHandler();
    charInfoHandler = new CharInfoHandler();
    gameObjectManager = new GameObjectManager();
    GameLoader::Load(gameObjectManager);
};

Game::~Game()
{
    // Release Render Data Buffer + Render Buffer
    for (unsigned int iRow{ 0 }; iRow < GameSettings::SCREEN_HEIGHT; ++iRow) {
        delete renderDataBuffer[iRow];
    }
    delete[] renderDataBuffer;
    delete renderBuffer;

    // Release Managers
    delete gameObjectManager;
    delete charInfoHandler;
    delete inputHandler;
    delete clock;

    // Release Constants
    hOutput = nullptr;
    delete csbiInfo;
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Update Game
void Game::update()
{
    clock->updateDeltaTime();
    inputHandler->updateKeyboardInput();
    gameObjectManager->updateObjects();
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Allow Managing Resize of Console Size
void Game::checkResize()
{
    if (GetConsoleScreenBufferInfo(hOutput, csbiInfo)) {
        const COORD& dwSize = csbiInfo->dwSize;
        if (dwSize.X != dwBufferSize.X || dwSize.Y != dwBufferSize.Y) {
            GameSettings::currentScreenWidth = dwSize.X;
            GameSettings::currentScreenHeight = dwSize.Y;
            SetConsoleScreenBufferSize(hOutput, dwBufferSize);
            system("cls");

            // TODO : Setup le setup d'auto centrage/resize du terminal selon sa size
        }
    }
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

// Render Game to Console
void Game::render()
{
    // Clean Z-Render-Buffer
    RenderData defaultRenderData = *charInfoHandler->getDefaultRenderData();
    for (unsigned int i{ 0 }; i < GameSettings::SCREEN_HEIGHT; ++i) {
        RenderData* const target = renderDataBuffer[i];
        std::fill(target, target + GameSettings::SCREEN_WIDTH, defaultRenderData);
    }

    // Render GameObjects into Z-Render-Buffer
    gameObjectManager->renderObjects(renderDataBuffer, GameSettings::SCREEN_WIDTH, GameSettings::SCREEN_HEIGHT);

    // Copy Z-Render-Buffer into Render-Buffer 
    for (unsigned int i{ 0 }, k{ 0 }; i < GameSettings::SCREEN_HEIGHT; k = ++i * GameSettings::SCREEN_WIDTH) {
        for (unsigned int j{ 0 }; j < GameSettings::SCREEN_WIDTH; ++j) {
            renderBuffer[k + j] = *renderDataBuffer[i][j].charInfo;
        }
    }

    // Flush Render Buffer into Console
    WriteConsoleOutput(hOutput, (CHAR_INFO*)renderBuffer, dwBufferSize, dwBufferCoord, &rcRegion);
}

//////////////////////////////////
//////////////////////////////////
//////////////////////////////////

void Game::postRender()
{
    gameObjectManager->postRenderObjects(
        renderDataBuffer,
        GameSettings::SCREEN_WIDTH,
        GameSettings::SCREEN_HEIGHT
    );
}
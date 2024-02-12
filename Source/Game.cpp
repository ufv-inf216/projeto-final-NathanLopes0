
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "Random.h"
#include "Game.h"
#include "Actors/Actor.h"
#include "Actors/Player.h"
#include "Actors/LimiterMenu.h"
#include "Actors/Teachers/Teacher.h"
#include "Scenes/MainMenu.h"
#include "Scenes/SelectPlayers.h"
#include "Scenes/StageSelect.h"
#include "Scenes/Battle.h"
#include "Scenes/Win.h"
#include "Scenes/Lose.h"
#include "Components/DrawComponents/DrawComponent.h"
#include "Components/DrawComponents/DrawTextComponent.h"



Game::Game(int windowWidth, int windowHeight)
        :mWindow(nullptr)
        ,mRenderer(nullptr)
        ,mTicksCount(0)
        ,mIsRunning(true)
        ,mUpdatingActors(false)
        ,mWindowWidth(windowWidth)
        ,mWindowHeight(windowHeight)
        ,mPlayer1(nullptr)
        ,mPlayer2(nullptr)
        ,mChangeScene(false)
        ,mGameWindowWidth(windowWidth / 2 - 50)
        ,mGameWindowHeight(windowHeight - 50)
        ,mGameState(GameScene::MainMenu)
        ,currStage(0)
{

}

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("DPI Bullet Hell", 0, 0, mWindowWidth, mWindowHeight, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    SDL_SetWindowPosition(mWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("Failed to initialize SDL_ttf");
        return false;
    }

    mAudio = new AudioSystem();

    Random::Init();

    mTicksCount = SDL_GetTicks();

    // Init all game actors
    InitializeActors();

    return true;
}

void Game::InitializeActors()
{
    switch (mGameState) {
        case GameScene::MainMenu: {
            mScene = new MainMenu(this);
            mScene->Load();
            break;
        }
        case GameScene::SelectPlayers: {
            mScene = new SelectPlayers(this);
            mScene->Load();
            break;
        }
        case GameScene::StageSelect: {
            mScene = new StageSelect(this);
            mScene->Load();
            break;
        }
        case GameScene::Battle: {
            mScene = new Battle(this);
            mScene->Load();
            break;
        }
        case GameScene::Win: {
            mScene = new Win(this);
            mScene->Load();
            break;
        }
        case GameScene::Lose :{
            mScene = new Lose(this);
            mScene->Load();
            break;
        }
        default:
            break;
    }

    for (int i = 0; i < 10; i++)
    {
        mNotas[Game::Materia(i)] = 40;
    }
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Quit();
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(nullptr);

    for (auto actor : mActors)
    {
        actor->ProcessInput(state);
    }

    if (mScene)
    {
        mScene->ProcessInput(state);
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    mTicksCount = SDL_GetTicks();

    if(!mChangeScene) {
        // Update all actors and pending actors
        UpdateActors(deltaTime);

        // Update camera position
        UpdateCamera();
    }
    else
    {
        UnloadActors();
        InitializeActors();
        mChangeScene = false;
    }
}

void Game::UpdateCamera()
{

}

void Game::UpdateActors(float deltaTime)
{
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == ActorState::Destroy)
        {
            deadActors.emplace_back(actor);
        }
    }

    for (auto actor : deadActors)
    {
        delete actor;
    }
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddDrawable(class DrawComponent *drawable)
{
    mDrawables.emplace_back(drawable);

    std::sort(mDrawables.begin(), mDrawables.end(),[](DrawComponent* a, DrawComponent* b) {
        return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveDrawable(class DrawComponent *drawable)
{
    auto iter = std::find(mDrawables.begin(), mDrawables.end(), drawable);
    mDrawables.erase(iter);
}

void Game::AddCollider(class CircleColliderComponent* collider)
{
    mColliders.emplace_back(collider);
}

void Game::RemoveCollider(CircleColliderComponent* collider)
{
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    mColliders.erase(iter);
}

void Game::GenerateOutput()
{
    // Set draw color to black
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    // Clear back buffer
    SDL_RenderClear(mRenderer);

    for (auto drawable : mDrawables)
    {
        if (drawable->IsVisible())
        {
            drawable->Draw(mRenderer);
        }
    }

    // Swap front buffer and back buffer
    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Game::LoadTexture(const std::string& texturePath) {

    auto loadedIMG = IMG_Load(texturePath.c_str());
    if (loadedIMG == nullptr) {
        return nullptr;
    }


    auto textureFromSur = SDL_CreateTextureFromSurface(mRenderer, loadedIMG);
    SDL_FreeSurface(loadedIMG);
    if (!textureFromSur)
    {
        return nullptr;
    }


    return textureFromSur;
}

void Game::Shutdown()
{
    UnloadActors();

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::UnloadActors()
{
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    delete mScene;
    mScene = nullptr;
}

void Game::RemoveTask(struct Task *task) {

    auto iter = std::find(mTasks.begin(), mTasks.end(), task);

    if (iter != mTasks.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mTasks.end() - 1);
        mTasks.pop_back();
    }

}

void Game::SetNota(const float newNota, Game::Materia materia) {

    mNotas[materia] = Math::Min(newNota, 100.0f);

}

void Game::SetScene(GameScene gameState)
{
    mAudio->StopAllSounds();
    mGameState = gameState;
    mChangeScene = true;
}

Teacher* Game::GetActiveTeacher() {
    if(mGameState == GameScene::Battle)
    {
        return mScene->GetActiveTeacher();
    }
    else return nullptr;
}

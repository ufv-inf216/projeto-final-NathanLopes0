//
// Created by User on 14/12/2023.
//

#include "MainMenu.h"
#include "../Game.h"
#include "../Font.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"

MainMenu::MainMenu(Game *game) : Scene(game), mMainMenuFont(nullptr) {
    mMainMenuFont = new Font();
    mMainMenuFont->Load("../Assets/Fonts/Zelda.ttf");

}

void MainMenu::Load() {

    auto background = new Actor(this);
    new DrawSpriteWColorEffect(background, "../Assets/DPIUfV.png", 1600, 1188, 99);
    background->SetPosition(Vector2(GetGame()->GetWindowWidth() / 2, GetGame()->GetWindowHeight() / 2));
    background->GetComponent<DrawSpriteWColorEffect>()->SetColorEffect(0,0,0,180);

    auto title = new Actor(this);
    new DrawSpriteComponent(title, "../Assets/DPIBHTitleMainMenu.png", 1200, 800);
    title->SetPosition(Vector2(GetGame()->GetWindowWidth() / 2, GetGame()->GetWindowHeight() / 2));

    auto pressSpace = new Actor(this);
    pressSpace->SetPosition(Vector2(600, 700));
    new DrawTextComponent(pressSpace, "Jogar", mMainMenuFont, 500, 64, 72);
}

void MainMenu::ProcessInput(const Uint8 *keyState) {

    keyState = SDL_GetKeyboardState(nullptr);

    if(keyState[SDL_SCANCODE_SPACE])
    {
        mGame->SetScene(Game::GameScene::StageSelect);
    }
}

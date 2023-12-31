//
// Created by User on 15/12/2023.
//

#include "Win.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Font.h"

Win::Win(Game* game) : Scene(game)
{
    mFont = new Font();
    mFont->Load("../Assets/Fonts/Zelda.ttf");
}

void Win::Load()
{
    auto message = new Actor(this);
    message->SetPosition(Vector2(mGame->GetWindowWidth() / 2, mGame->GetWindowHeight() / 2));
    new DrawTextComponent(message, "Voce Formou! Parabens!", mFont, 320, 128, 64);
}

const Vector2& Win::GetCameraPos() {
    return Vector2::Zero;
}

void Win::ProcessInput(const Uint8 *keyState) {

}
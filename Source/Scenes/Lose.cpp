//
// Created by User on 15/12/2023.
//

#include "Lose.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Font.h"

Lose::Lose(Game *game) : Scene(game) {
    mFont = new Font();
    mFont->Load("../Assets/Fonts/Zelda.ttf");
}

void Lose::Load()
{
    auto message = new Actor(this);
    message->SetPosition(Vector2(mGame->GetWindowWidth() / 2, mGame->GetWindowHeight() / 2));
    new DrawTextComponent(message, "Voce Tirou 0! Poxa!", mFont, 320, 128, 64);
}


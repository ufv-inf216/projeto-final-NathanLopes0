//
// Created by User on 08/12/2023.
//

#include "LimiterMenu.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Game.h"

LimiterMenu::LimiterMenu(Game* game, std::string& spritePath, int width, int height) : Actor(game) {

    mDrawComponent = new DrawSpriteComponent(this, spritePath, width, height, 101);
    SetPosition(Vector2(GetGame()->GetWindowWidth() / 2, GetGame()->GetWindowHeight() / 2));

}

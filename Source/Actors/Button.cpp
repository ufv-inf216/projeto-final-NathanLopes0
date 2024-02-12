//
// Created by User on 11/02/2024.
//

#include "Button.h"
#include "../Font.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Game.h"
#include "../Scenes/Scene.h"

Button::Button(Scene* scene, std::string &spritepath, std::string &subjectCode)
        :Actor(scene)
        ,width(128)
        ,height(64)
        ,selected(false)
{
    mFont = new Font();
    mFont->Load("../Assets/Fonts/Zelda.ttf");

    mDrawComponent = new DrawSpriteWColorEffect(this, spritepath
                                                ,width, height);
    mDrawTextComponent = new DrawTextComponent(this, subjectCode, mFont, 64, 24, 16, 110);

}

void Button::OnUpdate(float deltaTime) {
    if(selected)
        mDrawComponent->SetColorEffect(100, 0, 20, 180);
    else
        mDrawComponent->StopColorEffect();
}
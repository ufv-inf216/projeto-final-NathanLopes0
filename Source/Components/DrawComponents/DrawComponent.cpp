//
// Created by Lucas N. Ferreira on 03/08/23.
//

#include "DrawComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"
#include "../../Scenes/Scene.h"

DrawComponent::DrawComponent(class Actor* owner, int drawOrder)
    :Component(owner)
    ,mDrawOrder(drawOrder)
    ,mIsVisible(true)
{
    mOwner->GetScene()->GetGame()->AddDrawable(this);
}

DrawComponent::~DrawComponent()
{
    mOwner->GetScene()->GetGame()->RemoveDrawable(this);
}


void DrawComponent::Draw(SDL_Renderer *renderer)
{

}
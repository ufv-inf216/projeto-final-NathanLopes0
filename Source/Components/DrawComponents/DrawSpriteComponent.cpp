

#include "DrawSpriteComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"

DrawSpriteComponent::DrawSpriteComponent(class Actor* owner, const std::string &texturePath, const int width, const int height, const int drawOrder)
        :DrawComponent(owner, drawOrder)
        ,mWidth(width)
        ,mHeight(height)
{

    mSpriteSheetSurface = GetGame()->LoadTexture(texturePath);


}

void DrawSpriteComponent::Draw(SDL_Renderer *renderer)
{


    //coloquei -mWidth/2 e -mHeight/2 para centralizar o desenho com o centro do círculo do ColliderComponent

    auto srcrect = new SDL_Rect{0, 0, mWidth, mHeight};
    int posx = GetOwner()->GetPosition().x - GetOwner()->GetGame()->GetCameraPos().x - mWidth/2;
    int posy = GetOwner()->GetPosition().y - GetOwner()->GetGame()->GetCameraPos().y - mHeight/2;
    auto dstrect = new SDL_Rect {posx, posy, mWidth, mHeight};

    auto flipflag = SDL_RendererFlip::SDL_FLIP_NONE;

    if(GetOwner()->GetRotation() == Math::Pi)
        flipflag = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, srcrect, dstrect,
                     NULL, nullptr, flipflag);


}
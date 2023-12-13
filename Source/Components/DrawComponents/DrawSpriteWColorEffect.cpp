//
// Created by User on 13/12/2023.
//

#include "DrawSpriteWColorEffect.h"
#include "../../Actors/Actor.h"


DrawSpriteWColorEffect::DrawSpriteWColorEffect(Actor *owner, const std::string &texturePath, int width, int height,
                                               int drawOrder, int r_, int g_, int b_, int a_) //chamando o construtor do DrawSprite, e desativando o efeito inicialmente
                                               : DrawSpriteComponent(owner, texturePath, width, height, drawOrder), active(false),
                                               r(r_),
                                               g(g_),
                                               b(b_),
                                               a(a_)

{

}

void DrawSpriteWColorEffect::Draw(SDL_Renderer *renderer) {

    DrawSpriteComponent::Draw(renderer);
    if (active) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MUL);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        int Px = (int)mOwner->GetPosition().x - mWidth / 2;
        int Py = (int)mOwner->GetPosition().y - mHeight / 2;
        SDL_Rect rectEffect = {Px, Py, mWidth, mHeight};
        SDL_RenderFillRect(renderer, &rectEffect);
    }
}

void DrawSpriteWColorEffect::SetColorEffect(int r_, int g_, int b_, int a_) {
    r = r_;
    g = g_;
    b = b_;
    a = a_;
    active = true;
}



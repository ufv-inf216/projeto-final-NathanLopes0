//
// Created by User on 13/12/2023.
//

#ifndef DPIBULLETHELL_DRAWSPRITEWCOLOREFFECT_H
#define DPIBULLETHELL_DRAWSPRITEWCOLOREFFECT_H

#include "DrawSpriteComponent.h"

class DrawSpriteWColorEffect : public DrawSpriteComponent {

public:

    DrawSpriteWColorEffect(class Actor* owner, const std::string &texturePath, int width = 0, int height = 0, int drawOrder = 100, int r = 0, int g = 0, int b = 0, float a = 0.f);
    void Draw(SDL_Renderer* renderer) override;
    void SetColorEffect(int r, int g, int b, float a);
    void StopColorEffect() { active = false; }

private:
    int r, g, b;
    float a;
    bool active;
};


#endif //DPIBULLETHELL_DRAWSPRITEWCOLOREFFECT_H

//
// Created by User on 08/12/2023.
//

#ifndef DPIBULLETHELL_LIMITERMENU_H
#define DPIBULLETHELL_LIMITERMENU_H


#include <string>
#include "Actor.h"

class LimiterMenu : public Actor {
public:
    LimiterMenu(class Scene* scene, std::string& spritePath, int width, int height);
    void SetNotaAtual(float notaAtual);
    void SetStateTimeAtual(float stateTimer);
    void OnUpdate(float deltaTime) override;
    void writeNew(std::string & newString, int offSetY_);
    void changeText(int index, std::string& newText);
private:

    float offSetX, offSetY;
    int mWidth, mHeight;

    class DrawAnimatedComponent * mDrawComponent;
    class Font* mFont;
    std::vector<class DrawTextComponent *> mDrawTextComponent;
    std::vector<class Actor*> mExtraPoints;
    std::vector <class DrawSpriteComponent*> mDrawExtraPoints;


    void SetPontosPlayer(int pontos);

    void DrawApprovedSign();

    void ManageAnimations();

    void DrawPoints(int currPontos);
};


#endif //DPIBULLETHELL_LIMITERMENU_H

//
// Created by User on 08/12/2023.
//

#ifndef DPIBULLETHELL_LIMITERMENU_H
#define DPIBULLETHELL_LIMITERMENU_H


#include <string>
#include "Actor.h"

class LimiterMenu : public Actor {
public:
    LimiterMenu(Game* game, std::string& spritePath, int width, int height);
    void SetNotaAtual(float notaAtual);
    void SetStateTimeAtual(float stateTimer);
    void OnUpdate(float deltaTime) override;
    void writeNew(std::string & newString, int offSetY_);
    void changeText(int index, std::string& newText);
private:

    float offSetX, offSetY;
    int mWidth, mHeight;

    class DrawSpriteWColorEffect * mDrawComponent;
    class Font* mFont;
    std::vector<class DrawTextComponent *> mDrawTextComponent;


    void SetPontosPlayer(int pontos);

    void DrawApprovedSign();
};


#endif //DPIBULLETHELL_LIMITERMENU_H

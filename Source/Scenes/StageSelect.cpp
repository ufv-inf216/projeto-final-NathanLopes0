//
// Created by User on 14/12/2023.
//

#include "StageSelect.h"
#include "../Font.h"

StageSelect::StageSelect(Game *game) : Scene(game), mStageSelectFont(nullptr) {

    mStageSelectFont = new Font();
    mStageSelectFont->Load("../Assets/Fonts/Zelda.ttf");

}

void StageSelect::Load()
{

}

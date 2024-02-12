//
// Created by User on 14/12/2023.
//

#include "StageSelect.h"
#include "../Font.h"
#include "../Game.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Actors/Button.h"

StageSelect::StageSelect(Game *game) : Scene(game)
    ,mStageSelectFont(nullptr)
    ,mButtonSelected(0)
    ,numMat(10)
    ,mTimer(10)
{

    mStageSelectFont = new Font();
    mStageSelectFont->Load("../Assets/Fonts/Zelda.ttf");
    button.reserve(10);

}

void StageSelect::Load()
{
    float espacamentoX = 162;
    float espacamentoY = 140;
    float buttonWidth = 128;
    float buttonHeight = 64;

    float widthBorder = (float)mGame->GetWindowWidth() / 12; //borda de 100px
    float heightBorder = (float)mGame->GetWindowHeight() / 12; // borda de 66px

    //criando botoes
    std::string buttonSpritePath = "../Assets/Icons/DPIBHSelectSubjectButtonPrototype.png";
    std::string subjectCode = "";
    for (int j = 0; j < 4; j++)
    {
        switch(j)
        {
            case 0:
            {
                subjectCode = "INF 213";
                auto stage = new Button(this, buttonSpritePath, subjectCode);
                stage->SetPosition(Vector2(widthBorder + buttonWidth/2, GetGame()->GetWindowHeight()/2));
                button.push_back(stage);
                break;
            }
            case 1:
            {
                float area2x = widthBorder + 1.20f * (espacamentoX + buttonWidth);
                for (int i = 0; i < 4; i++)
                {
                    switch (i) {
                        case 0:
                            subjectCode = "INF 250";
                            break;
                        case 1:
                            subjectCode = "INF 220";
                            break;
                        case 2:
                            subjectCode = "INF 330";
                            break;
                        case 3:
                            subjectCode = "INF 332";
                            break;
                        default:
                            subjectCode = "ERROR";
                            break;
                    }
                    float area2y = heightBorder + buttonHeight/2 + i * (espacamentoY + buttonHeight);
                    auto stage = new Button(this, buttonSpritePath, subjectCode);
                    stage->SetPosition(Vector2(area2x, area2y));
                    button.push_back(stage);
                }
                break;
            }

            case 2:
            {
                float area2x = widthBorder + 2.25f * (espacamentoX + buttonWidth);
                for (int i = 0; i < 4; i++)
                {
                    switch (i) {
                        case 0: {
                            subjectCode = "INF 420";
                            break;
                        }
                        case 1: {
                            subjectCode = "BIO INF";
                            break;
                        }
                        case 2: {
                            subjectCode = "INF 394";
                            break;
                        }
                        case 3: {
                            subjectCode = "VIS CCP";
                            break;
                        }
                        default:
                            subjectCode = "ERROR";
                            break;
                    }
                    float area2y = heightBorder + buttonHeight/2 + i * (espacamentoY + buttonHeight);
                    auto stage = new Button(this, buttonSpritePath, subjectCode);
                    stage->SetPosition(Vector2(area2x, area2y));
                    button.push_back(stage);
                }
                break;
            }
            case 3:
            {
                subjectCode = "TCC";
                auto stage = new Button(this, buttonSpritePath, subjectCode);
                stage->SetPosition(Vector2(GetGame()->GetWindowWidth() - widthBorder - buttonWidth/2, GetGame()->GetWindowHeight()/2));
                button.push_back(stage);
                break;
            }
            default:
                break;
        }
    }
    button[0]->changeSelected();
}

void StageSelect::ProcessInput(const Uint8 *keyState) {

    keyState = SDL_GetKeyboardState(nullptr);

    //selecionar botão
    if (mTimer < 10) mTimer++;
    else
    {
        if (keyState[SDL_SCANCODE_LEFT]) {
            mButtonSelected--;
            mTimer = 0;
        } else if (keyState[SDL_SCANCODE_RIGHT]) {
            mButtonSelected++;
            mTimer = 0;
        }

        if (mButtonSelected < 0)
            mButtonSelected = numMat - 1;
        if (mButtonSelected >= numMat)
            mButtonSelected = 0;

        for (int i = 0; i < numMat; i++) {
            auto currButton = mButtonSelected - 1 + i;
            if (currButton < 0) currButton = numMat - 1;
            else if (currButton >= numMat) currButton = 0;

            if (button[currButton]->isSelected())
                button[currButton]->changeSelected();
        }

        button[mButtonSelected]->changeSelected();
    }

    //escolher Fase
   if (keyState[SDL_SCANCODE_RETURN])
   {
       mGame->SetStage(mButtonSelected);
       mGame->SetScene(Game::GameScene::Battle);
   }


}

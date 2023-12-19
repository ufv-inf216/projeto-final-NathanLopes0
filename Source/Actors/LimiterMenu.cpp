//
// Created by User on 08/12/2023.
//

#include "LimiterMenu.h"
#include "../Font.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../Components/DrawComponents/DrawTextComponent.h"
#include "../Components/DrawComponents/DrawAnimatedComponent.h"
#include "../Game.h"
#include "../Actors/Teachers/TStates/TState.h"
#include "../Scenes/Scene.h"

LimiterMenu::LimiterMenu(Scene* scene, std::string& spritePath, int width, int height)
    :Actor(scene)
    ,offSetX(256)
    ,offSetY(48)
    ,mWidth(width)
    ,mHeight(height)
    {

    mDrawComponent = new DrawAnimatedComponent(this, "../Assets/Background2.png", "../Assets/Background2.json", 101);
    mDrawComponent->AddAnimation("approved", {0});
    mDrawComponent->AddAnimation("normal", {1});
    mDrawComponent->AddAnimation("reproved", {2});

    mDrawComponent->SetAnimation("normal");
    mDrawComponent->SetAnimFPS(10.0f);

    SetPosition(Vector2(GetScene()->GetGame()->GetWindowWidth() / 2, GetScene()->GetGame()->GetWindowHeight() / 2));

    mFont = new Font();
    mFont->Load("../Assets/Fonts/Zelda.ttf");

    Vector2 textPosition = Vector2((float) mScene->GetGame()->GetGameWindowWidth() + offSetX,
                                   (float) mScene->GetGame()->GetGameWindowHeight() / 8);
    Vector2 offSetYVec = Vector2(0, offSetY);

    //Nota do Aluno
    auto mostraNota = new Actor(mScene);
    mostraNota->SetPosition(textPosition + offSetYVec * 0);
    auto tMostraNota = new DrawTextComponent(mostraNota, "00", mFont, 256, 32, 32, 102);
    mDrawTextComponent.push_back(tMostraNota);

    //Timer do Estado
    auto mostraTimer = new Actor(mScene);
    mostraTimer->SetPosition(textPosition + offSetYVec * 4 + Vector2(128, 0));
    auto tMostraTimer = new DrawTextComponent(mostraTimer, "00", mFont, 512, 64, 32, 102);
    mDrawTextComponent.push_back(tMostraTimer);

    //Numero de Pontos Extras
    auto mostraPontos = new Actor(mScene);
    mostraPontos->SetPosition(textPosition + offSetYVec * 1 + Vector2(64, 0));
    auto tMostraPontos = new DrawTextComponent(mostraPontos, "00", mFont, 384, 32, 32, 102);
    mDrawTextComponent.push_back(tMostraPontos);

    //Desenho de pontos extras
    for (int i = 0; i < 3; i++) {
        auto mostraPontosDraw = new Actor(mScene);
        mostraPontosDraw->SetPosition(Vector2::Zero);
        mExtraPoints.push_back(mostraPontosDraw);
        auto tMostraPontosDraw = new DrawSpriteComponent(mostraPontosDraw,
                                                         "../Assets/Icons/DPIBHPowerIcon2.png",
                                                         16, 16,
                                                         100);
        mDrawExtraPoints.push_back(tMostraPontosDraw);
    }

}


void LimiterMenu::SetNotaAtual(float notaAtual) {

    float currNote = roundf(notaAtual);
    int currNoteInt = (int)currNote;
    std::string NotaAtualStr = std::to_string(currNoteInt);
    if(NotaAtualStr.size() == 1)
        NotaAtualStr = "0" + NotaAtualStr;
    NotaAtualStr = "Nota: " + NotaAtualStr + " de 100";
    mDrawTextComponent[0]->SetText(NotaAtualStr);
}

void LimiterMenu::SetStateTimeAtual(float stateTimer) {

    int currTimer = 18 - (int)stateTimer;

    std::string StateTimeAtual = std::to_string(currTimer);
    if(StateTimeAtual.size() == 1)
        StateTimeAtual = "0" + StateTimeAtual;
    StateTimeAtual = StateTimeAtual + " Segundos restantes para\na prova acabar";
    mDrawTextComponent[1]->SetText(StateTimeAtual);
}

void LimiterMenu::SetPontosPlayer(int pontos)
{
    std::string PontosAtual = std::to_string(pontos) + " Pontos Extras";
    mDrawTextComponent[2]->SetText(PontosAtual);
}

void LimiterMenu::OnUpdate(float deltaTime) {

    float currNote = mScene->GetGame()->GetNota(mScene->GetGame()->GetActiveMateria());
    SetNotaAtual(currNote);

    float currTimer = mScene->GetActiveTeacher()->GetCurrentState()->GetStateTime();
    SetStateTimeAtual(currTimer);

    int currPontos = mScene->GetPlayer()->GetNumPontosExtras();
    SetPontosPlayer(currPontos);

    DrawPoints(currPontos);
    ManageAnimations();
}

void LimiterMenu::ManageAnimations()
{
    auto currNote = mScene->GetGame()->GetNota(mScene->GetGame()->GetActiveMateria());
    if(currNote >= 60)
    {
        mDrawComponent->SetAnimation("approved");

    }
    else if (currNote < 40)
        mDrawComponent->SetAnimation("reproved");
    else
        mDrawComponent->SetAnimation("normal");
}

void LimiterMenu::writeNew(std::string &newString, int offSetY_) {

    auto newTextActor = new Actor(mScene);
    auto textPosition = Vector2((float)mScene->GetGame()->GetGameWindowWidth() + offSetX,
                                (float)mScene->GetGame()->GetGameWindowHeight() / 8);

    newTextActor->SetPosition(textPosition + Vector2(0, offSetY * offSetY_));
    auto tMostraTexto = new DrawTextComponent(newTextActor, newString, mFont, 256, 32, 32, 102);
    mDrawTextComponent.push_back(tMostraTexto);
}

void LimiterMenu::changeText(int index, std::string & newText)
{
    mDrawTextComponent[index]->SetText(newText);
}

void LimiterMenu::DrawApprovedSign()
{

}

void LimiterMenu::DrawPoints(int currPontos)
{
    for (auto it : mDrawExtraPoints)
    {
        it->SetIsVisible(false);
    }

    for(int i = 0; i < currPontos; i++)
    {
        mDrawExtraPoints[i]->SetIsVisible(true);
        switch (i) {
            case 0: {
                auto Pos = mScene->GetPlayer()->GetPosition() + Vector2(32, 0);
                mExtraPoints[0]->SetPosition(Pos);
                break;
            }
            case 1: {
                auto Pos = mScene->GetPlayer()->GetPosition() + Vector2(-32, 0);
                mExtraPoints[1]->SetPosition(Pos);
                break;
            }
            case 2: {
                auto Pos = mScene->GetPlayer()->GetPosition() + Vector2(0, 32);
                mExtraPoints[2]->SetPosition(Pos);
                break;
            }
        }
    }

}

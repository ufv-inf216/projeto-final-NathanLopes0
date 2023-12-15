//
// Created by User on 14/12/2023.
//

#include "Battle.h"
#include "../Game.h"
#include "../Actors/LimiterMenu.h"

Battle::Battle(Game *game) : Scene(game) {

}

void Battle::Load()
{
    int currStage = mGame->GetCurrStage();
    mActiveTeacher = new Teacher(this, Teacher::Type(currStage));

    std::string player1avatar = "../Assets/Player/DPIBHPlayerPrototype.png";
    mPlayer = new Player(this, player1avatar);
    mPlayer->SetPosition(Vector2(mGame->GetGameWindowWidth() / 2.0f, mGame->GetGameWindowHeight() - 128.0f));

    std::string limiterMenuPath = "../Assets/DPIBHBackgroundPlaceholder.png";
    mLimiterMenu = new LimiterMenu(this, limiterMenuPath, GetGame()->GetWindowWidth(), GetGame()->GetWindowHeight());
    GetGame()->GetAudio()->PlaySound("backgroundmusic.mp3", true);

    mActiveTeacher->Start();
}

void Battle::ProcessInput(const Uint8 *keyState) {

}

Teacher* Battle::GetActiveTeacher()
{
    return mActiveTeacher;
}

Player* Battle::GetPlayer() {
    return mPlayer;
}

LimiterMenu* Battle::GetLimiterMenu()
{
    return mLimiterMenu;
}
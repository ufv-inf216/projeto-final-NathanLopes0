//
// Created by User on 29/11/2023.
//

#include "StartState.h"
#include "../Teacher.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../LimiterMenu.h"
#include "../../../Scenes/Scene.h"
#include "../../../Game.h"
#include "../../../Components/RigidBodyComponent.h"

StartState::StartState(FSMComponent *fsm) : TState(fsm, "start") {

}

void StartState::Start() {

    mTeacher->SetState(ActorState::Active);
    mTeacher->GetComponent<DrawSpriteComponent>()->SetIsVisible(true);
    mTeacher->SetCurrentStateRepresentation(this);
    std::string nTxt = " ";
    mTeacher->GetScene()->GetLimiterMenu()->writeNew(nTxt, 6);

    switch (mTeacher->GetType()) {
        case Teacher::Ricardo:
            mTeacher->GetScene()->GetGame()->SetActiveMateria(Game::INF250);
            mTeacher->GetScene()->GetGame()->SetNota(40, mTeacher->GetScene()->GetGame()->GetActiveMateria());
            break;
        case Teacher::Salles:
            mTeacher->GetScene()->GetGame()->SetActiveMateria(Game::INF213);
            mTeacher->GetScene()->GetGame()->SetNota(40, mTeacher->GetScene()->GetGame()->GetActiveMateria());
            break;
        default:
            break;
    }

    mTeacher->SetPosition(Vector2((float) mTeacher->GetScene()->GetGame()->GetGameWindowWidth() / 2,
                                  -(float) mTeacher->GetSpriteHeight() / 2));
    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(0, 100));


}

void StartState::HandleStateTransition(float stateTime) {

    if(mTeacher->GetPosition().y >= (float)mTeacher->GetSpriteHeight())
    {
        mFSM->SetState("stateOne");
    }

}

void StartState::Update(float deltaTime) {

}
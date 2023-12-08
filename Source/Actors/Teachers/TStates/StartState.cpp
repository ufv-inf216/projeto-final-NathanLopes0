//
// Created by User on 29/11/2023.
//

#include "StartState.h"
#include "../Teacher.h"
#include "../../../Components/AIComponents/FSMComponent.h"

StartState::StartState(FSMComponent *fsm) : TState(fsm, "start") {

}

void StartState::Start() {

    mTeacher->SetState(ActorState::Active);
    mTeacher->GetComponent<DrawSpriteComponent>()->SetIsVisible(true);

    mTeacher->SetPosition(Vector2((float) mTeacher->GetGame()->GetGameWindowWidth() / 2,
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
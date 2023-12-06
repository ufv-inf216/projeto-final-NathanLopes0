//
// Created by User on 06/12/2023.
//

#include "StateTwo.h"
#include "../Teacher.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"

StateTwo::StateTwo(FSMComponent *fsm) : TState(fsm, "stateTwo"),
    atkTimer(0)
{

}

void StateTwo::Start() {

    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
    // nao da certo pq o while acontece inteiro antes de sair do Start, e o professor visualmente se
    // teleporta pro meio
//    while(!inCenter())
//    {
//        moveToCenter();
//    }

}

bool StateTwo::inCenter()
{
    if((mTeacher->GetPosition() -
    Vector2(mTeacher->GetGame()->GetGameWindowWidth()/ 2, mTeacher->GetGame()->GetGameWindowHeight()/2)).Length() < 2)
        return true;
    return false;
}

void StateTwo::moveToCenter()
{
    Vector2 directionToCenter = Vector2(mTeacher->GetGame()->GetGameWindowWidth()/ 2, mTeacher->GetGame()->GetGameWindowHeight()/2) - mTeacher->GetPosition();
    directionToCenter.Normalize();

    mTeacher->SetPosition(Vector2(mTeacher->GetPosition()) + directionToCenter);
}

void StateTwo::Update(float deltaTime) {

    stateTime += deltaTime;
}

void StateTwo::HandleStateTransition(float stateTimer) {

    if (stateTimer > 10)
    {
        mFSM->SetState("stateOne");
    }

}

void StateTwo::Movement() {

}



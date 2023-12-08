//
// Created by User on 01/12/2023.
//

#include "StateOne.h"
#include "../Teacher.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"

StateOne::StateOne(FSMComponent *fsm)
    : TState(fsm, "stateOne")
{
    switch (mTeacher->GetType()) {
        case Teacher::Ricardo:
            mTaskSpeed = 150;
            stateAtkTimer = 1.3;
            break;
        case Teacher::Salles:
            mTaskSpeed = 280;
            stateAtkTimer = 0.6;
            break;
        default:
            mTaskSpeed = 0;
            break;
    }
}

void StateOne::Start() {

    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
    stateTime = 0;

}

void StateOne::Update(float deltaTime) {

    stateTime += deltaTime;

    switch(mTeacher->GetType())
    {
        case Teacher::Ricardo: {
            Movement();
            Attack(deltaTime, 0, 360, true, true, stateAtkTimer, 30, mTaskSpeed, 1);
            break;
        }
        case Teacher::Salles: {
            Movement();
            float startAngle = Random::GetFloatRange(180, 360);
            int playerDirectionInt = Random::GetIntRange(0, 99);
            bool playerDirection = false;
            if (playerDirectionInt < 20) playerDirection = true;
            Attack(deltaTime, startAngle, startAngle + 20, false, playerDirection, stateAtkTimer, 2, mTaskSpeed, 1.2);
            break;
        }
        default:
            break;
    }

    if(DetectCollision()) stateTime += 3 * deltaTime;
    HandleStateTransition(stateTime);

}

void StateOne::Movement()
{
    float border = 64;
    int randNum = Random::GetIntRange(0, 99);
    if(mTeacher->left)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150, 0));
        if(randNum > 98) {
            mTeacher->right = true;
            mTeacher->left = false;
        }
    } else if(mTeacher->right)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
        if(randNum > 98) {
            mTeacher->right = false;
            mTeacher->left = true;
        }
    }

    if (mTeacher->GetPosition().x > (float)mTeacher->GetGame()->GetGameWindowWidth() || mTeacher->GetPosition().x < border) {
        if(mTeacher->left) mTeacher->SetPosition(Vector2(mTeacher->GetPosition().x + (float)mTeacher->GetSpriteWidth() / 6, mTeacher->GetPosition().y));
        if(mTeacher->right) mTeacher->SetPosition(Vector2(mTeacher->GetPosition().x - (float)mTeacher->GetSpriteWidth() / 6, mTeacher->GetPosition().y));
        mTeacher->left = !mTeacher->left;
        mTeacher->right = !mTeacher->right;
    }

}


void StateOne::HandleStateTransition(float stateTimer) {

    //fazer o 30 ser uma variável que é recebida no Start e modificada, para poder ficar no estado por tempos
    //diferentes caso tenham professores diferentes.
    if (stateTimer > 40)
    {
        mTaskSpeed += 40;
        stateAtkTimer = Math::Max(stateAtkTimer - 0.25, 0.1);
        mTeacher->GetGame()->GetAudio()->PlaySound("enep01.wav");
        mTeacher->GetGame()->GetPlayer1()->addStage();
        mTeacher->GetGame()->SetActiveTeacher(mTeacher->GetGame()->GetPlayer1()->GetStage());
    }
}


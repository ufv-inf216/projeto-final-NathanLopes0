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
            stateAtkfrequency = 1.6;
            break;
        case Teacher::Salles:
            mTaskSpeed = 280;
            stateAtkfrequency = 0.2;
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
            Movement(deltaTime);
            bool playerDirection = false;
            bool dividefocus = false;
            int numTasks = 30;
            if (mTaskSpeed >= 190) playerDirection = true;
            if (mTaskSpeed >= 230) dividefocus = true;
            if (mTaskSpeed >= 270) numTasks = 45;
            Attack(deltaTime, 0, 360, dividefocus, playerDirection, stateAtkfrequency, numTasks, mTaskSpeed, 1);
            break;
        }
        case Teacher::Salles: {
            Movement(deltaTime);
            float startAngle = Random::GetFloatRange(180, 360);
            int playerDirectionInt = Random::GetIntRange(0, 99);
            bool playerDirection = false;
            int numTasks = 2;
            if(mTaskSpeed >= 400) numTasks = 3;
            if (playerDirectionInt < 20) playerDirection = true;
            Attack(deltaTime, startAngle, startAngle + 20, false, playerDirection, stateAtkfrequency, numTasks, mTaskSpeed, 1.2);
            break;
        }
        case Teacher::Andre:
            Movement(deltaTime);
            break;

        default:
            break;
    }

    if(DetectCollision()) {
        float points = Random::GetFloatRange(0.2, 0.6);
        mTeacher->GetGame()->SetNota(mTeacher->GetGame()->GetNota(mTeacher->GetGame()->GetActiveMateria()) + points,
                                     mTeacher->GetGame()->GetActiveMateria());
    }

    SDL_Log("%f, %f", stateTime, mTeacher->GetGame()->GetNota(mTeacher->GetGame()->GetActiveMateria()));
    //HandleStateTransition(stateTime);

}

void StateOne::Movement(float deltaTime)
{
    moveTime += deltaTime;
    float border = 64;
    if (mTeacher->GetPosition().x < border)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
        moveTime = 1;
    }
    if (mTeacher->GetPosition().x > (float)mTeacher->GetGame()->GetGameWindowWidth() - (float)mTeacher->GetSpriteWidth() / 2)
    {
        mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150,0));
        moveTime = 1;
    }

    if (moveTime > 1.5) {
        int randNum = Random::GetIntRange(0, 99);
        if (mTeacher->left) {
            mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150, 0));
            if (randNum < 50) {
                mTeacher->right = true;
                mTeacher->left = false;
            }
        } else if (mTeacher->right) {
            mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
            if (randNum < 50) {
                mTeacher->right = false;
                mTeacher->left = true;
            }
        }
        moveTime = 0;
    }
}


void StateOne::HandleStateTransition(float stateTimer) {

    //fazer o escalar ser uma variável que é recebida no Start e modificada, para poder ficar no estado por tempos
    //diferentes caso tenham professores diferentes.
    if (stateTimer > 10)
    {
        if(mTeacher->GetGame()->GetNota(mTeacher->GetGame()->GetActiveMateria()) >= 60)
        {
            mTaskSpeed += 40;
            mTaskSpeed = Math::Min(mTaskSpeed, 400.f);
            stateAtkfrequency = (float)Math::Max(stateAtkfrequency - 0.2, 0.1);
            mTeacher->GetGame()->GetAudio()->PlaySound("enep01.wav");
            mTeacher->GetGame()->GetPlayer1()->addStage();
            mTeacher->GetGame()->SetActiveTeacher(mTeacher->GetGame()->GetPlayer1()->GetStage());
        }
        else {
            mTeacher->GetGame()->SetActiveTeacher(mTeacher->GetGame()->GetPlayer1()->GetStage());
        }

    }
}


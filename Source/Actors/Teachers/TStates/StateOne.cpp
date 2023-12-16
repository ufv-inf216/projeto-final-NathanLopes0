//
// Created by User on 01/12/2023.
//

#include "StateOne.h"
#include "../Teacher.h"
#include "../../Projectiles/Task.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../LimiterMenu.h"
#include "../../../Random.h"
#include "../../../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../../../Scenes/Scene.h"
#include "../../../Game.h"

StateOne::StateOne(FSMComponent *fsm)
    : TState(fsm, "stateOne")
    
{

}

void StateOne::Start() {

    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
    stateTime = 0;
    mTeacher->SetCurrentStateRepresentation(this);
    std::string nTxt = "Prova 1 de 3";
    mTeacher->GetScene()->GetLimiterMenu()->changeText(3, nTxt);

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

void StateOne::Update(float deltaTime) {

    stateTime += deltaTime;
    Movement(deltaTime);

    switch(mTeacher->GetType())
    {
        case Teacher::Ricardo: {
            Attack(deltaTime, 0, 360, false, false, stateAtkfrequency, 30, mTaskSpeed, 1);
            break;
        }
        case Teacher::Salles: {
            float startAngle = Random::GetFloatRange(180, 360);
            int playerDirectionInt = Random::GetIntRange(0, 99);
            bool playerDirection = false;
            int numTasks = 2;
            if (playerDirectionInt < 20) {
                playerDirection = true;
            }
            auto tasksColor = Attack(deltaTime, startAngle, startAngle + 20, false, playerDirection, stateAtkfrequency, numTasks, mTaskSpeed, 1.2);
            if (playerDirection)
            {
                for (auto it : tasksColor)
                {
                    it->GetComponent<DrawSpriteWColorEffect>()->SetColorEffect(180, 20, 180, 1);
                }
            }
            break;
        }
        default:
            break;
    }

    if(DetectCollision()) {
        float points = Random::GetFloatRange(0.1, 0.18);
        auto mt = mTeacher->GetScene()->GetGame()->GetActiveMateria();
        mTeacher->GetScene()->GetGame()->SetNota(mTeacher->GetScene()->GetGame()->GetNota(mt) + points,
                                     mt);
    }

    if(mTeacher->GetScene()->GetGame()->GetNota(mTeacher->GetScene()->GetGame()->GetActiveMateria()) <= 0)
    {
        mTeacher->GetScene()->GetGame()->SetScene(Game::GameScene::MainMenu);
    }
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
    if (mTeacher->GetPosition().x > (float)mTeacher->GetScene()->GetGame()->GetGameWindowWidth() - (float)mTeacher->GetSpriteWidth() / 2)
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

    //colocar 17 - 20. está 2 apenas pra testar a mudança de estado.
    if (stateTimer > 17) {
        mTeacher->GetScene()->GetGame()->GetAudio()->PlaySound("enep01.wav");
        mFSM->SetState("stateTwo");
    }
}
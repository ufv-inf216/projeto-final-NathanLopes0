//
// Created by User on 06/12/2023.
//

#include "StateTwo.h"
#include "../Teacher.h"
#include "../../Projectiles/Question.h"
#include "../../Projectiles/Task.h"
#include "../../LimiterMenu.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Scenes/Scene.h"
#include "../../../Game.h"
#include "../../../Random.h"
#include "../../../Components/DrawComponents/DrawSpriteWColorEffect.h"

StateTwo::StateTwo(FSMComponent *fsm) : TState(fsm, "stateTwo"),
    centeredOnce(false)
{

}

void StateTwo::Start() {

    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
    stateTime = 0;
    mTeacher->SetCurrentStateRepresentation(this);
    std::string nTxt = "Prova 2 de 3";
    mTeacher->GetScene()->GetLimiterMenu()->changeText(3, nTxt);

    switch (mTeacher->GetType()) {
        case Teacher::Ricardo: {
            mTaskSpeed = 190;
            stateAtkfrequency = 1.6;
            break;
        }
        case Teacher::Salles: {
            mTaskSpeed = 280;
            stateAtkfrequency = 0.2;
            break;
        }
        default:
            mTaskSpeed = 0;
            break;
    }
}

bool StateTwo::inCenter()
{
    float centerRadius = 20;
    if((mTeacher->GetPosition() -
    Vector2(mTeacher->GetScene()->GetGame()->GetGameWindowWidth()/ 2, mTeacher->GetSpriteHeight())).Length() < centerRadius) {
        centeredOnce = true;
        return true;
    }
    return false;
}

void StateTwo::moveToCenter(float deltaTime)
{
    Vector2 directionToCenter = Vector2(mTeacher->GetScene()->GetGame()->GetGameWindowWidth()/ 2, mTeacher->GetSpriteHeight()) - mTeacher->GetPosition();
    directionToCenter.Normalize();

    mTeacher->SetPosition(Vector2(mTeacher->GetPosition()) + (directionToCenter * 100 * deltaTime));
}

void StateTwo::Update(float deltaTime) {

    if (!centeredOnce && !inCenter()) moveToCenter(deltaTime);
    else
    {
        stateTime += deltaTime;
        Movement(deltaTime);

        switch (mTeacher->GetType()) {
            case Teacher::Ricardo: {
                Attack(deltaTime, 0, 360, false, true,
                       stateAtkfrequency, 30, mTaskSpeed, 1);
                break;
            }
            case Teacher::Salles: {
                float angle = Random::GetFloatRange(180, 360);
                int pDInt = Random::GetIntRange(0, 99);
                bool pDirection = false;
                if (pDInt < 30) pDirection = true;
                auto tasksColor = Attack(deltaTime, angle, angle + 30, false,
                                         pDirection, stateAtkfrequency, 2, mTaskSpeed, 1.8);
                if (pDirection)
                    for (auto it : tasksColor)
                        it->GetComponent<DrawSpriteWColorEffect>()->SetColorEffect(180, 20, 180, 1);
                break;
            }
            default:
                break;
        }
        if (DetectCollision()) {
            float points = Random::GetFloatRange(0.15, 0.3);
            auto mt = mTeacher->GetScene()->GetGame()->GetActiveMateria();
            mTeacher->GetScene()->GetGame()->SetNota(mTeacher->GetScene()->GetGame()->GetNota(mt) + points,
                                         mt);
        }
    }
}

void StateTwo::HandleStateTransition(float stateTimer) {

    if (stateTimer > 18)
    {
        mFSM->SetState("stateThree");
    }

}

void StateTwo::Movement(float deltaTime) {
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



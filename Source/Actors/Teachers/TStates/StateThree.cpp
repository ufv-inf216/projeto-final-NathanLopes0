//
// Created by User on 13/12/2023.
//

#include "StateThree.h"
#include "../Teacher.h"
#include "../../Projectiles/Task.h"
#include "../../LimiterMenu.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Scenes/Scene.h"
#include "../../../Game.h"
#include "../../../Random.h"
#include "../../../Components/DrawComponents/DrawSpriteWColorEffect.h"


StateThree::StateThree(FSMComponent *fsm) : TState(fsm, "stateThree"), centeredOnce(false) {

}

void StateThree::Start() {
    mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2::Zero);
    stateTime = 0;
    mTeacher->SetCurrentStateRepresentation(this);
    std::string nTxt = "Prova 3 de 3";
    mTeacher->GetScene()->GetLimiterMenu()->changeText(3, nTxt);

    switch (mTeacher->GetType()) {
        case Teacher::Ricardo: {
            mTaskSpeed = 230;
            stateAtkfrequency = 1.4;
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

bool StateThree::inCenter()
{
    float centerRadius = 20;
    if((mTeacher->GetPosition() -
        Vector2((float)mTeacher->GetScene()->GetGame()->GetGameWindowWidth()/ 2, (float)mTeacher->GetSpriteHeight())).Length() < centerRadius) {
        centeredOnce = true;
        return true;
    }
    return false;
}

void StateThree::moveToCenter(float deltaTime)
{
    Vector2 directionToCenter = Vector2((float)mTeacher->GetScene()->GetGame()->GetGameWindowWidth()/ 2, (float)mTeacher->GetSpriteHeight()) - mTeacher->GetPosition();
    directionToCenter.Normalize();

    mTeacher->SetPosition(Vector2(mTeacher->GetPosition()) + (directionToCenter * 100 * deltaTime));
}

void StateThree::Update(float deltaTime) {
    if (!centeredOnce && !inCenter()) moveToCenter(deltaTime);
    else
    {
        stateTime += deltaTime;
        Movement(deltaTime);

        switch (mTeacher->GetType()) {
            case Teacher::Ricardo: {
                Attack(deltaTime, 0, 360, true, true,
                       stateAtkfrequency, 50, mTaskSpeed, 0.8);
                break;
            }
            case Teacher::Salles: {
                float angle = Random::GetFloatRange(180, 360);
                int pDInt = Random::GetIntRange(0, 99);
                bool pDirection = false;
                if (pDInt < 40) pDirection = true;
                auto tasksColor = Attack(deltaTime, angle, angle + 40, false,
                                         pDirection, stateAtkfrequency, 3, mTaskSpeed, 1.8);
                if (pDirection)
                    for (auto it : tasksColor)
                        it->GetComponent<DrawSpriteWColorEffect>()->SetColorEffect(180,20,180,1);
                break;
            }
            default:
                break;
        }

        if(DetectCollision()) {
            float points = Random::GetFloatRange(0.2, 0.4);
            auto mt = mTeacher->GetScene()->GetGame()->GetActiveMateria();
            mTeacher->GetScene()->GetGame()->SetNota(mTeacher->GetScene()->GetGame()->GetNota(mt) + points,
                                         mt);
        }
    }
}


void StateThree::Movement(float deltaTime) {

    if (mTeacher->GetType() != Teacher::Salles) {
        moveTime += deltaTime;
        float border = 64;
        if (mTeacher->GetPosition().x < border) {
            mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(150, 0));
            moveTime = 1;
        }
        if (mTeacher->GetPosition().x >
            (float) mTeacher->GetScene()->GetGame()->GetGameWindowWidth() - (float) mTeacher->GetSpriteWidth() / 2) {
            mTeacher->GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(-150, 0));
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
}


void StateThree::HandleStateTransition(float stateTimer) {
    if (stateTimer > 17)
    {
        for(auto it : mTeacher->GetScene()->GetGame()->GetTasks())
        {
            it->SetState(ActorState::Destroy);
            mTeacher->GetScene()->GetGame()->RemoveTask(it);
        }
        if (mTeacher->GetScene()->GetGame()->GetNota(mTeacher->GetScene()->GetGame()->GetActiveMateria()) >= 60)
        {
                int newStage = mTeacher->GetScene()->GetGame()->GetCurrStage() + 1;
                if (newStage > 1)
                    mTeacher->GetScene()->GetGame()->SetScene(Game::GameScene::Win);
                else {
                    mTeacher->GetScene()->GetGame()->SetStage(newStage);
                    mTeacher->GetScene()->GetGame()->SetScene(Game::GameScene::Battle);
                }
        }
        else
            mTeacher->GetScene()->GetGame()->SetScene(Game::GameScene::Battle);
    }
}

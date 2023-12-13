//
// Created by User on 01/12/2023.
//

#include "StateOne.h"
#include "../Teacher.h"
#include "../../Projectiles/Task.h"
#include "../../Projectiles/Question.h"
#include "../../../Components/AIComponents/FSMComponent.h"
#include "../../../Actors/LimiterMenu.h"

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
    mTeacher->SetCurrentStateRepresentation(this);

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
    if (stateTimer > 30)
    {
        if(mTeacher->GetGame()->GetNota(mTeacher->GetGame()->GetActiveMateria()) >= 60)
        {
            mTaskSpeed += 40;
            mTaskSpeed = Math::Min(mTaskSpeed, 400.f);
            stateAtkfrequency = (float)Math::Max(stateAtkfrequency - 0.2, 0.1);
            mTeacher->GetGame()->GetAudio()->PlaySound("enep01.wav");
            mTeacher->GetGame()->GetPlayer1()->addStage();
            mTeacher->GetGame()->SetActiveTeacher(mTeacher->GetGame()->GetPlayer1()->GetStage());
            switch (mTeacher->GetType())
            {
                case Teacher::Ricardo: {
                    if (mTaskSpeed == 190) {
                        std::string nTxt = "Ricardo Prova 1 de 3";
                        mTeacher->GetGame()->GetLimiterMenu()->writeNew(nTxt, 6);
                    }
                    if (mTaskSpeed == 230) {
                        std::string nTxt = "Ricardo Prova 2 de 3";
                        mTeacher->GetGame()->GetLimiterMenu()->changeText(3, nTxt);
                    }
                    if (mTaskSpeed == 270) {
                        std::string nTxt = "Ricardo Prova 3 de 3! Passou em INF 250!!";
                        mTeacher->GetGame()->GetLimiterMenu()->changeText(3, nTxt);
                    }
                    break;
                }
                    case Teacher::Salles: {
                        if(mTaskSpeed == 320)
                        {
                            std::string nTxt = "Salles Prova 1 de 3";
                            mTeacher->GetGame()->GetLimiterMenu()->writeNew(nTxt, 8);
                        }
                        if(mTaskSpeed == 360)
                        {
                            std::string nTxt = "Salles Prova 2 de 3";
                            mTeacher->GetGame()->GetLimiterMenu()->changeText(4, nTxt);
                        }
                        if(mTaskSpeed == 400)
                        {
                            std::string nTxt = "Salles Prova 3 de 3! Passou de INF 213!!";
                            mTeacher->GetGame()->GetLimiterMenu()->changeText(4, nTxt);
                        }
                        break;
                    }
                    default:
                        break;
            }
        }
        else {
            mTeacher->GetGame()->SetActiveTeacher(mTeacher->GetGame()->GetPlayer1()->GetStage());
        }
    }
}


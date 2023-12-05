//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include <string>
#include <iostream>
#include "Teacher.h"
#include "../Projectiles/Question.h"
#include "../Projectiles/Task.h"
#include "../../Components/AIComponents/FSMComponent.h"
#include "TStates/StartState.h"
#include "TStates/StateOne.h"

Teacher::Teacher(Game *game, Type type)
    :Actor(game),
    mType(type),
    left(true),
    right(false),
    extraPointCounter(10),
    atkTimer(2)

{

    startAngle = 180;
    finalAngle = 360;
    reflect = false;

    std::string prefix = "../Assets/Teachers/";
    //escolher a sprite de acordo com o tipo
    switch(mType)
    {
        case Ricardo:
            prefix += "DPIBHRicardoStartPrototype";
            break;
        case Salles:
            prefix += "DPIBHSallesStartPrototypeScaled";
            break;
        default:
            SDL_Log("Teacher Sprite doesn't exist");
            break;
    }

    //componentes
    mDrawSprite = new DrawSpriteComponent(this, prefix + ".png", 128, 128, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 32);

    //colocando os estados
    mFSMComponent = new FSMComponent(this);
    new StartState(mFSMComponent);
    new StateOne(mFSMComponent);

    //colocando o estado inicial "start"
    //a ideia é ele estar na posição setada acima, com SetPosition, e colocar ele descendo no início do estado Start.
    //SetState chama o Start do estado com nome "start"
    mFSMComponent->Start("start");


}

void Teacher::OnUpdate(float deltaTime) {

    //SDL_Log("%f", GetPosition().y);


    if (extraPointCounter <= 0)
    {
        CreateExtraPoint();
        //mudar para 80 depois, 40 apenas para mostrar/debug
        extraPointCounter = 40;
        GetGame()->GetAudio()->PlaySound("extraPt.wav");
    }
}

void Teacher::CreateExtraPoint() {
    auto point = new PowerUp(mGame);
    point->SetPosition(GetPosition() + Vector2(0, 64));
}

void Teacher::TaskCreation(float startAngle, float finalAngle, int numTasks, float speed, bool playerDirection, double waitTime) {

    std::string spritePath;
    switch (GetType())
    {
        case Type::Ricardo:
            spritePath = "../Assets/Teachers/DPIBHArduinoPrototype2.png";
            break;
        default:
            spritePath = "../Assets/Icons/PlaceholderTask.png";
            break;

    }

    float difAngle = finalAngle - startAngle;
    float angleDifference;
    if (difAngle >= 0)
        angleDifference = difAngle / (numTasks + 1);
    else
        angleDifference = (difAngle + 360) / (numTasks + 1);

    for (int i = 0; i < numTasks; i++) {

        float currAngle = -startAngle - (angleDifference * (i + 1));
        std::cout << "Task de angulo " << -currAngle << " -> Vetor velocidade normalizado: ";
        auto task = new Task(GetGame(), this, spritePath, currAngle, speed, playerDirection, waitTime);
        task->SetPosition(GetPosition());

        //DEBUG
        auto aux = task->GetComponent<RigidBodyComponent>()->GetVelocity();
        auto normVel = Vector2::Normalize(aux);
        std::cout << normVel.x << ", " << normVel.y << '\n';


    }

}
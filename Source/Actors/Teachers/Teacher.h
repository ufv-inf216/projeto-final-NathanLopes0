//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_TEACHER_H
#define DPIBULLETHELL_TEACHER_H

#include <string>
#include "../../Random.h"
#include "../../Game.h"
#include "../Player.h"
#include "../PowerUp.h"
#include "../../Components/DrawComponents/DrawSpriteComponent.h"
#include "../../Components/RigidBodyComponent.h"
#include "../../Components/ColliderComponents/CircleColliderComponent.h"

class Teacher : public Actor {
public:
    enum Type
    {
        Ricardo,
        Julio,
        Sabrina,
        Lucas,
        Andre,
        Salles,
        Thiago,
        Marcos

    };

    Teacher(class Game* game, Type type);
    void OnUpdate(float deltaTime) override;
    void CreateExtraPoint();
    Type GetType() { return mType; }

    int GetSpriteHeight() {return GetComponent<DrawSpriteComponent>()->GetSpriteHeight(); }
    int GetSpriteWidth() { return GetComponent<DrawSpriteComponent>()->GetSpriteWidth(); }


    bool left;
    bool right;
    int extraPointCounter;
private:

    class DrawSpriteComponent* mDrawSprite;
    class RigidBodyComponent* mRigidBodyComponent;
    class CircleColliderComponent* mColliderComponent;
    class FSMComponent* mFSMComponent;

    Type mType;
    bool reflect; //reflect é para fazer o comportamento de wave nos ataques
    int hp;
    float atkTimer;
    float startAngle, finalAngle; //também para fazer o comportamento de wave nos ataques



    void TaskCreation(float startAngle, float finalAngle, int numTasks, float speed);
};


#endif //DPIBULLETHELL_TEACHER_H

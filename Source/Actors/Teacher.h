//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_TEACHER_H
#define DPIBULLETHELL_TEACHER_H

#include <string>
#include "../Random.h"
#include "../Game.h"
#include "Player.h"
#include "PowerUp.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ColliderComponents/CircleColliderComponent.h"

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


private:

    class DrawSpriteComponent* mDrawSprite;
    class RigidBodyComponent* mRigidBodyComponent;
    class CircleColliderComponent* mColliderComponent;
    Type mType;
    bool left, right;
    int extraPointCounter;
    float atkTimer;

    void TaskCreation(float startAngle, float finalAngle, float frequency);

    void TaskCreation(float startAngle, float finalAngle, int numTasks);
};


#endif //DPIBULLETHELL_TEACHER_H

//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_TEACHER_H
#define DPIBULLETHELL_TEACHER_H

#include <string>
#include "../Actor.h"
#include "../../Components/DrawComponents/DrawSpriteComponent.h"

class Teacher : public Actor {
public:
    enum Type
    {
        Salles,
        Ricardo,
        Thiago,
        Andre,
        Arroyo,
        Julio,
        Sabrina,
        Marcos,
        Michel,
        Lucas
    };

    Teacher(class Scene* scene, Type type);
    void OnUpdate(float deltaTime) override;
    void CreateExtraPoint();
    Type GetType() { return mType; }
    class TState * GetCurrentState() { return mCurrentState; }
    void SetCurrentStateRepresentation(TState* state) {mCurrentState = state;}

    int GetSpriteHeight() {return GetComponent<class DrawSpriteComponent>()->GetSpriteHeight(); }
    int GetSpriteWidth() { return GetComponent<class DrawSpriteComponent>()->GetSpriteWidth(); }
    void SetExtraPointCounter(float extraPtC);

    class Task *
    TaskCreation(float angle, float speed, bool playerDirection, double waitTime);

    float GetExtraPointTime() const { return extraPointTime; }
    virtual void SetExtraPointTime(float ptT) { extraPointTime = ptT; }


    bool left;
    bool right;
    int extraPointCounter;

    void Start();

private:

    class DrawSpriteComponent* mDrawSprite;
    class RigidBodyComponent* mRigidBodyComponent;
    class CircleColliderComponent* mColliderComponent;
    class FSMComponent* mFSMComponent;
    class TState* mCurrentState;
    std::vector<class Task*> mTasks;

    float extraPointTime;

    Type mType;
};


#endif //DPIBULLETHELL_TEACHER_H

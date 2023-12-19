//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_PLAYER_H
#define DPIBULLETHELL_PLAYER_H

#include <string>

#include "Actor.h"



class Player : public Actor {

public:

    Player(class Scene *scene, std::string &avatarPath);

    void OnUpdate(float deltaTime) override;
    void OnProcessInput(const Uint8 *keyState) override;

    std::vector<class Question *> GetProjectiles() { return mQuestions; }
    bool AddPontoExtra();
    int GetNumPontosExtras() { return numPontosExtras; }
    Vector2 directionToPlayer(const Actor* object);

private:

    float pSpeed;
    float atkTimer;
    int numPontosExtras;
    std::string avatarSpritePath;
    std::vector<class Question*> mQuestions;

    class DrawSpriteWColorEffect* mDrawSprite;
    class RigidBodyComponent * mRigidBodyComponent;
    class CircleColliderComponent* mColliderComponent;
    std::vector <class DrawSpriteComponent*> mDrawPoints;


    float invencibilityTime;
    bool pisca, piscaOvercharge;
    float piscafrequencia;
    bool lose;
};


#endif //DPIBULLETHELL_PLAYER_H

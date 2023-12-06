//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_PLAYER_H
#define DPIBULLETHELL_PLAYER_H

#include <string>

#include "Actor.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/DrawComponents/DrawSpriteComponent.h"
#include "../Components/ColliderComponents/CircleColliderComponent.h"

class Player : public Actor {

public:

    Player(struct Game *game, std::string &avatarPath);


    void OnUpdate(float deltaTime) override;
    std::vector<class Question *> GetProjectiles() { return mQuestions; }
    bool AddPontoExtra();
    Vector2 directionToPlayer(const Actor* object);


private:

    float pSpeed;
    float atkTimer;
    int numPontosExtras;
    std::string avatarSpritePath;
    std::vector<class Question*> mQuestions;

    DrawSpriteComponent* mDrawSprite;
    RigidBodyComponent * mRigidBodyComponent;
    CircleColliderComponent* mColliderComponent;


    void OnProcessInput(const Uint8 *keyState) override;
};


#endif //DPIBULLETHELL_PLAYER_H

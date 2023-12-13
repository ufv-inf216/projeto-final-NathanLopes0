//
// Created by User on 20/10/2023.
//

#ifndef DPIBULLETHELL_PLAYER_H
#define DPIBULLETHELL_PLAYER_H

#include <string>

#include "Actor.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../Components/ColliderComponents/CircleColliderComponent.h"

class Player : public Actor {

public:

    Player(struct Game *game, std::string &avatarPath);


    void OnUpdate(float deltaTime) override;
    std::vector<class Question *> GetProjectiles() { return mQuestions; }
    bool AddPontoExtra();
    int GetNumPontosExtras() { return numPontosExtras; }
    Vector2 directionToPlayer(const Actor* object);
    void addStage();
    int GetStage() const { return stage; }

private:

    float pSpeed;
    float atkTimer;
    int numPontosExtras;
    std::string avatarSpritePath;
    std::vector<class Question*> mQuestions;

    DrawSpriteWColorEffect* mDrawSprite;
    RigidBodyComponent * mRigidBodyComponent;
    CircleColliderComponent* mColliderComponent;


    void OnProcessInput(const Uint8 *keyState) override;
    int stage;
    float invencibilityTime;
    bool pisca, piscaOvercharge;
    float piscafrequencia;
};


#endif //DPIBULLETHELL_PLAYER_H

//
// Created by User on 16/11/2023.
//

#ifndef DPIBULLETHELL_QUESTION_H
#define DPIBULLETHELL_QUESTION_H

#include "Projectile.h"
#include "../Player.h"

class Question : public Projectile {

public:

    Question(Game * game, class Player * owner, std::string &spritePath);

private:
    Player* mOwner;
    float mFowardSpeed;

    void OnUpdate(float deltaTime) override;
};


#endif //DPIBULLETHELL_QUESTION_H

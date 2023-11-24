//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include "Player.h"
#include "Projectiles/Question.h"

Player::Player(struct Game *game, std::string &avatarPath)
        :Actor(game)
        ,pSpeed(300.0f)
        ,atkTimer(0.1f)
        ,numPontosExtras(0)
{

    mDrawSprite = new DrawSpriteComponent(this, avatarPath, 32, 32, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 16);

    SetPosition(Vector2(600, 600));
    std::string spriteQuestionPath = "../Assets/Player/DPIBHStudentProjectile(Question)v3.png";

    for (int i = 0; i < 500; i++)
    {
        auto* question = new Question(GetGame(), this, spriteQuestionPath);
        question->SetState(ActorState::Paused);
        question->GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
        mQuestions.push_back(question);

    }

}

void Player::OnUpdate(float deltaTime) {

    atkTimer -= deltaTime;

//    for (auto it : GetGame()->GetTasks())
//    {
//        if(GetComponent<CircleColliderComponent>()->Intersect())
//        {
//            SetState(ActorState::Destroy);
//        }
//    }

}

void Player::OnProcessInput(const Uint8 *keyState) {

    keyState = SDL_GetKeyboardState(nullptr);

    float newXSpeed = 0;
    float newYSpeed = 0;

    if(keyState[SDL_SCANCODE_W])
    {
        newYSpeed -= pSpeed;
    }
    else if(keyState[SDL_SCANCODE_S])
    {
        newYSpeed += pSpeed;
    }

    if(keyState[SDL_SCANCODE_A])
    {
        newXSpeed -= pSpeed;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        newXSpeed += pSpeed;
    }

    GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(newXSpeed,newYSpeed));

    //limitando (um pouco) o jogador aos limites da tela
    SetPosition(Vector2(std::clamp(GetPosition().x, (float) GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 2.f,(float)GetGame()->GetWindowWidth() - (float)GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 2.f),
                        std::clamp(GetPosition().y, (float) GetComponent<DrawSpriteComponent>()->GetSpriteHeight() / 2.f, (float)GetGame()->GetWindowHeight() - (float)GetComponent<DrawSpriteComponent>()->GetSpriteHeight() / 2.f)
    ));


    //Mudar para V na versão final para 2 jogadores
    if (keyState[SDL_SCANCODE_SPACE])
    {
        if (atkTimer < 0) {
            for (auto it: mQuestions) {
                if (it->GetState() == ActorState::Paused) {
                    it->SetPosition(GetPosition());
                    it->SetState(ActorState::Active);
                    it->GetComponent<DrawSpriteComponent>()->SetIsVisible(true);
                    break;
                }
            }
            mGame->GetAudio()->PlaySound("qst00.wav");
            atkTimer = 0.1;
        }
    }
}

bool Player::AddPontoExtra() {
    if(numPontosExtras == 3) return false;

    numPontosExtras++;
    return true;
}

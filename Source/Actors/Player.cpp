//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include "Player.h"
#include "Projectiles/Question.h"
#include "Projectiles/Task.h"

Player::Player(struct Game *game, std::string &avatarPath)
        :Actor(game)
        ,pSpeed(300.0f)
        ,atkTimer(0.1f)
        ,numPontosExtras(1)
        ,stage(0)
{

    mDrawSprite = new DrawSpriteComponent(this, avatarPath, 48, 48, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    SetPosition(Vector2(GetGame()->GetGameWindowWidth() / 2, GetGame()->GetGameWindowHeight() - GetComponent<DrawSpriteComponent>()->GetSpriteHeight()));
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

    for (auto i : GetGame()->GetTasks())
    {

        if(GetComponent<CircleColliderComponent>()->Intersect(*i->GetComponent<CircleColliderComponent>()))
        {

            SetState(ActorState::Destroy);

            //diminui nota ao invés de destruir. também ganha um tempo de invencibilidade que não conta pontos caso desvie,
            //mas não diminui nota caso seja acertade.
            break;
        }
    }

    if (GetComponent<CircleColliderComponent>()->Intersect(*mGame->GetTeacher(GetStage())->GetComponent<CircleColliderComponent>()))
    {
        SetState(ActorState::Destroy);
        //diminuir nota, ativar invencibility frames ou então não deixar o jogador se aproximar?

    }


}

void Player::OnProcessInput(const Uint8 *keyState) {

    keyState = SDL_GetKeyboardState(nullptr);

    float newXSpeed = 0;
    float newYSpeed = 0;

    if(keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP])
    {
        newYSpeed -= pSpeed;
    }
    else if(keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])
    {
        newYSpeed += pSpeed;
    }

    if(keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT])
    {
        newXSpeed -= pSpeed;
    }
    else if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT])
    {
        newXSpeed += pSpeed;
    }

    GetComponent<RigidBodyComponent>()->SetVelocity(Vector2(newXSpeed,newYSpeed));

    //limitando (um pouco) o jogador aos limites da tela
    SetPosition(Vector2(std::clamp(GetPosition().x, (float) GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 1.1f,(float)GetGame()->GetGameWindowWidth() +
                                GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 2),
                        std::clamp(GetPosition().y, (float) GetComponent<DrawSpriteComponent>()->GetSpriteHeight(), (float)GetGame()->GetGameWindowHeight() +
                                GetComponent<DrawSpriteComponent>()->GetSpriteHeight() / 5)
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
            atkTimer = 0.12;
        }
    }

    if (keyState[SDL_SCANCODE_B] && numPontosExtras > 0)
    {
        numPontosExtras--;
        for(auto it : GetGame()->GetTasks())
        {
            it->SetState(ActorState::Destroy);
            GetGame()->RemoveTask(it);
        }
        mGame->GetAudio()->PlaySound("lazer00.wav");
        atkTimer = 5;
    }
}

bool Player::AddPontoExtra() {
    if(numPontosExtras == 3) return false;

    numPontosExtras++;
    return true;
}

Vector2 Player::directionToPlayer(const Actor *object) {
    auto objectPosition = object->GetPosition();
    auto directionToPlayer = GetPosition() - objectPosition;

    directionToPlayer.Normalize();

    return directionToPlayer;

}

void Player::addStage() {

    stage++;
    int md = mGame->GetTeachers().size();
    stage %= md;

}

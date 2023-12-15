//
// Created by User on 20/10/2023.
//

#include <algorithm>
#include "Player.h"
#include "Projectiles/Question.h"
#include "Projectiles/Task.h"
#include "../Components/DrawComponents/DrawSpriteWColorEffect.h"
#include "../Components/ColliderComponents/CircleColliderComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Game.h"
#include "../Scenes/Scene.h"
#include "../Random.h"

Player::Player(class Scene *scene, std::string &avatarPath)
        :Actor(scene)
        ,pSpeed(300.0f)
        ,atkTimer(0.1f)
        ,numPontosExtras(0)
        ,invencibilityTime(0)
        ,piscafrequencia(0.1)
        ,pisca(true)
        ,piscaOvercharge(false)
{
    mDrawSprite = new DrawSpriteWColorEffect(this, avatarPath, 48, 48, 100);
    mRigidBodyComponent = new RigidBodyComponent(this);
    mColliderComponent = new CircleColliderComponent(this, 8);

    SetPosition(Vector2(mScene->GetGame()->GetGameWindowWidth() / 2, mScene->GetGame()->GetGameWindowHeight() - GetComponent<DrawSpriteComponent>()->GetSpriteHeight()));
    std::string spriteQuestionPath = "../Assets/Player/DPIBHStudentProjectile(Question)v3.png";

    for (int i = 0; i < 500; i++)
    {
        auto* question = new Question(mScene, this, spriteQuestionPath);
        question->SetState(ActorState::Paused);
        question->GetComponent<DrawSpriteComponent>()->SetIsVisible(false);
        mQuestions.push_back(question);

    }

//    mDrawSprite->SetIsVisible(false);
//    SetState(ActorState::Paused);
}

void Player::OnUpdate(float deltaTime)
{
    atkTimer -= deltaTime;
    if (piscaOvercharge && atkTimer <= 0)
    {
        piscaOvercharge = false;
        mDrawSprite->StopColorEffect();
    }

    if (invencibilityTime > 0){
        piscafrequencia -= deltaTime;
        if (piscafrequencia < 0)
        {
            piscafrequencia = 0.1;
            mDrawSprite->SetIsVisible(pisca);
            pisca = !pisca;
        }
        invencibilityTime -= deltaTime;
    }
    if (invencibilityTime <= 0) {
        mDrawSprite->SetIsVisible(true);
        for (auto i: mScene->GetGame()->GetTasks()) {

            if (mColliderComponent->Intersect(*i->GetComponent<CircleColliderComponent>())) {
                float deduceNota = Random::GetFloatRange(9.0f, 13.0f);
                mScene->GetGame()->GetAudio()->PlaySound("pldead00.wav");
                auto mt = mScene->GetGame()->GetActiveMateria();
                mScene->GetGame()->SetNota(mScene->GetGame()->GetNota(mt) - deduceNota, mt);
                invencibilityTime = 2.2;
                if (mScene->GetGame()->GetNota(mt) <= 0) {
                    SetState(ActorState::Destroy);
                }
                break;
            }
        }
    }
    if (mColliderComponent->Intersect(*mScene->GetActiveTeacher()->GetComponent<CircleColliderComponent>()))
    {
        float deduceNota = Random::GetFloatRange(16.0f, 24.0f);
        mScene->GetGame()->GetAudio()->PlaySound("pldead00.wav");
        auto mt = mScene->GetGame()->GetActiveMateria();
        mScene->GetGame()->SetNota(Math::Max(mScene->GetGame()->GetNota(mt) - deduceNota, 0.f), mt);
        invencibilityTime = 2.2;
        if (mScene->GetGame()->GetNota(mt) < 0)
        {
            SetState(ActorState::Destroy);
        }
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

    //limitando o jogador aos limites da tela
    SetPosition(Vector2(std::clamp(GetPosition().x, (float) GetComponent<DrawSpriteComponent>()->GetSpriteWidth() / 1.1f,(float)mScene->GetGame()->GetGameWindowWidth() +
                                GetComponent<DrawSpriteWColorEffect>()->GetSpriteWidth() / 2),
                        std::clamp(GetPosition().y, (float) GetComponent<DrawSpriteComponent>()->GetSpriteHeight(), (float)mScene->GetGame()->GetGameWindowHeight() +
                                GetComponent<DrawSpriteWColorEffect>()->GetSpriteHeight() / 5)
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
            mScene->GetGame()->GetAudio()->PlaySound("qst00.wav");
            atkTimer = 0.12;
        }
    }

    if (keyState[SDL_SCANCODE_B] && numPontosExtras > 0 && atkTimer < 0)
    {
        numPontosExtras--;
        auto mt = mScene->GetGame()->GetActiveMateria();
        mScene->GetGame()->SetNota(mScene->GetGame()->GetNota(mt) + 10, mt);
        for(auto it : mScene->GetGame()->GetTasks())
        {
            it->SetState(ActorState::Destroy);
            mScene->GetGame()->RemoveTask(it);
        }
        mScene->GetGame()->GetAudio()->PlaySound("lazer00.wav");
        atkTimer = 5;
        piscaOvercharge = true;
        mDrawSprite->SetColorEffect(255, 0, 0, 255);
    }
}

bool Player::AddPontoExtra() {
    if(numPontosExtras >= 3)
    {
        auto mt = mScene->GetGame()->GetActiveMateria();
        mScene->GetGame()->SetNota(mScene->GetGame()->GetNota(mt) + Random::GetFloatRange(1.0f, 2.0f),
                       mt);

        return false;
    }

    mScene->GetGame()->GetAudio()->PlaySound("powerup.wav");
    numPontosExtras++;
    return true;
}

Vector2 Player::directionToPlayer(const Actor *object) {
    auto objectPosition = object->GetPosition();
    auto directionToPlayer = GetPosition() - objectPosition;

    directionToPlayer.Normalize();
    return directionToPlayer;

}

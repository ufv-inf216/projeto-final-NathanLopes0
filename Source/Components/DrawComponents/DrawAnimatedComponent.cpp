//
// Created by Lucas N. Ferreira on 28/09/23.
//

#include "DrawAnimatedComponent.h"
#include "../../Actors/Actor.h"
#include "../../Game.h"
#include "../../Json.h"
#include "../../Scenes/Scene.h"
#include <fstream>

DrawAnimatedComponent::DrawAnimatedComponent(class Actor* owner, const std::string &spriteSheetPath, const std::string &spriteSheetData, int drawOrder)
        :DrawSpriteComponent(owner, spriteSheetPath, 0, 0, drawOrder)
{
    LoadSpriteSheet(spriteSheetPath, spriteSheetData);
}

DrawAnimatedComponent::~DrawAnimatedComponent()
{
    for (const auto& rect : mSpriteSheetData)
    {
        delete rect;
    }
    mSpriteSheetData.clear();
}

void DrawAnimatedComponent::LoadSpriteSheet(const std::string& texturePath, const std::string& dataPath)
{
    // Load sprite sheet texture
    mSpriteSheetSurface = mOwner->GetScene()->GetGame()->LoadTexture(texturePath);

    // Load sprite sheet data
    std::ifstream spriteSheetFile(dataPath);
    nlohmann::json spriteSheetData = nlohmann::json::parse(spriteSheetFile);

    SDL_Rect* rect = nullptr;
    for(const auto& frame : spriteSheetData["frames"]) {

        int x = frame["frame"]["x"].get<int>();
        int y = frame["frame"]["y"].get<int>();
        int w = frame["frame"]["w"].get<int>();
        int h = frame["frame"]["h"].get<int>();
        rect = new SDL_Rect({x, y, w, h});

        mSpriteSheetData.emplace_back(rect);
    }
}

void DrawAnimatedComponent::Draw(SDL_Renderer *renderer) {

    auto spriteIdx = mAnimations[mAnimName][(int) mAnimTimer];

    int posx = GetOwner()->GetPosition().x - GetScene()->GetCameraPos().x;
    int posy = GetOwner()->GetPosition().y - GetScene()->GetCameraPos().y;


    //provavelmente mudar o 32 fixo para uma variável. Mas n tava dando certo no Mario. O que fazer?
    auto dstrect = new SDL_Rect{posx, posy, 32, 32};

    auto flipflag = SDL_RendererFlip::SDL_FLIP_NONE;

    if (GetOwner()->GetRotation() == Math::Pi)
        flipflag = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

    SDL_RenderCopyEx(renderer, mSpriteSheetSurface, mSpriteSheetData[spriteIdx],
                    dstrect, NULL, nullptr, flipflag);

}


void DrawAnimatedComponent::Update(float deltaTime)
{
    // --------------
    // TODO - PARTE 4
    // --------------

    // TODO 1.1 (~2 linhas): Verifique se animação está pausada (`mIsPaused`). Se estiver, saia da função (return).

    if(mIsPaused) return;

    // TODO 1.2 (~1 linha): Atualize o timer da animação `mAnimTimer` com base na taxa de atualização
    //  (`mAnimFPS`) e no delta time.

    mAnimTimer += mAnimFPS * deltaTime;

    // TODO 1.3 (~3 linhas): Podemos converter o timer da animação `mAnimTimer`para inteiro para obter o índice do quadro
    //  atual. No entanto, temos que garantir que esse índice não será maior do que número total de quadros da animação
    //  corrente (`mAnimations[mAnimName].size()). Verifique se o timer da animação é maior ou igual ao número de quadros
    //  da animação corrente. Se for, utilize um laço `while` para decrementar o timer por esse mesmo número
    //  até essa condição seja falsa.

    while((int)mAnimTimer >= mAnimations[mAnimName].size()) {
        mAnimTimer -= (float)mAnimations[mAnimName].size();
    }
}

void DrawAnimatedComponent::SetAnimation(const std::string& name)
{
    // --------------
    // TODO - PARTE 4
    // --------------

    // TODO 3.1 (~2 linhas): salve o nome da animação corrente `name` na variável membro `mAnimName` e
    //  chame a função Update passando delta time igual a zero para reinicializar o timer da animação
    //  `mAnimTimer`.

    mAnimName = name;
    Update(0);

}

void DrawAnimatedComponent::AddAnimation(const std::string& name, const std::vector<int>& spriteNums)
{
    mAnimations.emplace(name, spriteNums);
}

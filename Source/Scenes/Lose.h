//
// Created by User on 15/12/2023.
//

#ifndef DPIBULLETHELL_LOSE_H
#define DPIBULLETHELL_LOSE_H


#include "Scene.h"

class Lose : public Scene{
public:
    Lose(class Game* game);
    void Load();
private:
    class Font* mFont;
};


#endif //DPIBULLETHELL_LOSE_H

//
// Created by User on 15/12/2023.
//

#ifndef DPIBULLETHELL_WIN_H
#define DPIBULLETHELL_WIN_H


#include "Scene.h"

class Win : public Scene{
public:
    Win(class Game* game);
    void Load();
private:

    class Font* mFont;
};


#endif //DPIBULLETHELL_WIN_H

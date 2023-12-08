//
// Created by User on 08/12/2023.
//

#ifndef DPIBULLETHELL_LIMITERMENU_H
#define DPIBULLETHELL_LIMITERMENU_H


#include <string>
#include "Actor.h"

class LimiterMenu : public Actor {
public:
    LimiterMenu(Game* game, std::string& spritePath, int width, int height);
private:
    class DrawSpriteComponent * mDrawComponent;
};


#endif //DPIBULLETHELL_LIMITERMENU_H

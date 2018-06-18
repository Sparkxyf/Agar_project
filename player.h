#ifndef PLAYER_H
#define PLAYER_H

#include "boll.h"

class player: public boll
{
public:
    player();
    void move(D2D1_POINT_2F pos);
};

#endif // PLAYER_H

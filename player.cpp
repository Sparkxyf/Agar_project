#include "player.h"

player::player()
{
}

void player::move(D2D1_POINT_2F pos)
{
    D2D1_POINT_2F p, bp;
    p.x = pos.x-30-x;
    p.y = pos.y-30-y;
    bp.x = x;bp.y = y;
    x += (p.x/sqrt(p.x*p.x+p.y*p.y))*2.5;
    y += (p.y/sqrt(p.x*p.x+p.y*p.y))*2.5;
    if(x <= 0||x >= 640-60)
        x = bp.x;
    if(y <= 0||y >= 480-60)
        y = bp.y;
}

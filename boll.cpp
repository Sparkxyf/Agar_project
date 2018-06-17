#include "boll.h"

boll::boll(): score(10),x(rand()%(640-60)),y(rand()%(480-60)),invicible(90)
{
}

void boll::timeout()
{
    if(invicible)
        invicible--;
}

void boll::paint(ID2D1HwndRenderTarget* render, ID2D1SolidColorBrush* brush, bool pauseing)
{
    if(!pauseing)
        timeout();
    if((invicible/6)%2)
        return;
    D2D1_ELLIPSE e;
    e.point.x = this->x+30;
    e.point.y = this->y+30;
    e.radiusX = e.radiusY = sqrt(score/M_PI);
    render->FillEllipse(&e, brush);
}

bool boll::isColling(const boll& other)
{
    if(&other==this)
        return false;
    D2D1_POINT_2F dist;
    FLOAT dist_len;
    dist.x = fabs(this->x-other.x);
    dist.y = fabs(this->y-other.y);
    dist_len = sqrt(dist.x*dist.x+dist.y*dist.y);
    if(dist_len < sqrt(other.score/M_PI)+sqrt(this->score/M_PI))
        return true;
    else
        return false;
}

void boll::CalcAiMove(const boll& otherbolls)
{
    D2D1_POINT_2F t_pos, v_pos;FLOAT f;
    if(&otherbolls == this)
        return;
    t_pos.x = otherbolls.x - x;
    t_pos.y = otherbolls.y - y;
    v_pos.x = (t_pos.x/sqrt(t_pos.x*t_pos.x+t_pos.y*t_pos.y));
    v_pos.y = (t_pos.y/sqrt(t_pos.x*t_pos.x+t_pos.y*t_pos.y));
    f = t_pos.x*t_pos.x+t_pos.y*t_pos.y;
    f = 1/f;
    if(this->score <= otherbolls.score)
        f *= -this->score;
    else
        f *= otherbolls.score;
    v_pos.x *= f;
    v_pos.y *= f;
    vx += v_pos.x;
    vy += v_pos.y;
}

void boll::Move()
{
    FLOAT tx, ty;
    tx = vx; ty = vy;
    vx = (tx/sqrt(tx*tx+ty*ty))*2;
    vy = (ty/sqrt(tx*tx+ty*ty))*2;
    if(x+vx < 640-60 && x+vx > 0)
        x+=vx;
    if(y+vy < 480-60 && y+vy > 0)
        y+=vy;
}

void boll::addScore(int s)
{
    this->score+=s;
}

int boll::getScore()
{
    return score;
}

void boll::ReInit()
{
    *this = boll();
}

int boll::getInvicible()
{
    return invicible;
}

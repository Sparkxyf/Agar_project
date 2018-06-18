#ifndef BOLL_H
#define BOLL_H

#include <windows.h>
#include <d2d1.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

class boll
{
public:
    boll();
    void timeout();
    void paint(ID2D1HwndRenderTarget* render, ID2D1SolidColorBrush* brush, bool pauseing);
    bool isColling(const boll& other);
    int getInvicible();
    void addScore(int s);
    int getScore();
    virtual void ReInit();
    void ClearVxy(){vx = vy = 0;}
    void CalcAiMove(const boll &otherbolls);
    void Move();
protected:
    FLOAT x, y;
    FLOAT vx,vy;
    int score;
    int invicible;
};

#endif // BOLL_H

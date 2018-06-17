#ifndef DRAW_H
#define DRAW_H

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <algorithm>
#include "boll.h"
#include "player.h"
#include "food.h"

class Draw
{
public:
    Draw(HWND hWnd);
    ~Draw();
    void paint(void);
    void Restart();
    D2D1_POINT_2F pos = D2D1::Point2F();
    bool pauseing = false;
private:
    ID2D1Factory *pFactory = nullptr;
    ID2D1HwndRenderTarget *render = nullptr;
    IDWriteFactory* pWriteFactory;
    IDWriteTextFormat* pFormat;
    food foodlist[30];
    player play;
    boll bolllist[9];
    bool Over = false;
    struct _Brushs
    {
        typedef ID2D1SolidColorBrush *Brush;
        Brush wall, player, otherbolls, text;
    }brushs = {nullptr, nullptr, nullptr, nullptr};
};

#endif // DRAW_H

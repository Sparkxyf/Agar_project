#include "draw.h"

#define BGR(r,g,b) (((r)<<16)|((g)<<8)|(b))

Draw::Draw(HWND hWnd)
{
    HRESULT hr;
    RECT rect;
    GetClientRect(hWnd, &rect);
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
    hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                          D2D1::HwndRenderTargetProperties(hWnd,
                                                                           D2D1::SizeU(640,480))
                                          ,&render);
    if(!SUCCEEDED(hr))
    {
        MessageBoxA(hWnd, "Create RenderTarget Fail!", "ERROR", MB_ICONERROR);
        PostQuitMessage(1);
        return;
    }
    render->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),&brushs.wall);
    render->CreateSolidColorBrush(D2D1::ColorF(BGR(255,0,255)),&brushs.player);
    render->CreateSolidColorBrush(D2D1::ColorF(BGR(255,200,100)),&brushs.otherbolls);
    render->CreateSolidColorBrush(D2D1::ColorF(BGR(255,0,0)),&brushs.text);
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&pWriteFactory)
        );
    pWriteFactory->CreateTextFormat(L"微软雅黑",
                                    nullptr,
                                    DWRITE_FONT_WEIGHT_REGULAR,
                                    DWRITE_FONT_STYLE_NORMAL,
                                    DWRITE_FONT_STRETCH_NORMAL,
                                    72.0f,
                                    L"en-us",
                                    &pFormat
                                    );
    pFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    pFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

template<typename T>
void Release(T* p)
{
    if(p)
        p->Release();
}

Draw::~Draw()
{
    Release(brushs.wall);
    Release(brushs.player);
    Release(brushs.otherbolls);
    Release(brushs.text);
    Release(render);
    Release(pFactory);
    Release(pFormat);
    Release(pWriteFactory);
}

void Draw::paint()
{
    render->BeginDraw();
    render->Clear(D2D1::ColorF(0));
    render->DrawRectangle(D2D1::RectF(30,30,640-30,480-30),brushs.wall);
    if(pauseing)
        goto pauseed;
    for(int i = 0; i < 9; i++)
    {
        if(play.isColling(bolllist[i]) && !bolllist[i].getInvicible())
        {
            if(play.getScore() < bolllist[i].getScore())
                Over = true;
            play.addScore(bolllist[i].getScore());
            bolllist[i].ReInit();
        }
        for(int j = 0; j < 30; j++)
        {
            if(bolllist[i].isColling(foodlist[j]))
            {
                bolllist[i].addScore(foodlist[j].getScore());
                foodlist[j].ReInit();
            }
        }
        for(int j = 0; j < 9; j++)
        {
            if(bolllist[i].isColling(bolllist[j]))
            {
                if(bolllist[i].getScore() >= bolllist[j].getScore())
                {
                    if(bolllist[j].getInvicible())
                    {
                        if(bolllist[i].getInvicible())
                            continue;
                        else
                        {
                            bolllist[j].addScore(bolllist[i].getScore());
                            bolllist[i].ReInit();
                        }
                    }
                    bolllist[i].addScore(bolllist[j].getScore());
                    bolllist[j].ReInit();
                }
                else
                {
                    if(bolllist[i].getInvicible())
                    {
                        if(bolllist[j].getInvicible())
                            continue;
                        else
                        {
                            bolllist[i].addScore(bolllist[j].getScore());
                            bolllist[j].ReInit();
                        }
                    }
                    bolllist[j].addScore(bolllist[i].getScore());
                    bolllist[i].ReInit();
                }
            }
        }
    }
    for(int i = 0; i < 9; i++)
    {
        bolllist[i].ClearVxy();
        bolllist[i].CalcAiMove(play);
        for(int j = 0; j < 30; j++)
        {
            bolllist[i].CalcAiMove(foodlist[j]);
        }
        for(int j = 0; j < 9; j++)
        {
            bolllist[i].CalcAiMove(bolllist[j]);
        }
        bolllist[i].Move();
    }
    for(int i = 0; i < 30; i++)
    {
        if(play.isColling(foodlist[i]))
        {
            play.addScore(foodlist[i].getScore());
            foodlist[i].ReInit();
        }
    }
    play.move(pos);
    pauseed:;
    play.paint(render,brushs.player,pauseing);
    for(int i = 0; i < 9; i++)
    {
        bolllist[i].paint(render,brushs.otherbolls,pauseing);
    }
    for(int i = 0; i < 30; i++)
    {
        foodlist[i].paint(render,brushs.otherbolls,pauseing);
    }
    if(Over)
    {
        render->DrawTextW(L"Game Over!",10,pFormat,D2D1::RectF(0,0,640,480),brushs.text);
    }
    render->EndDraw();
}

void Draw::Restart()
{
    play.ReInit();
    for(int i = 0; i < 9; i++)
    {
        bolllist[i].ReInit();
    }
    Over = false;
}

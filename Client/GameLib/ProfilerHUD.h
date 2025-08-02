// ProfilerHUD.h
#pragma once
#include <d3d8.h>
#include <d3dx8.h>
#include "CD3DFont.h"

class CProfilerHUD {
public:
    CProfilerHUD();
    void BeginFrame();
    void CountDrawCall();
    void CountPolygons(int n);
    void EndFrame(float dt);
    void Render(LPDIRECT3DDEVICE8 device, CD3DFont* pFont);

private:
    int m_drawCalls;
    int m_polyCount;
    float m_fps;
    float m_elapsed;
};
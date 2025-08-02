
#include "StdAfx.h"
// ProfilerHUD.cpp
#include "ProfilerHUD.h"
#include <cstdio>

CProfilerHUD::CProfilerHUD()
{
    m_drawCalls = 0;
    m_polyCount = 0;
    m_fps = 0.0f;
    m_elapsed = 0.0f;
}

void CProfilerHUD::BeginFrame() {
    m_drawCalls = 0;
    m_polyCount = 0;
}

void CProfilerHUD::CountDrawCall() { m_drawCalls++; }
void CProfilerHUD::CountPolygons(int n) { m_polyCount += n; }

void CProfilerHUD::EndFrame(float dt) {
    m_elapsed = dt;
    m_fps = (dt > 0.0f) ? (1.0f / dt) : 0.0f;
}

void CProfilerHUD::Render(LPDIRECT3DDEVICE8 device, CD3DFont* pFont) {
    char buf[128];
    sprintf(buf, "FPS: %.1f\nDraw Calls: %d\nPolygons: %d", m_fps, m_drawCalls, m_polyCount);
    if (pFont)
        pFont->DrawText(10, 10, D3DCOLOR_ARGB(255, 255, 255, 0), buf);
}
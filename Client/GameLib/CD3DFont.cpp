#include "StdAfx.h"
// CD3DFont.cpp
#include "CD3DFont.h"
#include <cstring>
#include <windows.h>

CD3DFont::CD3DFont(const char* strFontName, DWORD dwHeight, DWORD dwFlags)
    : m_pd3dDevice(NULL), m_pD3DXFont(NULL), m_dwFontHeight(dwHeight), m_dwFontFlags(dwFlags)
{
    strncpy(m_strFontName, strFontName, 79);
    m_strFontName[79] = 0;
}

CD3DFont::~CD3DFont()
{
    DeleteDeviceObjects();
}

HRESULT CD3DFont::RestoreDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice)
{
    m_pd3dDevice = pd3dDevice;
    // ---- DirectX8: se creează un HFONT și apoi un D3DXFont! ----
    HFONT hFont = CreateFontA(
        m_dwFontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, m_strFontName
    );
    if (!hFont) return E_FAIL;

    HRESULT hr = D3DXCreateFont(m_pd3dDevice, hFont, &m_pD3DXFont);

    DeleteObject(hFont); // nu mai trebuie după crearea fontului DX
    return hr;
}

HRESULT CD3DFont::InvalidateDeviceObjects()
{
    if (m_pD3DXFont) {
        m_pD3DXFont->OnLostDevice();
    }
    return S_OK;
}

HRESULT CD3DFont::DeleteDeviceObjects()
{
    if (m_pD3DXFont) {
        m_pD3DXFont->Release();
        m_pD3DXFont = NULL;
    }
    return S_OK;
}

HRESULT CD3DFont::DrawText(float x, float y, D3DCOLOR color, const char* strText, DWORD dwFlags)
{
    if (!m_pD3DXFont) return E_FAIL;
    RECT rc;
    rc.left = (int)x;
    rc.top = (int)y;
    rc.right = rc.left + 1024; // width
    rc.bottom = rc.top + 64;
    // --- DirectX8: DrawTextA are 5 parametri, nu 6! ---
    return m_pD3DXFont->DrawTextA(strText, -1, &rc, dwFlags, color);
}

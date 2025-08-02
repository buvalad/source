// CD3DFont.h
#pragma once
#include <d3d8.h>
#include <d3dx8.h>

class CD3DFont
{
public:
    CD3DFont(const char* strFontName, DWORD dwHeight, DWORD dwFlags = 0L);
    ~CD3DFont();

    HRESULT RestoreDeviceObjects(LPDIRECT3DDEVICE8 pd3dDevice);
    HRESULT InvalidateDeviceObjects();
    HRESULT DeleteDeviceObjects();

    HRESULT DrawText(float x, float y, D3DCOLOR color, const char* strText, DWORD dwFlags = 0L);

protected:
    char    m_strFontName[80];
    DWORD   m_dwFontHeight;
    DWORD   m_dwFontFlags;
    LPDIRECT3DDEVICE8  m_pd3dDevice;
    LPD3DXFONT         m_pD3DXFont;
};

#pragma once

#include "GrpBase.h"

class CGraphicIndexBuffer : public CGraphicBase
{
public:
    CGraphicIndexBuffer();
    virtual ~CGraphicIndexBuffer();

    void Destroy();

    // Creează un index buffer gol (pentru un anumit format și count)
    bool Create(int idxCount, D3DFORMAT d3dFmt);

    // Creează direct din fațe, cu suport pentru 16/32bit (implicit 16bit)
    bool Create(int faceCount, TFace* faces, bool use32Bit = false);

    bool CreateDeviceObjects();
    void DestroyDeviceObjects();

    bool Copy(int bufSize, const void* srcIndices);

    bool Lock(void** pretIndices) const;
    void Unlock() const;

    bool Lock(void** pretIndices);
    void Unlock();

    void SetIndices(int startIndex = 0) const;

    LPDIRECT3DINDEXBUFFER8 GetD3DIndexBuffer() const;

    int GetIndexCount() const { return m_iidxCount; }
    DWORD GetBufferSize() const { return m_dwBufferSize; }
    D3DFORMAT GetIndexFormat() const { return m_d3dFmt; }

protected:
    void Initialize();

protected:
    LPDIRECT3DINDEXBUFFER8 m_lpd3dIdxBuf;
    DWORD m_dwBufferSize;
    D3DFORMAT m_d3dFmt;
    int m_iidxCount;
};


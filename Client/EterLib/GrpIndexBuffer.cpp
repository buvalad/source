﻿#include "StdAfx.h"
#include "../eterBase/Stl.h"
#include "GrpIndexBuffer.h"
#include "StateManager.h"

LPDIRECT3DINDEXBUFFER8 CGraphicIndexBuffer::GetD3DIndexBuffer() const
{
	assert(m_lpd3dIdxBuf != NULL);
	return m_lpd3dIdxBuf;
}

void CGraphicIndexBuffer::SetIndices(int startIndex) const
{
	assert(ms_lpd3dDevice != NULL);
	STATEMANAGER.SetIndices(m_lpd3dIdxBuf, startIndex);
}

bool CGraphicIndexBuffer::Lock(void** pretIndices) const
{
	assert(m_lpd3dIdxBuf != NULL);
	return SUCCEEDED(m_lpd3dIdxBuf->Lock(0, 0, (BYTE**)pretIndices, 0));
}

void CGraphicIndexBuffer::Unlock() const
{
	assert(m_lpd3dIdxBuf != NULL);
	m_lpd3dIdxBuf->Unlock();
}

bool CGraphicIndexBuffer::Lock(void** pretIndices)
{
	assert(m_lpd3dIdxBuf != NULL);
	return SUCCEEDED(m_lpd3dIdxBuf->Lock(0, 0, (BYTE**)pretIndices, 0));
}

void CGraphicIndexBuffer::Unlock()
{
	assert(m_lpd3dIdxBuf != NULL);
	m_lpd3dIdxBuf->Unlock();
}

bool CGraphicIndexBuffer::Copy(int bufSize, const void* srcIndices)
{
	assert(m_lpd3dIdxBuf != NULL);

	BYTE* dstIndices;
	if (FAILED(m_lpd3dIdxBuf->Lock(0, 0, &dstIndices, 0)))
		return false;

	memcpy(dstIndices, srcIndices, bufSize);
	m_lpd3dIdxBuf->Unlock();

	return true;
}

// Noua funcție pentru a crea un buffer de indici 16/32 bit
bool CGraphicIndexBuffer::Create(int faceCount, TFace* faces, bool use32Bit)
{
	int idxCount = faceCount * 3;
	m_iidxCount = idxCount;

	D3DFORMAT format = use32Bit ? D3DFMT_INDEX32 : D3DFMT_INDEX16;
	if (!Create(idxCount, format))
		return false;

	if (use32Bit)
	{
		DWORD* dstIndices;
		if (FAILED(m_lpd3dIdxBuf->Lock(0, 0, (BYTE**)&dstIndices, 0)))
			return false;

		for (int i = 0; i < faceCount; ++i, dstIndices += 3)
		{
			dstIndices[0] = faces[i].indices[0];
			dstIndices[1] = faces[i].indices[1];
			dstIndices[2] = faces[i].indices[2];
		}
	}
	else
	{
		WORD* dstIndices;
		if (FAILED(m_lpd3dIdxBuf->Lock(0, 0, (BYTE**)&dstIndices, 0)))
			return false;

		for (int i = 0; i < faceCount; ++i, dstIndices += 3)
		{
			dstIndices[0] = faces[i].indices[0];
			dstIndices[1] = faces[i].indices[1];
			dstIndices[2] = faces[i].indices[2];
		}
	}

	m_lpd3dIdxBuf->Unlock();
	return true;
}

// Suportă ambele tipuri de indici, alocând corect bufferul
bool CGraphicIndexBuffer::CreateDeviceObjects()
{
	return SUCCEEDED(ms_lpd3dDevice->CreateIndexBuffer(
		m_dwBufferSize,
		D3DUSAGE_WRITEONLY,
		m_d3dFmt,
		D3DPOOL_MANAGED,
		&m_lpd3dIdxBuf));
}

void CGraphicIndexBuffer::DestroyDeviceObjects()
{
	safe_release(m_lpd3dIdxBuf);
}

// Creează bufferul, ajustează dimensiunea în funcție de tipul de index
bool CGraphicIndexBuffer::Create(int idxCount, D3DFORMAT d3dFmt)
{
	Destroy();

	m_iidxCount = idxCount;
	m_dwBufferSize = (d3dFmt == D3DFMT_INDEX32) ? sizeof(DWORD) * idxCount : sizeof(WORD) * idxCount;
	m_d3dFmt = d3dFmt;

	return CreateDeviceObjects();
}

void CGraphicIndexBuffer::Destroy()
{
	DestroyDeviceObjects();
}

void CGraphicIndexBuffer::Initialize()
{
	m_lpd3dIdxBuf = NULL;
}

CGraphicIndexBuffer::CGraphicIndexBuffer()
{
	Initialize();
}

CGraphicIndexBuffer::~CGraphicIndexBuffer()
{
	Destroy();
}



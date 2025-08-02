#pragma once

#include "GrpBase.h"

class CGraphicTexture : public CGraphicBase
{
	public:
		virtual bool IsEmpty() const;

		int GetWidth() const;
		int GetHeight() const;

		void SetTextureStage(int stage) const;
		LPDIRECT3DTEXTURE8 GetD3DTexture() const;

		void DestroyDeviceObjects();

	protected:
		CGraphicTexture();
		virtual	~CGraphicTexture();

		void Destroy();
		void Initialize();

	protected:
		bool m_bEmpty;

		int m_width;
		int m_height;

		LPDIRECT3DTEXTURE8 m_lpd3dTexture;
};
//martysama0134's dcf42890919f0da1c0e6dbb7f15bc7ec

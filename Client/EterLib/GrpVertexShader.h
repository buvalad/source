#pragma once

#include "GrpBase.h"

class CVertexShader : public CGraphicBase
{
	public:
		CVertexShader();
		virtual ~CVertexShader();

		void Destroy();
		bool CreateFromDiskFile(const char* c_szFileName, const DWORD* c_pdwVertexDecl);

		void Set();

	protected:
		void Initialize();

	protected:
		DWORD m_handle;
};
//martysama0134's dcf42890919f0da1c0e6dbb7f15bc7ec

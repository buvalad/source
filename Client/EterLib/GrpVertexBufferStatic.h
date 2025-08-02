#pragma once

#include "GrpVertexBuffer.h"

class CStaticVertexBuffer : public CGraphicVertexBuffer
{
	public:
		CStaticVertexBuffer();
		virtual ~CStaticVertexBuffer();

		bool Create(int vtxCount, DWORD fvf, bool isManaged=true);
};
//martysama0134's dcf42890919f0da1c0e6dbb7f15bc7ec

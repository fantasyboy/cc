#include "stdafx.h"
#include "base.h"


base::base(DWORD dwNodeBase): m_dwNodeBase(dwNodeBase)
{

}

base::~base()
{
}


DWORD base::GetNodeBase() const
{
	return m_dwNodeBase;
}

char* base::GetName() const
{
	return nullptr;
}

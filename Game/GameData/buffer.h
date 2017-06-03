#pragma once
#include "base.h"
class buffer :
	public base
{
public:
	buffer(DWORD dwNodeBase);
	~buffer();

	virtual char* GetName() const;

	DWORD GetBufferCount()const;
};


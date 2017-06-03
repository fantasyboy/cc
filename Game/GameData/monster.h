#pragma once
#include "base.h"
#include "BufferService.h"
typedef struct _EM_POINT_3D
{
	float x;
	float z;
	float y;
}EM_POINT_3D , *PEM_POINT_3D;
class monster :
	public base
{
public:
	monster(DWORD dwNodeBase);
	~monster();
	virtual char* GetName() const;
	float GetCurrentHealth()const;
	float GetMaxHealth() const;
	float GetCurrentMagic() const;
	float GetMaxMagic() const;
	PEM_POINT_3D GetPoint()const;
	DWORD GetCamp()const;
	DWORD GetType()const;
	bool BVisableSee()const;
	bool BDead()const;
	float GetDistance(PEM_POINT_3D mons);
	PEM_POINT_3D GetMonsterOrientation()const;
	bool BMoving()const;
	std::shared_ptr<CBufferService> GetBuffService();
private:
	std::shared_ptr<CBufferService> m_bufferService;
};


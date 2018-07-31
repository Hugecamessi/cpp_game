#pragma once
#include "DisplayableObject.h"
class DemoBObject :
	public DisplayableObject
{
public:
	DemoBObject(BaseEngine* pEngine);
	~DemoBObject();
	void Draw();
	void DoUpdate(int iCurrentTime);
};


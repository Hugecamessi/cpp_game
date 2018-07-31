#pragma once
#include "DisplayableObject.h"
#include "GameEngine.h"
#include "JPGImage.h"

class GameWeapon :
	public DisplayableObject
{
public:
	//pType is bullet/weapon(for monster)
	GameWeapon(GameEngine * pEngine);
	~GameWeapon();

	void Draw();
	void DoUpdate(int iCurrentTime);
	void SetSpeed(double wSpeedX, double wSpeedY);
	void SetPosition(int wPossitionX, int wPossitionY);

private:
	ImageData im;
	double wSpeedX;
	double wSpeedY = 0;
	int wPositionX;
	int wPositionY;
};


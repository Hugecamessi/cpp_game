#pragma once
#include "DisplayableObject.h"
#include "GameEngine.h"
#include "JPGImage.h"

class GameAccessories :
	public DisplayableObject
{
public:
	//wrap/arrow for selection in initState/heart/key/door/chest
	GameAccessories(GameEngine* pEngine, int aPositionX, int aPositionY);
	void SetPosition(int iX, int iY);
	void Draw();

	~GameAccessories();

	void SetAState(const char * setState);

private:
	ImageData im;
	enum State { before, after };
	State aState = before;
	int aType;
	int iTick=0;
	int dPositionY;
	int doorOpen = 0;
};


class PlayerBullet :
	public GameAccessories
{
public:
	PlayerBullet(GameEngine * pEngine, int aPositionX, int aPositionY);

	void Draw();
	void setPosition(int iX, int iY);
	void setSpeed(int iSX);
	void DoUpdate(int iCurrentTime);
	double getDistance() { return distance; }

protected:
	ImageData im;
	double distance = 800;
	int bPositionX;
	int bPositionY;
	double bSpeedX;
	const double bSpeedY = 0;
};
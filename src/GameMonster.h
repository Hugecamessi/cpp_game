#pragma once
#include "header.h"
#include "templates.h"
#include "DisplayableObject.h"
#include "GameEngine.h"
#include "JPGImage.h"
#define air 1
#define ground 2
#define bird 3

class GameMonster :
	public DisplayableObject
{
public:
	GameMonster::GameMonster(GameEngine * pEngine, int iID, int iType
		, int initPositionX, int initPositionY);
	
	~GameMonster();

	void SetSpeed(double dSX, double dSY);
	void Draw();

	void DoUpdate(int iCurrentTime);

protected:
	GameEngine * m_pMainEngine;
	enum State { left, right, walk, attack, dead};
	State mDirection = right;
	State mState = walk;
	ImageData im_left, im_right;
	int mType;
	int mID;
	int deadPic = 0;
	//mPositionX is to record the position of the right edge of the pic
	double mPositionX = 64;
	double mPositionY = 64;
	double mSpeedX = 1;
	double mSpeedY = 0;
	double initialmSpeedX = 1;
	double initialmSpeedY = 0;
	double initialmPositionX;
	double initialmPositionY;

public:
	void GameMonster::SetMonsterState(const char* setState);
};


class GameMonsterBird:
	public GameMonster
{
public:
	GameMonsterBird(GameEngine * pEngine, int iID, int iType, int iSize, int initPositionX, int initPositionY);

	void Draw();
	void setPosition(int iX, int iY);
	void DoUpdate(int iCurrentTime);
	double getDistance() { return distance; }

protected:
	ImageData im_birdleft, im_birdright;
	double distance = 800;
};

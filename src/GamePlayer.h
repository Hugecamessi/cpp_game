#pragma once
#include "DisplayableObject.h"
#include "GameEngine.h"

class GameEngine;
class GameTileManager;

class GamePlayer :
	public DisplayableObject
{
public:
	GamePlayer(GameEngine* pEngine, int pType, const char* szLabel, int iXLabelOffset, int iYLabelOffset);
	~GamePlayer();

	void Draw();
	void DoUpdate(int iCurrentTime);
	void SetLabelVisible();

	int getPlayerLife() { return pLife; }
	int getPlayerKey() { return pKey; }
	void resetKey() { pKey = 0; }
	int getPlayerDir() { return pDir; }
	void setPlayerLife(int value);
	void setPosition(double dX, double dY);
	void setMonsterKilled(int value);


private:
	enum State { left, right, front, back };
	State pState = front;
	// 1 represents right, 2 represents left
	int pDir=0;
	ImageData im;
	GameEngine * m_pMainEngine;
	int pcurrState;
	int pType;
	int pKey=0;
	//pLife is 0 - 3
	int pLife = 3;
	int pHeart = 0;
	int pTime;
	// Label to apply
	const char* pLabel;
	enum pLabelState {visible, invisible};
	pLabelState pLState = invisible;
	double playerPositionX;
	double playerPositionY;
};


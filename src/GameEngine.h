#pragma once
#include "BaseEngine.h"
#include "GameTileManager.h"
#include "JPGImage.h"
#include <fstream>
using namespace std;

class GameObject;
class GamePlayer;
class GameMonster;
class GameMonsterBird;
class GameAccessories;
class PlayerBullet;
enum State { stateInit, stateMain, statePaused
	, stateFinished, stateRecord, stateFailed};

class GameEngine :
	public BaseEngine
{
public:
	GameEngine();
	~GameEngine();
	void SetupBackgroundBuffer();
	void MouseDown(int iButton, int iX, int iY);
	void KeyDown(int iKeyCode);
	int InitialiseObjects();
	void GameAction();
	void UnDrawStrings();
	void DrawStringsOnTop();
	void DrawStringsUnderneath();

	GameTileManager* GetTileManager() { return &m_oTiles; }
	State getState() { return m_state; }
private:
	GameTileManager m_oTiles;

public:
	ifstream fileMap, fileRecordRead;
	ofstream fileRecordWrite;
	int m_iPauseStarted = 0;
	int startTime = 0;
	int mapWidth;
	int mapHeight;
	int tileWidth;
	int tileHeight;
	char data[100][100];
	int monsterKilled = 1;
	
private:
	ImageData im, im_characters, im_temp, im_exit, im_background, im_double, im_MainBG;
	State m_state;
	int keyX;
	int keyY;
	int gameTime=0;
	int totalTime = 0;
	int saveTimes = 0;
	int getPlayerLife = 0;
	int saveLifeTimes = 0;
	int offset = 0;
	char pName[10] = {};
	int pNameLength = 0;

protected:
	// Three member variables, to store pointers to the three balls
	// Only the pointers are created with the main object - not anything that they may point to
	// These have to be initialised in the initialisation list
	GameObject* yellowBird;
	GameMonsterBird* brownBird;
	GamePlayer* player;
	GameMonster* groundMonster;
	GameMonster* airMonster1;
	GameMonster* airMonster2;
	GameMonster* airMonster3;
	PlayerBullet* bullet;
	GameAccessories* flowerStart;
	GameAccessories* flowerRecord;
	GameAccessories* flowerExit;	

public:
	void MouseMoved(int iX, int iY);
};


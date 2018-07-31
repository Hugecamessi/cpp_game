#include "header.h"
#include "templates.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "GamePlayer.h"
#include "GameMonster.h"
#include "GameWeapon.h"
#include "GameAccessories.h"
#include "JPGImage.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#define air 1
#define ground 2
#define bird 3
#define door 3
using namespace std;

GameEngine::GameEngine()
	: m_state(stateInit) // NEW
{
	fileMap.open("docs/map.txt");
	if (!fileMap) {
		printf("Error, Cannot open the file!");
		exit(0);
	}
	char ch = 'a';
	mapHeight = 0;
	while (ch != EOF)
	{
		ch = fileMap.get();
		int tempx = 0;
		while (ch != '\n' && ch != EOF) {
			data[mapHeight][tempx] = ch;
			tempx++;
			ch = fileMap.get();
		}
		mapWidth = tempx;
		mapHeight++;
	}
	fileMap.close();
	im_MainBG.LoadImage("img/MainBG.png");

	// Specify how many tiles Width and high
	tileWidth = mapWidth;
	tileHeight = mapHeight;
		// Specify how many tiles Width and high
	m_oTiles.SetSize(tileWidth, tileHeight);
	// Set up the tiles
	for (int x = 0; x < tileWidth; x++)
		for (int y = 0; y < tileHeight; y++)
			m_oTiles.SetValue(x, y, data[y][x] - 'a');

	m_iPauseStarted = 0;
}

GameEngine::~GameEngine()
{
}

void GameEngine::SetupBackgroundBuffer()
{
	// Draw an image loaded from a file.
	
	// Load the image file into an image object - at the normal size
	im.LoadImage("img/constructors.png");
	im_background.LoadImage("img/initbg.png");
	im_characters.LoadImage("img/Hiker.png");
	im_double.ResizeFrom(&im, 1600, 2560, true);
	// NEW SWITCH
	switch (m_state)
	{
	case stateInit: // Reload the level data
		FillBackground(0x33ccff);
		im_background.RenderImageWithMask(this->GetBackground(),
			0, 0,
			0, 0,
			800, 600);
		
		for (int i = 0; i < GetWindowWidth() / 16; i++)
			for (int j = 0; j < 3; j++) {
				if (j == 2) {
					im.RenderImageWithMask(this->GetBackground(),
						256, 60,
						i * 16, GetWindowHeight() - 16 * 3,
						16, 16);
				}
				else {
					im.RenderImageWithMask(this->GetBackground(),
						256, 76,
						i * 16, GetWindowHeight() - 16 * (j + 1),
						16, 16);
				}
			}
		
		//Trees
		im_double.RenderImageWithMask(this->GetBackground(), 200, 1280, 0, 500, 200, 64);
		// wooden box
		im.RenderImageWithMask(this->GetBackground(), 352, 592, 70, 550,16, 16);
		// silver box
		im.RenderImageWithMask(this->GetBackground(), 368, 592, 200, 570, 16, 16);
		// golden box
		im.RenderImageWithMask(this->GetBackground(), 384, 592, 150, 580, 16, 16);
		// boy
		im_characters.RenderImageWithMask(this->GetBackground(), 0, 0, 350, 90, im_characters.GetWidth(), im_characters.GetHeight());

		return;
	case stateMain:
		FillBackground(0x000000);
		im_MainBG.RenderImage(this->GetBackground(), 0, 0, 0, 0, im_background.GetWidth(), im_background.GetHeight());
		m_oTiles.SetBaseTilesPositionOnScreen(0, 90);
		m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, tileWidth - 1, tileHeight - 1);
		break; // Drop out to the complicated stuff
	case statePaused:
		FillBackground(0x000000);
		im.LoadImage("BackgroundClouds.jpg");
		break; // Drop out to the complicated stuff
	case stateFinished:
		FillBackground(0x000000);
		im_background.RenderImage(this->GetBackground(), 0, 0, 0, 0, im_background.GetWidth(), im_background.GetHeight());
		break;
	case stateFailed:
		FillBackground(0x000000);
		im_background.RenderImage(this->GetBackground(), 0, 0, 0, 0, im_background.GetWidth(), im_background.GetHeight());
		break;
	case stateRecord:
		FillBackground(0x000000);
		im_background.RenderImage(this->GetBackground(), 0, 0, 0, 0, im_background.GetWidth(), im_background.GetHeight());
		break;
	} // End switch
}


void GameEngine::UnDrawStrings()
{
	CopyBackgroundPixels(0/*X*/, 0/*Y*/, 799, 599/*Height*/);
}

void GameEngine::MouseDown(int iButton, int iX, int iY)
{
	//printf("Position: %d, %d\n", iX, iY);
	if (m_state != stateInit && m_state != stateFinished) {
		if (iX >= 598 && iX <= 655 && iY >= 28 && iY <= 55)
			SetExitWithCode(0);
	}
	
	switch (m_state)
	{
	case stateInit:
		for (int i = 0; i < 3; i++)
			GetDisplayableObject(i)->SetVisible(false);
		if (iX > 150 && iX < 240 && iY>200 && iY < 230) {
			brownBird->setPosition(100+rand() % 700, 100+ rand() % 400);
			m_state = stateMain;
			for (int i = 3; i < 9; i++)
				GetDisplayableObject(i)->SetVisible(true);
			flowerExit->SetPosition(555, 28);
			flowerExit->SetVisible(false);
		}
		if (iX > 150 && iX < 270 && iY>300 && iY < 330) {
			m_state = stateRecord;
			for (int i = 0; i < 10; i++)
				GetDisplayableObject(i)->SetVisible(false);
		}
		if (iX > 150 && iX < 210 && iY>400 && iY < 430)
			SetExitWithCode(0);

		SetupBackgroundBuffer();
		Redraw(true);
		startTime = GetTime();
		break;
	case stateMain:
		player->SetLabelVisible();
		break;
	case stateFinished:
		if (iX >= 195 && iX <= 280 && iY >= 300 && iY <= 325 && pNameLength != 0)
			saveTimes++;

		if (iX >= 598 && iX <= 655 && iY >= 28 && iY <= 55) {
			if (saveTimes > 0) {
				fileRecordWrite.open("docs/record.txt", ios_base::out | ios_base::app);
				if (!fileRecordWrite) {
					printf("Error, Cannot open the file!");
					SetExitWithCode(0);
				}
				//name, time, life, monsterKilled 
				fileRecordWrite << pName << " ";
				fileRecordWrite << getPlayerLife << " ";
				fileRecordWrite << gameTime << " ";
				fileRecordWrite << monsterKilled << "\n";
				fileRecordWrite.close();
			}
			SetExitWithCode(0);
		}	
		break;
	case stateRecord:
		if (iX >= 45 && iX <= 165 && iY >= 28 && iY <= 55) {
			m_state = stateInit;
			DestroyOldObjects();
			SetupBackgroundBuffer();
			InitialiseObjects();
		}
		break;
	case stateFailed:
		if (iX >= 197 && iX <= 254 && iY >= 200 && iY <= 225)
		{
			m_state = stateInit;
			SetupBackgroundBuffer();
			InitialiseObjects();
			Redraw(true);
		}
		else if (iX >= 393 && iX <= 450 && iY >= 200 && iY <= 225)
			SetExitWithCode(0);
		break;
	}
	Redraw(true);
}




void GameEngine::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE)
		SetExitWithCode(0);

	switch (m_state)
	{
	case stateMain:
		if (iKeyCode == SDLK_SPACE) {
			m_state = statePaused;
			m_iPauseStarted = GetTime();
			Redraw(true);
		}
		if (iKeyCode == SDLK_b) {
			delete GetDisplayableObject(9);
			PlayerBullet* bullet = new PlayerBullet(this, player->GetXCentre(), player->GetYCentre() - 16);
			StoreObjectInArray(9, bullet);
			if (player->getPlayerDir() == 1)
				bullet->setSpeed(3);
			else
				bullet->setSpeed(-3);

			bullet->setPosition(player->GetXCentre(), player->GetYCentre()-16);
			bullet->SetVisible(true);
		}
		break;
	case statePaused:
		if (iKeyCode == SDLK_SPACE) {
			m_state = stateMain;
			IncreaseTimeOffset(m_iPauseStarted - GetTime());
			//printf("timeoffset: %d", GetTimeOffset());
			//SetupBackgroundBuffer();
			Redraw(true);
		}
		break;
	case stateFinished:
		if (iKeyCode == SDLK_BACKSPACE && pNameLength != 0) {
			pNameLength=pNameLength-1;
			pName[pNameLength] = NULL;
		}
		else if (pNameLength < 9 && iKeyCode != SDLK_SPACE && iKeyCode != SDLK_KP_ENTER) {
			pName[pNameLength] = iKeyCode;
			pNameLength++;
		}
		else {
			break;
		}

		SetupBackgroundBuffer();
		Redraw(true); 
		break;
	} 
}

int GameEngine::InitialiseObjects()
{
	DrawableObjectsChanged();
	DestroyOldObjects();
	CreateObjectArray(11);

	flowerStart = new GameAccessories(this, 105, 197);
	flowerRecord = new GameAccessories(this, 105, 297);
	flowerExit = new GameAccessories(this, 105, 397);
	
	player = new GamePlayer(this, 0, "Alen", -10, 160);

	groundMonster = new GameMonster(this, 0, ground, -10, 478);
	airMonster1 = new GameMonster(this, 1, air, -10, 323);
	airMonster2 = new GameMonster(this, 2, air, 750, 262);
	airMonster3 = new GameMonster(this, 3, air, 698, 390);

	yellowBird = new GameObject(this, 1, 1, 64, 0, 200 + rand() % 200);
	yellowBird->SetSpeed(1.1, 1.0);
	brownBird = new GameMonsterBird(this, 2, bird, 64, 400, 200 + rand() % 200);
	brownBird->SetSpeed(1.0,1.0);
	bullet = new PlayerBullet(this, player->GetXCentre(), player->GetYCentre()-16);
	
	
	StoreObjectInArray(0, flowerStart);
	StoreObjectInArray(1, flowerRecord);
	StoreObjectInArray(2, flowerExit); 
	StoreObjectInArray(3, groundMonster);
	StoreObjectInArray(4, airMonster1);
	StoreObjectInArray(5, airMonster2);
	StoreObjectInArray(6, airMonster3);
	StoreObjectInArray(7, brownBird);
	StoreObjectInArray(8, player);
	StoreObjectInArray(9, bullet);
	StoreObjectInArray(10, NULL);
	return 0;

}

void GameEngine::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;
	SetTimeToAct(20);
	if (player->getPlayerLife() == 0 && saveLifeTimes == 0) {
		m_state = stateFailed;
		gameTime = 0;
		player->setPlayerLife(-player->getPlayerLife());
		player->resetKey();
		Redraw(true);
	}

	// NEW SWITCH - different from the base class
	switch (m_state)
	{
	case stateInit:
		UpdateAllObjects(GetTime());
		break;
	case stateMain:
		if (brownBird->getDistance() < 40) {
			player->setPosition(-10, 160);
			player->setPlayerLife(-1);
			brownBird->setPosition(600, 10);
		}
		if (player->getPlayerKey() > 0 && player->getPlayerLife() > 0 && !(player->IsVisible())) {
			m_state = stateFinished;
			for (int i = 0; i < 4; i++) {
				if (!GetDisplayableObject(i + 3)->IsVisible())
					monsterKilled++;
			}
			for (int i = 0; i < 8; i++)
				GetDisplayableObject(i)->SetVisible(false);
			if (saveLifeTimes == 0) {
				saveLifeTimes++;
				getPlayerLife = player->getPlayerLife();
			}
			totalTime = (GetModifiedTime() - startTime) / 1000;
			SetupBackgroundBuffer();
			Redraw(true);
		}	
		

		UpdateAllObjects(GetTime());
		break;
	case statePaused:
		break;
	case stateFailed:
		DestroyOldObjects();
		break;
	case stateFinished:
		break;
	}
}

void GameEngine::DrawStringsOnTop()
{
	if (m_state != stateInit)
	{	
		char buf1[128], buf2[128];
		
		if (m_state == stateFailed) {
			gameTime = 0;
		}
		else if (m_state == stateFinished) {
			gameTime = totalTime;
		}
		else
		{
			gameTime = (GetModifiedTime() - startTime) / 1000;
		}
		sprintf(buf1, "Exit");
		DrawForegroundString(600, 30, buf1, 0XFFFFFF, NULL);

		if (m_state != stateRecord) {
			sprintf(buf1, "Life: %d", player->getPlayerLife());
			DrawForegroundString(50, 30, buf1, 0XFFFFFF, NULL);
			sprintf(buf1, "Key: %d", player->getPlayerKey());
			DrawForegroundString(180, 30, buf1, 0XFFFFFF, NULL);
			sprintf(buf2, "Time: %d", gameTime);
			DrawForegroundString(300, 30, buf2, 0xFFFFFF, NULL);
		}				
	}
	if (m_state == stateRecord) {
		char buf1[128], buf2[128];
		sprintf(buf1, "<< Back");
		DrawForegroundString(50, 30, buf1, 0XFFFFFF, NULL);
		sprintf(buf1, "Name");
		DrawForegroundString(50, 100, buf1, 0XFFFFFF, NULL);
		sprintf(buf1, "Life Remain");
		DrawForegroundString(220, 100, buf1, 0XFFFFFF, NULL);
		sprintf(buf2, "Time");
		DrawForegroundString(470, 100, buf2, 0xFFFFFF, NULL); 
		sprintf(buf2, "Killed Monster");
		DrawForegroundString(570, 100, buf2, 0xFFFFFF, NULL);

		fileRecordRead.open("docs/record.txt");
		if (!fileRecordRead) {
			printf("Error, Cannot open the file!");
			SetExitWithCode(0);
		}
		string str;
		vector<string> records;
		while (fileRecordRead >> str)
			records.push_back(str);

		const int iWordCount = records.size();
		for (int i = 0; i < iWordCount / 4; i++)
			for (int j = 0; j < 4; j++)
				DrawForegroundString(50 + 215 * j, 130 + 40 * i, &records[i * 4 + j][0], 0x000000, NULL);
		fileRecordRead.close();
	}
}

void GameEngine::DrawStringsUnderneath()
{
	// NEW SWITCH
	switch (m_state)
	{
	case stateInit:
		DrawForegroundString(100, 60, "Explore The Jungle", 0x0, NULL); //GetFont("AncientStory.ttf", 50)
		DrawForegroundString(150, 200, "START", 0x0, NULL);
		DrawForegroundString(150, 300, "RECORD", 0x0, NULL);
		DrawForegroundString(150, 400, "EXIT", 0x0, NULL);
		break;
	case stateMain:
		break;
	case statePaused:
		DrawForegroundString(200, 300, "Paused. Press SPACE to continue", 0xffffff, NULL);
		break;
	case stateFailed:
		DrawForegroundString(200, 150, "Failed, start again!", 0xffff00);
		DrawBackgroundString(200, 200, "Yes", 0xffff00);
		DrawBackgroundString(400, 200, "No", 0xffff00);
		break;
	case stateFinished:
		DrawForegroundString(200, 150, "Congratulations!", 0xffff00);
		DrawForegroundString(200, 200, "Record your name!", 0xffff00);
		DrawForegroundRectangle(200, 250, 500, 280, 0x95DFF0);
		DrawForegroundString(203, 253, pName, 0xFFFFFF, NULL);
		flowerRecord->SetPosition(180,300);
		DrawForegroundString(200, 300, "SAVE", 0xffff00);
		break;
	}
}

void GameEngine::MouseMoved(int iX, int iY)
{
	switch (m_state)
	{
	case stateInit:
		if (iX > 140 && iX < 275 && iY>195 && iY < 230) {
			flowerStart->SetVisible(true);
		}
		else if (iX > 140 && iX < 275 && iY>295 && iY < 330)
			flowerRecord->SetVisible(true);
		else if (iX > 140 && iX < 275 && iY>395 && iY < 430)
			flowerExit->SetVisible(true);
		else {
			flowerStart->SetVisible(false);
			flowerRecord->SetVisible(false);
			flowerExit->SetVisible(false);
		}		
		Redraw(true);
		break;
	case stateFailed:
		if (iX >= 598 && iX <= 655 && iY >= 28 && iY <= 55)
			flowerExit->SetVisible(true);
		else if (iX >= 197 && iX <= 254 && iY >= 200 && iY <= 225)
			flowerStart->SetVisible(true);
		else if (iX >= 393 && iX <= 450 && iY >= 200 && iY <= 225)
			flowerRecord->SetVisible(true);
		else {
			flowerStart->SetVisible(false);
			flowerExit->SetVisible(false);
			flowerRecord->SetVisible(false);		
		}
		break;
	case stateFinished:
		break;
	}
}
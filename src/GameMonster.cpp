#include "header.h"
#include "templates.h"
#include "GameEngine.h"
#include "GameMonster.h"
#include "JPGImage.h"
#define air 1
#define ground 2
#define bird 3

GameMonster::GameMonster(GameEngine * pEngine, int iID, int iType, int initPositionX, int initPositionY)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, mID(iID)
	, mType(iType)
	, initialmPositionX(initPositionX)
	, initialmPositionY(initPositionY)
{
	mState = walk;
	if (mType == air) {
		im_right.LoadImage("img/monster1right.png");
		im_left.LoadImage("img/monster1left.png");
	}
	else {
		im_right.LoadImage("img/monster2_right.png");
		im_left.LoadImage("img/monster2_left.png");
	}
	
	if (initPositionX < 400) {
		mDirection = right;
		mSpeedX = 1;
	}
	else {
		mDirection = left;
		mSpeedX = -1;
	}		
		
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the monster size as both height and width
	m_iDrawWidth = 32;
	m_iDrawHeight = 32;
	// Current and previous coordinates for the object - set them the same initially
	m_iPreviousScreenX = m_iCurrentScreenX = initPositionX;
	m_iPreviousScreenY = m_iCurrentScreenY = initPositionY;
	// And make it visible
	SetVisible(false);
}

GameMonster::~GameMonster()
{
}

void GameMonster::SetSpeed(double dSX, double dSY)
{
	mSpeedX = dSX;
}

void GameMonster::SetMonsterState(const char* setState)
{
	if (setState[0] == 'w') {
		mState = walk;
	}
	else if (setState[0] == 'a') {
		mState = attack;
	}
	else if (setState[0] == 'd') {
		mState = dead;
	}
}

void GameMonster::Draw()
{
	if (!IsVisible() || deadPic > 28) {
		SetVisible(false);
		return;
	}
	int iTick = GetEngine()->GetTime() / 100; // 1 per 20ms
	int actionNum = 0;
	int mPositionY;

	switch (mState)
	{
	case walk:
		mPositionY = 64;
		if (mType = ground)
			actionNum = 4;
		else
			actionNum = 5;
		break;
	case attack:
		mPositionY = 128;
		if (mType = ground)
			actionNum = 4;
		else
			actionNum = 6;
		break;
	case dead:
		mPositionY = 192;
		actionNum = 7;
		deadPic++;
		
		break;
	}
	int mtempX = iTick % actionNum;	


	switch (mDirection)
	{
	case right:
		im_right.RenderImageWithMask(GetEngine()->GetForeground()
			, mtempX * 64, mPositionY
			, m_iCurrentScreenX, m_iCurrentScreenY
			, 64, 64);
		break;
	case left:
		im_left.RenderImageWithMask(GetEngine()->GetForeground()
			, im_left.GetWidth() - (mtempX + 1) * 64, mPositionY
			, m_iCurrentScreenX, m_iCurrentScreenY
			, 64, 64);
		break;
	}

	StoreLastScreenPositionForUndraw();
}

void GameMonster::DoUpdate(int iCurrentTime)
{
	mPositionX += mSpeedX;
	if (mSpeedX > 0)
		mDirection = right;
	else
		mDirection = left;
		
	switch(mID)
	{
	case 0:
		if ((mPositionX + initialmPositionX) < initialmPositionX-10
			|| (mPositionX + initialmPositionX) > (GetEngine()->GetWindowWidth() - 60))
			mSpeedX = -mSpeedX;
		break;
	case 1:
		if ((mPositionX + initialmPositionX) < initialmPositionX-10
			|| (mPositionX + initialmPositionX) > 250)
			mSpeedX = -mSpeedX;
		break;
	case 2:
		if ((mPositionX + initialmPositionX) < 330)
			mSpeedX = -mSpeedX;
		if ((mPositionX + initialmPositionX > 750) && mDirection==right)
			mSpeedX = -mSpeedX;
		break;
	case 3:
		if ((mPositionX + initialmPositionX) < 490)
			mSpeedX = -mSpeedX;
		if ((mPositionX + initialmPositionX > 700) && mDirection == right)
			mSpeedX = -mSpeedX;
		break;
	}

	double bulletX = m_pMainEngine->GetDisplayableObject(9)->GetXCentre();
	double bulletY = m_pMainEngine->GetDisplayableObject(9)->GetYCentre();
	double playerX = m_pMainEngine->GetDisplayableObject(8)->GetXCentre();
	double playerY = m_pMainEngine->GetDisplayableObject(8)->GetYCentre();
	for (int i = 0; i < 4; i++) {
		double monsterX = m_pMainEngine->GetDisplayableObject(i+3)->GetXCentre();
		double monsterY = m_pMainEngine->GetDisplayableObject(i + 3)->GetYCentre();
		double distance2 = abs(bulletX - monsterX);

		printf("distance2 %lf\n", abs(bulletY - monsterY));
		if (distance2 < 15.0 && abs(bulletY - monsterY)<25.0 && m_pMainEngine->GetDisplayableObject(9)->IsVisible())
		{
			printf("here!\n");
			m_pMainEngine->GetDisplayableObject(i + 3)->SetVisible(false);
			m_pMainEngine->GetDisplayableObject(9)->SetVisible(false);
		}
	}

	
	
	// Work out current position
	m_iCurrentScreenX = initialmPositionX + mPositionX;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}


/** Constructor */

GameMonsterBird::GameMonsterBird(GameEngine * pEngine, int iID, int iType, int iSize, int initPositionX, int initPositionY)
	: GameMonster(pEngine, iID, iType, initPositionX, initPositionY)
{
	if (rand() % 2 == 0) {
		im_birdright.LoadImage("img/animals/yellowbird64right.png");
		im_birdleft.LoadImage("img/animals/yellowbird64left.png");
	}
	else {
		im_birdright.LoadImage("img/animals/brownbird64right.png");
		im_birdleft.LoadImage("img/animals/brownbird64left.png");
	}

	mSpeedX = 1;
	mSpeedY = 1;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = iSize;
	m_iDrawHeight = iSize;
	// Current and previous coordinates for the object - set them the same initially
	m_iPreviousScreenX = m_iCurrentScreenX = initPositionX;
	m_iPreviousScreenY = m_iCurrentScreenY = initPositionY;
	// And make it visible
	SetVisible(true);
}

void GameMonsterBird::Draw()
{
	if (!IsVisible())
		return;
	int iTick = GetEngine()->GetTime() / 100; // 1 per 20ms
	int im_Y = iTick % 4;

	if (mSpeedX > 0)
		mDirection = right;
	else
		mDirection = left;

	switch (mDirection)
	{
	case right:
		im_birdright.RenderImageWithMask(GetEngine()->GetForeground()
			, im_birdright.GetWidth(), im_Y * im_birdright.GetHeight() / 4
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im_birdright.GetWidth(), im_birdright.GetHeight() / 4 - 1);
		break;
	case left:
		im_birdleft.RenderImageWithMask(GetEngine()->GetForeground()
			, im_birdleft.GetWidth(), im_Y * im_birdleft.GetHeight() / 4
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im_birdleft.GetWidth(), im_birdleft.GetHeight() / 4 - 1);
		break;
	}
	StoreLastScreenPositionForUndraw();
}

void GameMonsterBird::setPosition(int iX, int iY)
{
	mPositionX = m_iPreviousScreenX = m_iCurrentScreenX = iX;
	mPositionY= m_iPreviousScreenY = m_iCurrentScreenY = iY;
}

void GameMonsterBird::DoUpdate(int iCurrentTime)
{
	if (!IsVisible()) {
		mPositionX = m_iPreviousScreenX = m_iCurrentScreenX = 0;
		mPositionY = m_iPreviousScreenY = m_iCurrentScreenY = 0;
		return;
	}
	mPositionX += (int)mSpeedX;
	mPositionY += (int)mSpeedY;
	switch (m_pMainEngine->getState()) 
	{
	default:
		if ((mPositionX + m_iStartDrawPosX) < 0)
		{
			mPositionX = -m_iStartDrawPosX;
			if (mSpeedX < 0)
				mSpeedX = -mSpeedX;
		}

		if ((mPositionX + m_iStartDrawPosX + m_iDrawWidth) >(GetEngine()->GetWindowWidth() - 1))
		{
			mPositionX = GetEngine()->GetWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			if (mSpeedX > 0)
				mSpeedX = -mSpeedX;
		}

		if ((mPositionY + m_iStartDrawPosY) < 0)
		{
			mPositionY = -m_iStartDrawPosY;
			if (mSpeedY < 0)
				mSpeedY = -mSpeedY;
		}

		if ((mPositionY + m_iStartDrawPosY + m_iDrawHeight) >(GetEngine()->GetWindowHeight() - 1))
		{
			mPositionY = GetEngine()->GetWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			if (mSpeedY > 0)
				mSpeedY = -mSpeedY;
		}
		break;
	case stateMain:
		double playerX = m_pMainEngine->GetDisplayableObject(8)->GetXCentre();
		double playerY = m_pMainEngine->GetDisplayableObject(8)->GetYCentre();
		double birdX = GetXCentre();
		double birdY = GetYCentre();
		distance = sqrt((playerX - birdX)*(playerX - birdX) + (playerY - birdY)*(playerY - birdY));
		double distanceX = (playerX - birdX);
		double distanceY = (playerY - birdY);
				
		mSpeedX = 2*distanceX / distance;
		mSpeedY = 2*distanceY / distance;

		break;
	}

	// Work out current position
	m_iCurrentScreenX = (int)(mPositionX + 0.5);
	m_iCurrentScreenY = (int)(mPositionY + 0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
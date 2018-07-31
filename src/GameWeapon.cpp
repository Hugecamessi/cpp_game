#include "header.h"
#include "templates.h"
#include "GameEngine.h"
#include "GameWeapon.h"
#include "JPGImage.h"

GameWeapon::GameWeapon(GameEngine* pEngine)
	: DisplayableObject(pEngine)
{
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 0;
	m_iCurrentScreenY = m_iPreviousScreenY = 0;

	SetVisible(false);
}


GameWeapon::~GameWeapon()
{
}



void GameWeapon::Draw()
{
	if (!IsVisible())
		return;

	GetEngine()->DrawForegroundOval(m_iCurrentScreenX - 4, m_iCurrentScreenY - 4,
		m_iCurrentScreenX + 3, m_iCurrentScreenY + 3, 0x8B4513);
	
	StoreLastScreenPositionForUndraw();
}

void GameWeapon::DoUpdate(int iCurrentTime)
{
	m_iCurrentScreenX = (int)(wPositionX+0.5);
	m_iCurrentScreenY = (int)(wPositionY + 0.5);

	RedrawObjects();
}

void GameWeapon::SetSpeed(double iX, double iY)
{
	wSpeedX = iX;
	wSpeedY = iY;
}

void GameWeapon::SetPosition(int iX, int iY)
{
	wPositionX = iX;
	wPositionY = iY;
}
#include "header.h"
#include "templates.h"
#include "GameEngine.h"
#include "GameAccessories.h"
#include "JPGImage.h"

GameAccessories::GameAccessories(GameEngine * pEngine,int aPositionX, int aPositionY)
	:DisplayableObject(pEngine)
{
	im.LoadImage("img/flower.png");		
	
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = aPositionX;
	m_iCurrentScreenY = m_iPreviousScreenY = aPositionY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 64;
	m_iDrawHeight = 64;
	// And make it visible
	SetVisible(false);
}

GameAccessories::~GameAccessories()
{
}


void GameAccessories::SetAState(const char* setState)
{
	if (setState[0] == 'b') {
		aState = before;
	}
	else if (setState[0] == 'a') {
		aState = after;
	}
}

void GameAccessories::SetPosition(int iX, int iY)
{
	m_iCurrentScreenX = m_iPreviousScreenX = iX;
	m_iCurrentScreenY = m_iPreviousScreenY = iY;
}

void GameAccessories::Draw()
{
	if (!IsVisible())
		return;
	
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, im.GetWidth(), im.GetHeight());
		

	StoreLastScreenPositionForUndraw();
}



/** Constructor */
PlayerBullet::PlayerBullet(GameEngine * pEngine, int aPositionX, int aPositionY)
	: GameAccessories(pEngine, aPositionX, aPositionY)
{
	im.LoadImage("img/bullet.png");
	// The object coordinate will be the top left of the object
	m_iCurrentScreenX = m_iPreviousScreenX = aPositionX;
	m_iCurrentScreenY = m_iPreviousScreenY = aPositionY;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 20;
	m_iDrawHeight = 20;
	// And make it visible
	SetVisible(false);
}

void PlayerBullet::Draw()
{
	if (!IsVisible())
		return;
	/*
	GetEngine()->DrawForegroundOval(m_iCurrentScreenX - 4, m_iCurrentScreenY - 4,
		m_iCurrentScreenX + 3, m_iCurrentScreenY + 3, 0x8B4513);
	*/
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX, m_iCurrentScreenY, im.GetWidth(), im.GetHeight());

	StoreLastScreenPositionForUndraw();
}

void PlayerBullet::setPosition(int iX, int iY)
{
	bPositionX = m_iPreviousScreenX = m_iCurrentScreenX = iX;
	bPositionY = m_iPreviousScreenY = m_iCurrentScreenY = iY+10;
}

void PlayerBullet::setSpeed(int iSX)
{
	bSpeedX = iSX;
}

void PlayerBullet::DoUpdate(int iCurrentTime)
{
	if (bPositionX < -10 || bPositionX > 820) {
		SetVisible(false);
		bPositionX = 0;
		return;
	}

	bPositionX += bSpeedX;
	bPositionY += bSpeedY;

	m_iCurrentScreenX = (int)(bPositionX + 0.5);
	m_iCurrentScreenY = (int)(bPositionY + 0.5);

	
	RedrawObjects();
}

#include "header.h"
#include "templates.h"
#include "GamePlayer.h"



GamePlayer::GamePlayer(GameEngine* pEngine, int pType, const char* szLabel,
	int iXLabelOffset, int iYLabelOffset)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, pLabel(szLabel)
{
	if (pType == 0)
		im.LoadImage("img/characters/Leonor.png");
	else
		im.LoadImage("img/characters/Wendy.png");
		
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = iXLabelOffset;
	m_iCurrentScreenY = m_iPreviousScreenY = iYLabelOffset;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the player size as both height and width
	m_iDrawWidth = 64;
	m_iDrawHeight = 64;
	// And make it visible
	SetVisible(false);
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::setPlayerLife(int value)
{
	//value is 1 or -1
	pLife += value;
}

void GamePlayer::setPosition(double dX, double dY)
{
	m_iCurrentScreenX = m_iPreviousScreenX = dX;
	m_iCurrentScreenY = m_iPreviousScreenY = dY;
}


void GamePlayer::Draw()
{
	if (!IsVisible())
		return;
	//get the time, in terms of the number of ticks.
	int iTick = m_pMainEngine->GetTime() / 100; // 1 per 20ms
	int im_Y = iTick % 4;

	switch (pState) 
	{
	case left:
		im.RenderImageWithMask(GetEngine()->GetForeground()
			, im.GetWidth() / 4, im.GetHeight() / 4 * im_Y
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im.GetWidth() / 4, im.GetHeight() / 4);
		break;
	case right:
		im.RenderImageWithMask(GetEngine()->GetForeground()
			, im.GetWidth() / 4 * 3, im.GetHeight() / 4 * im_Y
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im.GetWidth() / 4, im.GetHeight() / 4);
		break;
	case front:
		im.RenderImageWithMask(GetEngine()->GetForeground()
			, 0, im.GetHeight() / 4 * im_Y
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im.GetWidth()/4, im.GetHeight() / 4);
		break;
	case back:
		im.RenderImageWithMask(GetEngine()->GetForeground()
			, im.GetWidth() / 4 * 2, im.GetHeight() / 4 * im_Y
			, m_iCurrentScreenX, m_iCurrentScreenY
			, im.GetWidth()/4, im.GetHeight() / 4);
		break;
	}
	

	if ((pLabel != NULL) && (strlen(pLabel)>0 && pLState == visible))
		GetEngine()->DrawForegroundString(m_iCurrentScreenX, m_iCurrentScreenY-9, pLabel, 0xffffff);
	
	StoreLastScreenPositionForUndraw();
}

void GamePlayer::DoUpdate(int iCurrentTime)
{
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY >= 480)
		m_iCurrentScreenY = 480;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_UP)) {
		pDir = 0;
		pState = back;
		if (m_iCurrentScreenX >= 185 && m_iCurrentScreenX <= 200) {
			m_iCurrentScreenX = 192;
			m_iCurrentScreenY -= 2;
		}
		if (m_iCurrentScreenX >= 120 && m_iCurrentScreenX <= 130) {
			m_iCurrentScreenX = 128;
			m_iCurrentScreenY -= 2;
		}
		if (m_iCurrentScreenX >= 505 && m_iCurrentScreenX <= 515) {
			m_iCurrentScreenX = 512;
			m_iCurrentScreenY -= 2;
		}
		if (m_iCurrentScreenX >= 635 && m_iCurrentScreenX <= 645) {
			m_iCurrentScreenX = 640;
			m_iCurrentScreenY -= 2;
		}
		if (m_iCurrentScreenX >= 340 && m_iCurrentScreenX <= 365) {
			m_iCurrentScreenX = 352;
			m_iCurrentScreenY -= 2;
		}
	}
	if (GetEngine()->IsKeyPressed(SDLK_DOWN)) {
		pDir = 0;
		pState = back;
		if (m_iCurrentScreenX >= 185 && m_iCurrentScreenX <= 200) {
			m_iCurrentScreenX = 192;
			m_iCurrentScreenY += 2;
		}
		if (m_iCurrentScreenX >= 120 && m_iCurrentScreenX <= 130) {
			m_iCurrentScreenX = 128;
			m_iCurrentScreenY += 2;
		}
		if (m_iCurrentScreenX >= 505 && m_iCurrentScreenX <= 515) {
			m_iCurrentScreenX = 512;
			m_iCurrentScreenY += 2;
		}
		if (m_iCurrentScreenX >= 635 && m_iCurrentScreenX <= 645) {
			m_iCurrentScreenX = 640;
			m_iCurrentScreenY += 2;
		}
		if (m_iCurrentScreenX >= 340 && m_iCurrentScreenX <= 365) {
			m_iCurrentScreenX = 352;
			m_iCurrentScreenY += 2;
		}
	}
	if (GetEngine()->IsKeyPressed(SDLK_LEFT)) {
		pDir = 2;
		pState = left; 
		printf("%d,%d\n", m_iCurrentScreenX, m_iCurrentScreenY);
		if (m_iCurrentScreenY <= 110 && m_iCurrentScreenX > 424) {
			m_iCurrentScreenY = 98;
			m_iCurrentScreenX -= 2;
		}
		if (m_iCurrentScreenY <= 162 && m_iCurrentScreenX < 354) {
			m_iCurrentScreenY = 162;
			m_iCurrentScreenX -= 2;
		}
		if (m_iCurrentScreenX > 348 && m_iCurrentScreenY > 162 && m_iCurrentScreenY <= 290) {
			m_iCurrentScreenY = 258;
			m_iCurrentScreenX -= 2;
		}
		if (m_iCurrentScreenX <= 256 && m_iCurrentScreenY > 280 && m_iCurrentScreenY <= 354) {
			m_iCurrentScreenY = 322;
			m_iCurrentScreenX -= 2;
		}
		if (m_iCurrentScreenY > 430) {
			m_iCurrentScreenY = 480;
			m_iCurrentScreenX -= 2;
		}
		if (m_iCurrentScreenX > 484 && m_iCurrentScreenX <= 704 && m_iCurrentScreenY>334 && m_iCurrentScreenY < 416) {
			m_iCurrentScreenY = 386;
			m_iCurrentScreenX -= 2;
		}
	}
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT)) {
		pDir = 1;
		pState = right;
		if (m_iCurrentScreenY <= 110 && m_iCurrentScreenX >= 424) {
			m_iCurrentScreenY = 98;
			m_iCurrentScreenX += 2;
		}
		if (m_iCurrentScreenY <= 162 && m_iCurrentScreenX <= 350) {
			m_iCurrentScreenY = 162;
			m_iCurrentScreenX += 2;
		}
		if (m_iCurrentScreenX >= 348 && m_iCurrentScreenY >162 && m_iCurrentScreenY <= 290) {
			m_iCurrentScreenY = 258;
			m_iCurrentScreenX += 2;
		}
		if (m_iCurrentScreenX <= 254 && m_iCurrentScreenY > 280 && m_iCurrentScreenY <= 354) {
			m_iCurrentScreenY = 322;
			m_iCurrentScreenX += 2;
		}
		if (m_iCurrentScreenY > 430) {
			m_iCurrentScreenY = 480;
			m_iCurrentScreenX += 2;
		}
		if (m_iCurrentScreenX >= 484 && m_iCurrentScreenX < 704 && m_iCurrentScreenY>334 && m_iCurrentScreenY < 416) {
			m_iCurrentScreenY = 386;
			m_iCurrentScreenX += 2;
		}
	}


	if (GetEngine()->IsKeyPressed(SDLK_w)) {
		pDir = 0;
		pState = back;
		m_iCurrentScreenY -= 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_s)) {
		pDir = 0;
		pState = back;
		m_iCurrentScreenY += 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_a)) {
		pDir = 2;
		pState = left;
		m_iCurrentScreenX -= 2;
	}
	if (GetEngine()->IsKeyPressed(SDLK_d)) {
		pDir = 1;
		pState = right;
		m_iCurrentScreenX += 2;
	}
	if (m_pMainEngine->getState() == stateMain) {
		GameTileManager* m_pTileManager = m_pMainEngine->GetTileManager();
		int ptileX = m_pTileManager->GetTileXForPositionOnScreen(m_iCurrentScreenX);
		int ptileY = m_pTileManager->GetTileYForPositionOnScreen(m_iCurrentScreenY);
		int iCurrentTile = m_pTileManager->GetValue(ptileX, ptileY);  
		//int iCurrentTile = m_pMainEngine->m_oTiles.GetValue(ptileX, ptileY);
		if (ptileX > 22 && ptileY == 5 && pHeart == 0) {
			m_pTileManager->UpdateTile(GetEngine(), 24, 6, 11);
			pLife++;
			pHeart++;
		}
		if (ptileX > 20 && ptileY == 9) {
			m_pTileManager->UpdateTile(GetEngine(), 22, 10, 11);
			m_pTileManager->UpdateTile(GetEngine(), 22, 0, 10);
			pKey = 1;
			m_pEngine->GetDisplayableObject(7)->SetVisible(false);
		}
		if (ptileX == 22 && ptileY == 0 && pKey > 0)
			SetVisible(false);
	}
	
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

void GamePlayer::SetLabelVisible()
{
	if (pLState == visible)
		pLState = invisible;
	else
		pLState = visible;
}
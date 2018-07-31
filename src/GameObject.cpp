#include "header.h"
#include "templates.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "GamePlayer.h"
#include "JPGImage.h"

GameObject::GameObject(GameEngine * pEngine, 
	int iID, int iType, int iSize,
	int iXLabelOffset, int iYLabelOffset)
	: DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iType(iType)
	, m_dX(iXLabelOffset)
    , m_dY(iYLabelOffset)
	, m_iXLabelOffset(iXLabelOffset)
	, m_iYLabelOffset(iYLabelOffset)
{	

	im.LoadImage("img/animals/yellowbird64left.png");
	m_dSX = 1;
	m_dSY = 1;
	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;
	// Record the ball size as both height and width
	m_iDrawWidth = 32;
	m_iDrawHeight = 32;
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = m_iDrawWidth;
	m_iCurrentScreenY = m_iPreviousScreenY = m_iDrawHeight;
	// And make it visible
	SetVisible(true);
}

void GameObject::SetPosition(double dX, double dY)
{
	m_dX = rand() % GetEngine()->GetWindowWidth();
	m_dY = rand() % GetEngine()->GetWindowHeight();
}

void GameObject::SetSpeed(double dSX, double dSY)
{
	m_dSX = -rand() % 3 + 1.5;
	m_dSY = -rand() % 3 + 1.5;
}


GameObject::~GameObject()
{

}

void GameObject::Draw()
{
	if (!IsVisible())
		return;
	
	int iTick = GetEngine()->GetTime() / 100; // 1 per 20ms
	int im_Y = iTick % 4;
	
	im.RenderImageWithMask(GetEngine()->GetForeground(), 0, im_Y * im.GetHeight() / 4 + 1
		, m_iCurrentScreenX, m_iCurrentScreenY, im.GetWidth(), im.GetHeight() / 4 - 1);

	StoreLastScreenPositionForUndraw();
}

void GameObject::DoUpdate(int iCurrentTime)
{/*
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_dSY -= 0.01;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_dSY += 0.01;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_dSX -= 0.01;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_dSX += 0.01;
	if (GetEngine()->IsKeyPressed(SDLK_SPACE))
		m_dSX = m_dSY = 0;

	m_dX += m_dSX;
	m_dY += m_dSY;

	if ((m_dX + m_iStartDrawPosX) < 0)
	{
		m_dX = -m_iStartDrawPosX;
		if (m_dSX < 0)
			m_dSX = -m_dSX;
	}

	if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) >(GetEngine()->GetWindowWidth() - 1))
	{
		m_dX = GetEngine()->GetWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
	}

	if ((m_dY + m_iStartDrawPosY) < 0)
	{
		m_dY = -m_iStartDrawPosY;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
	}

	if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) >(GetEngine()->GetWindowHeight() - 1))
	{
		m_dY = GetEngine()->GetWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
	*/
	m_dX += m_dSX;
	m_dY += m_dSY;
	State here = m_pMainEngine->getState();
	switch (m_pMainEngine->getState()) 
	{
	case stateInit:
		if ((m_dX + m_iStartDrawPosX) < 0)
		{
			m_dX = -m_iStartDrawPosX;
			if (m_dSX < 0)
				m_dSX = -m_dSX;
		}

		if ((m_dX + m_iStartDrawPosX + m_iDrawWidth) >(GetEngine()->GetWindowWidth() - 1))
		{
			m_dX = GetEngine()->GetWindowWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
			if (m_dSX > 0)
				m_dSX = -m_dSX;
		}

		if ((m_dY + m_iStartDrawPosY) < 0)
		{
			m_dY = -m_iStartDrawPosY;
			if (m_dSY < 0)
				m_dSY = -m_dSY;
		}

		if ((m_dY + m_iStartDrawPosY + m_iDrawHeight) >(GetEngine()->GetWindowHeight() - 1))
		{
			m_dY = GetEngine()->GetWindowHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
			if (m_dSY > 0)
				m_dSY = -m_dSY;
		}
		break;
	default:
		int playerX = m_pMainEngine->GetDisplayableObject(8)->GetXCentre();
		int playerY = m_pMainEngine->GetDisplayableObject(8)->GetYCentre();
		int birdX = GetXCentre();
		int birdY = GetYCentre();
		distance = sqrt((playerX - birdX)*(playerX - birdX) + (playerY - birdY)*(playerY - birdY));
		double distanceX = (playerX - birdX);
		double distanceY = (playerY - birdY);
		m_dSX = distanceX / distance;
		m_dSY = distanceY / distance;
		break;
	}


	// Work out current position
	m_iCurrentScreenX = (int)(m_dX + 0.5);
	m_iCurrentScreenY = (int)(m_dY + 0.5);

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
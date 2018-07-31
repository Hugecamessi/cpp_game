#include "header.h"

#include "templates.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "GameTileManager.h"
#include "JPGImage.h"

GameTileManager::GameTileManager()
	: TileManager(32,32)
{
}


GameTileManager::~GameTileManager()
{
}

void GameTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	ImageData im;
	switch (GetValue(iMapX, iMapY))
	{
	case 1://b tile2
		im.LoadImage("img/PNG/tile (2).png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 2://c tree
		if (rand() % 2 == 0) {
			im.LoadImage("img/PNG/tile (20).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		}
		else {
			im.LoadImage("img/PNG/tile (23).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		}
		break;
	case 3://d rope
		im.LoadImage("img/PNG/rope64.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 4://e tile
		im.LoadImage("img/PNG/tile (7).png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 5://f ladder
		im.LoadImage("img/ladder64.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 6://g flower/mushroom/grass
		switch (rand() % 5)
		{
		case 1:
			im.LoadImage("img/PNG/tile (22).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
			break;
		case 2:
			im.LoadImage("img/PNG/tile (25).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
			break;
		case 3:
			im.LoadImage("img/PNG/tile (26).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
			break;
		case 4:
			im.LoadImage("img/PNG/tile (27).png");
			im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
			break;
		}
		break;
	case 7://h heart
		im.LoadImage("img/heart.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 8://i key
		im.LoadImage("img/key.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	case 9://j doorCLOSED
		im.LoadImage("img/door.png");
		im.RenderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth()/3, im.GetHeight()/4);
		break;
	case 10://k doorOPENED
		im.LoadImage("img/door.png");
		im.RenderImageWithMask(pSurface, 0, 3 * im.GetHeight()/4+1
			, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth()/3, im.GetHeight()/4-1);
		break;
	case 11://L for mask heart & key
		im.LoadImage("img/forMask.jpg");
		im.RenderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, im.GetWidth(), im.GetHeight());
		break;
	default:
		break;
	}

	
}

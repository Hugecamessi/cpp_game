#pragma once
#include "header.h"
#include "templates.h"
#include "TileManager.h"
#include "JPGImage.h"
class GameTileManager :
	public TileManager
{
public:
	GameTileManager();
	~GameTileManager();
	void DrawTileAt(BaseEngine * pEngine, SDL_Surface * pSurface, int iMapX, int iMapY, int iStartPositionScreenX, int iStartPositionScreenY) const;

private:
	ImageData imBG, im_temp;
};


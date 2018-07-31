#pragma once
#include "header.h"
#include "templates.h"
#include "DisplayableObject.h"
#include "GameEngine.h"
#include "JPGImage.h"

class GameObject :
	public DisplayableObject
{
public:
	GameObject(GameEngine * pEngine
		, int iID, int iType, int iSize
		, int iXLabelOffset, int iYLabelOffset);
	void Draw();
	void SetPosition(double dX, double dY);
	void SetSpeed(double dSX, double dSY);
	void DoUpdate(int iCurrentTime);

	~GameObject();

	double getDistance() { return distance; }

protected:
	ImageData im;
	/** Pointer to the main engine object */
	GameEngine * m_pMainEngine;
	// Size of thing to draw
	int m_iSize;
	int m_iType;
	double m_dX;
	double m_dY;
	double m_dSX;
	double m_dSY;
	double initialDsx;
	double initialDsy;
	// Unique id for object, passed to engine to identify it
	int m_iID;
	// Type of thing to draw
	int m_iDrawType;
	// Label to apply
	const char* m_szLabel;
	// Label offset in pixels
	int m_iXLabelOffset;
	int m_iYLabelOffset;
	double distance;
};
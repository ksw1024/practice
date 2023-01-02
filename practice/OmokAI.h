#pragma once
#include "pch.h"
#include "Event.h"

enum class LineType
{
	None,
	Row,
	Column,
	L_Diagonal,
	R_Diagonal
};

class OmokAI
{
	SINGLE(OmokAI);

public:
	bool AIMode;
	char AI_Color;

public:
	void init(bool useAI, char Color);
	LineType GetLineType(vector<XY> vec);
	ReadLineInfo CheckMax_Vec(vector<vector<XY>> Lines, char Color);
	MaxLineInfo Update();
	void ReadLine(MaxLineInfo MaxLinedata, char Color);
	XY GetmPos(char Color);
	vector<XY> CheckDot(XY Coordinates);
	
};


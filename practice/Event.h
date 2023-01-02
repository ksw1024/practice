#pragma once
#include "pch.h"
#include "Square.h"

struct _tRectangle
{
	int Left;
	int Right;
	int Bottom;
	int Top;
};

struct XY
{
	int x;
	int y;
};

struct MaxLineInfo
{
	char Color;
	int  Num;
	bool Black_Middle;
	bool White_Middle;
	
	vector<XY> BlackMiddle_Pos;
	vector<XY> WhiteMiddle_Pos;

	vector<XY> BlackXY;
	vector<XY> WhiteXY;
};

struct ReadLineInfo
{
	vector<XY> Line;
	int Line_Size;
};

class Event
{
	SINGLE(Event);

public:
	char Get_Color();
	void Update();
	vector<int> GetLine(string data, char Color);
	int GetMax(int Max, int Comp);
	void Winner(char _winer);
	void init();
	MaxLineInfo  GetMaxLine();

public:
	vector<XY> GetDiagonal_XY(int data);
	TURN       GetTurn();
};

  
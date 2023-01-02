#pragma once
#include "pch.h"
class Square
{
	SINGLE(Square);

public:
	int SquareNumber;
	int left;
	int Right;
	int top;
	int Bottom;
	char Color;
	bool last;
	
public:
	void Create_Squares();
	void Create_Plate();
	void Update();
	char GetPlateColor(int x, int y) { return Squares[y * Square_Number + x].Color; }
	Square GetSquare(int x, int y) { return Squares[y * Square_Number + x]; }
	int    GetBlackNum();
	int    GetWhiteNum();

public:
	vector<Square> Squares;
	vector<Square> Plate;
};


#include "Square.h"
#include "Core.h"
#include "Event.h"
#include "KeyMgr.h"

void Square::Create_Squares()
{
	int x = 500 - Square_Size;
	int y = 75 - Square_Size;
	
	for (int i = 0; i < Square_Number; i++)
	{
		for (int j = 0; j < Square_Number; j++)
		{
			Square sq;
			
			sq.left = x;
			sq.top = y;
			sq.Right = x + Square_Size;
			sq.Bottom = y + Square_Size;
			sq.Color = 'N';
			sq.last = false;
			++sq.SquareNumber;
			Squares.push_back(sq);
			x += Square_Size;
		}
		x = 500 - Square_Size;
		y += Square_Size;
	}
}

void Square::Create_Plate()
{
	int x = 500 - (Square_Size / 2);
	int y = 75 - (Square_Size / 2);

	for (int i = 0; i < Omok_Size; i++)
	{
		for (int j = 0; j < Omok_Size; j++)
		{
			Square sq;

			sq.left = x;
			sq.top = y;
			sq.Right = x + Square_Size;
			sq.Bottom = y + Square_Size;
			sq.Color = 'N';
			Plate.push_back(sq);
			x += Square_Size;
		}
		x = 500 - (Square_Size / 2);
		y += Square_Size;
	}
}

void Square::Update()
{
	// 플레이어 착수
	if (Squares.size() > 0)
	{
		int Size = Squares.size();

		for (int i = 0; i < Size; i++)
		{
			if (KeyMgr::GetInst()->GetPos().x > Squares[i].left
				&& KeyMgr::GetInst()->GetPos().x < Squares[i].Right
				&& KeyMgr::GetInst()->GetPos().y > Squares[i].top
				&& KeyMgr::GetInst()->GetPos().y < Squares[i].Bottom
				&& KeyMgr::GetInst()->GetKeyState(KEY::LBTN) == KEY_STATE::TAP)
			{
				if (Squares[i].Color == 'N')
					Squares[i].Color = Event::GetInst()->Get_Color(); 
			}
		}
	}
}

int Square::GetBlackNum()
{
	int Result = 0;
	
	for (int i = 0; i < Squares.size(); i++)
	{
		if (Squares[i].Color == 'B')
			++Result;
	}

	return Result;
}

int Square::GetWhiteNum()
{
	int Result = 0;

	for (int i = 0; i < Squares.size(); i++)
	{
		if (Squares[i].Color == 'W')
			++Result;
	}

	return Result;
}

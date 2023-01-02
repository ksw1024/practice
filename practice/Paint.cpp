#include "Paint.h"
#include "Square.h"
#include "Core.h"
#include "OmokAI.h"

void Paint::Draw_Plate()
{
	int Size = Square::GetInst()->Plate.size();

	HBRUSH BrownBrush = CreateSolidBrush(RGB(235, 118, 0));
	HPEN   BlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	
	SelectObject(Core::GetInst()->GetMemDC(), BlackPen);
	SelectObject(Core::GetInst()->GetMemDC(), BrownBrush);

	for (int i = 0; i < Size; i++)
	{
		Rectangle(Core::GetInst()->GetMemDC(),
			Square::GetInst()->Plate[i].left,
			Square::GetInst()->Plate[i].top,
			Square::GetInst()->Plate[i].Right,
			Square::GetInst()->Plate[i].Bottom);
	}
	
	DeleteObject(BlackPen);
	DeleteObject(BrownBrush);
}

void Paint::Draw_Square()
{
	int Size = Square::GetInst()->Squares.size();

	HBRUSH Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HPEN   RedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	SelectObject(Core::GetInst()->GetMemDC(), RedPen);
	SelectObject(Core::GetInst()->GetMemDC(), Brush);

	for (int i = 0; i < Size; i++)
	{
		Rectangle(Core::GetInst()->GetMemDC(),
			Square::GetInst()->Squares[i].left,
			Square::GetInst()->Squares[i].top,
			Square::GetInst()->Squares[i].Right,
			Square::GetInst()->Squares[i].Bottom);
	}

	DeleteObject(RedPen);
	DeleteObject(Brush);
	
}

void Paint::Draw_Circle()
{
	int Size = Square::GetInst()->Squares.size();
	
	for (int i = 0; i < Size; i++)
	{
		if (Square::GetInst()->Squares[i].Color != 'N')
		{
			HBRUSH Brush;
			HPEN   Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			
			if (Square::GetInst()->Squares[i].Color == 'B')
			{
				Brush = CreateSolidBrush(RGB(0, 0, 0));
				
				if (OmokAI::GetInst()->AIMode == true && Square::GetInst()->Squares[i].last == true)
					Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
				
			}
			else
			{
				Brush = CreateSolidBrush(RGB(255, 255, 255));
			}

			SelectObject(Core::GetInst()->GetMemDC(), Pen);
			SelectObject(Core::GetInst()->GetMemDC(), Brush);
			
			Ellipse(Core::GetInst()->GetMemDC(),
				Square::GetInst()->Squares[i].left,
				Square::GetInst()->Squares[i].top,
				Square::GetInst()->Squares[i].Right,
				Square::GetInst()->Squares[i].Bottom);

			DeleteObject(Brush);
			DeleteObject(Pen);
		}
	}
}

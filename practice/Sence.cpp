#include "Sence.h"
#include "Sence.h"
#include "Event.h"
#include "Core.h"
#include "Paint.h"

void Sence::Cls()
{
	HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(Core::GetInst()->GetMemDC(), WhiteBrush);

	Rectangle(Core::GetInst()->GetMemDC(), 0, 0, x_Resolution, y_Resolution);

	DeleteObject(WhiteBrush);
}

void Sence::Update()
{  
	Square::GetInst()->Update();
}

void Sence::render()
{
	Paint::GetInst()->Draw_Plate();
	//Paint::GetInst()->Draw_Square();
	Paint::GetInst()->Draw_Circle();
}

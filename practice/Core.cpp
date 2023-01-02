#include "Core.h"
#include "Paint.h"
#include "Square.h"
#include "Event.h"
#include "KeyMgr.h"
#include "Sence.h"
#include "Event.h"
#include "OmokAI.h"

void Core::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hDC = GetDC(_hWnd);
	m_hBit = CreateCompatibleBitmap(m_hDC, x_Resolution, y_Resolution);
	m_memDC = CreateCompatibleDC(m_hDC);

	/*
		더블 버퍼링 : 화면이 깜빡이는걸 방지하기위해 더블 버퍼링 기능을 추가해야함
					 더블 버퍼링은 화면을 2개를 만들어 사용자가 안보이는 화면에 미리 그리고
					 다 그린 결과물을 보여줌과 동시에 이전에 보여줬던 화면을 숨기고 다시 그리고
					 보여주는걸 반복함 (도화지를 2개를 준비해 그리는 것과 비슷함)
					 그래서 사용자는 항상 다 그려진 결과물만 보게 됨

		CreateCompatibleBitmap 함수 : 컬러 비트맵을 만드는 함수 이다 (백 버퍼 생성)
		
		CreateCompatibleDC 함수 : 기존 메인 윈도우의 DC와 호환되는 DC를 만드는 함수
								  그래서 이 함수가 반환하는 DC로 그리면 사용자가 안보이는
								  화면에 그릴수 있음 즉 더블 버퍼링 기능 구현
	*/
	
	SelectObject(m_memDC, m_hBit);

	Square::GetInst()->Create_Squares();
	Square::GetInst()->Create_Plate();
	Event::GetInst()->init();
	KeyMgr::GetInst()->init();
	OmokAI::GetInst()->init(true, 'B'); 
	Program = true;
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::Update()
{
	KeyMgr::GetInst()->Update();
	Event::GetInst()->Update();
	Sence::GetInst()->Update();
}

void Core::Render()
{
	// 화면 지워줌
	Sence::GetInst()->Cls();
	
	// 메인 윈도우 DC인 m_hdc 가 아닌 더블 버퍼링 DC인 m_memDC 에서 그려줌
	Sence::GetInst()->render();
	
	// 백 버퍼에서 다 그리고 메인 DC로 그림을 복사해줌
	BitBlt(m_hDC, 0, 0, x_Resolution, y_Resolution, m_memDC, 0, 0, SRCCOPY);
	/*
		BitBlt 함수 : BitBlt 함수는 DC 간에 그림을 복사하는 함수입니다. 
				      따라서 '원본 DC'와 '사본 DC'가 매개 변수에 넘어가야 하는데 
				      hdcSrc가 '원본 DC'이고 hdcDest가 '사본 DC'입니다.
	*/
}

void Core::Game_Restart()
{
	//기존 게임 정보 삭제
	Square::GetInst()->Squares.clear();
	Square::GetInst()->Plate.clear();

	// 새 게임 정보 초기화
	Square::GetInst()->Create_Squares();
	Square::GetInst()->Create_Plate();
	Event::GetInst()->init();
	KeyMgr::GetInst()->init();
	OmokAI::GetInst()->init(true, 'B');
	Program = true;
}

Core::~Core()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}

#pragma once
#include "pch.h"
class Core
{
	SINGLE(Core);

private:
	HWND m_hWnd; // 메인 윈도우 핸들
	HDC m_hDC;   // 메인 윈도우 DC
	int _WM_LBUTTONDOWN; //마우스 클릭 상태 정보
	bool Program;

	HBITMAP	m_hBit; // 더블 버퍼링에 사용되는 백 버퍼
	HDC m_memDC; // 더블버퍼링에 사용되는 백 버퍼 DC

public:
	HDC		GetMainDC() { return m_hDC; }
	HDC		GetMemDC() { return m_memDC; }
	HWND	GetMainHwnd() { return m_hWnd; }
	inline void RunProgram(bool _Run) { Program = _Run; }
	bool    isRun() { return Program; }
	void    Game_Restart();

public:
    ~Core();
	void Init(HWND _hWnd);
	void Progress();
	void Update();
	void Render();
};


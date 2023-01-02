#pragma once
#include "pch.h"
class Core
{
	SINGLE(Core);

private:
	HWND m_hWnd; // ���� ������ �ڵ�
	HDC m_hDC;   // ���� ������ DC
	int _WM_LBUTTONDOWN; //���콺 Ŭ�� ���� ����
	bool Program;

	HBITMAP	m_hBit; // ���� ���۸��� ���Ǵ� �� ����
	HDC m_memDC; // ������۸��� ���Ǵ� �� ���� DC

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


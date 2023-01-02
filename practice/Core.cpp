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
		���� ���۸� : ȭ���� �����̴°� �����ϱ����� ���� ���۸� ����� �߰��ؾ���
					 ���� ���۸��� ȭ���� 2���� ����� ����ڰ� �Ⱥ��̴� ȭ�鿡 �̸� �׸���
					 �� �׸� ������� �����ܰ� ���ÿ� ������ ������� ȭ���� ����� �ٽ� �׸���
					 �����ִ°� �ݺ��� (��ȭ���� 2���� �غ��� �׸��� �Ͱ� �����)
					 �׷��� ����ڴ� �׻� �� �׷��� ������� ���� ��

		CreateCompatibleBitmap �Լ� : �÷� ��Ʈ���� ����� �Լ� �̴� (�� ���� ����)
		
		CreateCompatibleDC �Լ� : ���� ���� �������� DC�� ȣȯ�Ǵ� DC�� ����� �Լ�
								  �׷��� �� �Լ��� ��ȯ�ϴ� DC�� �׸��� ����ڰ� �Ⱥ��̴�
								  ȭ�鿡 �׸��� ���� �� ���� ���۸� ��� ����
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
	// ȭ�� ������
	Sence::GetInst()->Cls();
	
	// ���� ������ DC�� m_hdc �� �ƴ� ���� ���۸� DC�� m_memDC ���� �׷���
	Sence::GetInst()->render();
	
	// �� ���ۿ��� �� �׸��� ���� DC�� �׸��� ��������
	BitBlt(m_hDC, 0, 0, x_Resolution, y_Resolution, m_memDC, 0, 0, SRCCOPY);
	/*
		BitBlt �Լ� : BitBlt �Լ��� DC ���� �׸��� �����ϴ� �Լ��Դϴ�. 
				      ���� '���� DC'�� '�纻 DC'�� �Ű� ������ �Ѿ�� �ϴµ� 
				      hdcSrc�� '���� DC'�̰� hdcDest�� '�纻 DC'�Դϴ�.
	*/
}

void Core::Game_Restart()
{
	//���� ���� ���� ����
	Square::GetInst()->Squares.clear();
	Square::GetInst()->Plate.clear();

	// �� ���� ���� �ʱ�ȭ
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

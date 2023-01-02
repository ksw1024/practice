#include "KeyMgr.h"
#include "Core.h"

int Key_Arr[(int)KEY::LAST] =
{
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'Z',
	'X',
	'C',
	'V',
	'B',
	'N',
	'M',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_INSERT,
	VK_DELETE,
	VK_HOME,
	VK_END,
	VK_PRIOR,
	VK_NEXT,

	VK_MENU,
	VK_LCONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_TAB,
	VK_ESCAPE,
	VK_RETURN
};

void KeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		KeyInfo _tKeyInfo;
		_tKeyInfo.state = KEY_STATE::NONE;
		_tKeyInfo.prev = false;
		
		Vec_Key.push_back(_tKeyInfo);
	}
}

void KeyMgr::Update()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		// 현재 키가 눌린상태
		if (GetAsyncKeyState(Key_Arr[i]) & 0x8000)
		{
			//이전에도 눌려있었다 
			if (Vec_Key[i].prev)
			{
				Vec_Key[i].state = KEY_STATE::HOLD;
			}
			//이전에 눌려있지 않았다
			else
			{
				Vec_Key[i].state = KEY_STATE::TAP;
			}

			Vec_Key[i].prev = true;
		}
		//현재 키가 눌려있지 않은 상태
		else
		{
			if (Vec_Key[i].prev)
			{
				Vec_Key[i].state = KEY_STATE::AWAY;
			}
			else
			{
				Vec_Key[i].state = KEY_STATE::NONE;
			}

			Vec_Key[i].prev = false;
		}
	}

	POINT ptPos = {};
	GetCursorPos(&ptPos);

	ScreenToClient(Core::GetInst()->GetMainHwnd(), &ptPos);

	m_Pos = ptPos;
}





#pragma once
#include "pch.h"

enum class KEY_STATE
{
	NONE,	// Prev X Curr X
	TAP,	// Prev X Curr O
	HOLD,	// Prev O Curr O
	AWAY,	// Prev O Curr X
};

enum class KEY
{
	UP,
	DOWN,
	LEFT,
	RIGHT,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,

	NUM_0,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,

	NUMPAD_0,
	NUMPAD_1,
	NUMPAD_2,
	NUMPAD_3,
	NUMPAD_4,
	NUMPAD_5,
	NUMPAD_6,
	NUMPAD_7,
	NUMPAD_8,
	NUMPAD_9,

	LBTN,
	RBTN,

	INSERT,
	DEL,
	HOME,
	END,
	PAGE_UP,
	PAGE_DOWN,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	TAB,
	ESC,
	ENTER,

	LAST,
};

struct KeyInfo
{
	KEY_STATE state;
	bool prev;
};

class KeyMgr
{
	SINGLE(KeyMgr);

private:
	vector<KeyInfo> Vec_Key;
	POINT m_Pos;

public:
	void init();
	void Update();

public:
	inline	KEY_STATE GetKeyState(KEY _key) { return Vec_Key[(int)_key].state; }
	POINT GetPos() { return m_Pos; }
};




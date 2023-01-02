#pragma once

#define Omok_Size 19
#define Square_Size 44
#define Square_Number (Omok_Size + 1)
#define x_Resolution 1920
#define y_Resolution 1080

using namespace std;

#define SINGLE(_type)		public:\
								static _type* GetInst()\
								{\
									static _type Inst;\
									return &Inst;\
								}

enum class TURN
{
	BLACK,
	WHITE
};


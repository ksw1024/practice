#include "Event.h"
#include "Core.h"
#include "OmokAI.h"

char Event::Get_Color()
{
	if (GetTurn() == TURN::BLACK)
		return 'B';
	if(GetTurn() == TURN::WHITE)
		return 'W';
}

void Event::Update()
{
	MaxLineInfo _tMaxline = OmokAI::GetInst()->Update();

	if (_tMaxline.Num >= 5)
	{
		Winner(_tMaxline.Color);
	}
}

vector<int> Event::GetLine(string data, char Color)
{
	int Num = 0;  
	int Max = 0;
	
	vector<vector<int>> v_arr;
	vector<int>         i_arr;

	for (int i = 0; i < data.size(); i++)
	{
		bool Not_Line = true;
		
		if (data[i] == Color)
		{
			++Num;

			Max = GetMax(Max, Num);
			i_arr.push_back(i);
			Not_Line = false;
		}
		if (i > 0 && i < data.size() - 1)
		{
			if (data[i - 1] == Color && data[i] == 'N' && data[i + 1] == Color)
			{
				++Num;

				Max = GetMax(Max, Num);
				i_arr.push_back(i);
				Not_Line = false;
			}
		}
		if(Not_Line)
		{
			Num = 0;
			v_arr.push_back(i_arr);
			i_arr.clear();
		}
	}

	v_arr.push_back(i_arr);
	
	for (int i = 0; i < v_arr.size(); i++)
	{
		if (v_arr[i].size() == Max)
			return v_arr[i];
	}
}

int Event::GetMax(int Max, int Comp)
{ 
	if (Comp > Max)
		return Comp;
	else
		return Max;
}

void Event::Winner(char _winer)
{
	Core::GetInst()->RunProgram(false);
	Core::GetInst()->Render();

	if (_winer == 'B')
		MessageBox(Core::GetInst()->GetMainHwnd(), L"흑 승리", L"결과", MB_OK);
	
	else if (_winer == 'W')
		MessageBox(Core::GetInst()->GetMainHwnd(), L"백 승리", L"결과", MB_OK);
}

void Event::init()
{
	
}

MaxLineInfo Event::GetMaxLine()
  {
	MaxLineInfo Result;
	vector<vector<XY>> Black_XY;
	vector<vector<XY>> White_XY;
	
	char Plate[Square_Number][Square_Number];
	int Bmax = 0;
	int Wmax = 0;

	for (int i = 0; i < Square_Number; i++)
	{
		for (int j = 0; j < Square_Number; j++)
		{
			Plate[i][j] = Square::GetInst()->Squares[i * Square_Number + j].Color;
		}
	}

	//가로 체크
	for (int i = 0; i < Square_Number; i++)
	{
		string str;

		for (int j = 0; j < Square_Number; j++)
		{
			str.push_back(Plate[i][j]);
		}

		vector<int> Bline = GetLine(str, 'B');
		vector<int> Wline = GetLine(str, 'W');

		Bmax = GetMax(Bmax, Bline.size());
		Wmax = GetMax(Wmax, Wline.size());

		if (OmokAI::GetInst()->AIMode)
		{
			vector<XY> LinePos;

			for (int k = 0; k < Bline.size(); k++)
			{
				XY xy;
				
				xy.x = Bline[k];
				xy.y = i;
				
				LinePos.push_back(xy);
			}

			if (LinePos.size() > 0)
				Black_XY.push_back(LinePos);
			
			LinePos.clear();

			for (int k = 0; k < Wline.size(); k++)
			{
				XY xy;
				
				xy.x = Wline[k];
				xy.y = i;
				
				LinePos.push_back(xy);
			}

			if (LinePos.size() > 0)
				White_XY.push_back(LinePos);
			
		}
	}

	// 세로 체크
	for (int i = 0; i < Square_Number; i++)
	{
		string str;

		for (int j = 0; j < Square_Number; j++)
		{
			str.push_back(Plate[j][i]);
		}

		vector<int> Bline = GetLine(str, 'B');
		vector<int> Wline = GetLine(str, 'W');

		Bmax = GetMax(Bmax, Bline.size());
		Wmax = GetMax(Wmax, Wline.size());

		if (OmokAI::GetInst()->AIMode)
		{
			vector<XY> LinePos;

			for (int k = 0; k < Bline.size(); k++)
			{
				XY xy;
				
				xy.x = i;
				xy.y = Bline[k];
				
				LinePos.push_back(xy);
			}
			
			if (LinePos.size() > 0)
				Black_XY.push_back(LinePos);
			
			LinePos.clear();

			for (int k = 0; k < Wline.size(); k++)
			{
				XY xy;
				
				xy.x = i;
				xy.y = Wline[k];
				
				LinePos.push_back(xy);
			}

			if (LinePos.size() > 0)
				White_XY.push_back(LinePos);
			
		}
	}

	//왼쪽 대각선 체크

	bool Upper = true;
	int L_dia = Square_Number - 1;

	for (int i = 0; i < Square_Number; i++)
	{
		string str;
		vector<XY> DiaLineXYpos;

		//상단 부분
		if (Upper)
		{
			vector<XY> Dia_XY = GetDiagonal_XY(i);

			for (int j = 0; j < Dia_XY.size(); j++)  
			{
				XY xy;
				
				xy.x = Dia_XY[j].x;
				xy.y = Dia_XY[j].y;
				
				DiaLineXYpos.push_back(xy);
				
				str.push_back(Plate[Dia_XY[j].y][Dia_XY[j].x]);
			}

			if (i == 17)
				int a = 0;
			
			vector<int> Bline = GetLine(str, 'B');
			vector<int> Wline = GetLine(str, 'W');

			Bmax = GetMax(Bmax, Bline.size());
			Wmax = GetMax(Wmax, Wline.size());

			if (OmokAI::GetInst()->AIMode)
			{
				vector<XY> LinePos;
				
				for (int k = 0; k < Bline.size(); k++)
				{
					XY xy = DiaLineXYpos[Bline[k]];
				
					LinePos.push_back(xy);
				}
				
				if (LinePos.size() > 0)
					Black_XY.push_back(LinePos);
				
				LinePos.clear();
				
				for (int k = 0; k < Wline.size(); k++)
				{
					XY xy = DiaLineXYpos[Wline[k]];
				
					LinePos.push_back(xy);
				}
				
				if (LinePos.size() > 0)
					White_XY.push_back(LinePos);
			}

			if (i == Square_Number - 1)
			{
				i = 0;
				str.clear();
				Upper = false;
				
				if (OmokAI::GetInst()->AIMode)
					DiaLineXYpos.clear();
			}
		}
		
		//하단 부분
		if (!Upper)
		{
			vector<XY> Dia_XY = GetDiagonal_XY(i);

			for (int j = 0; j < Dia_XY.size(); j++)
			{
				XY xy;
				
				xy.x = Dia_XY[j].x + L_dia;
				xy.y = Dia_XY[j].y + L_dia;

				DiaLineXYpos.push_back(xy);
				
				str.push_back(Plate[Dia_XY[j].y + L_dia][Dia_XY[j].x + L_dia]);
			}

			vector<int> Bline = GetLine(str, 'B');
			vector<int> Wline = GetLine(str, 'W');

			Bmax = GetMax(Bmax, Bline.size());
			Wmax = GetMax(Wmax, Wline.size());

			if (OmokAI::GetInst()->AIMode)
			{
				vector<XY> LinePos;

				for (int k = 0; k < Bline.size(); k++)
				{
					XY xy = DiaLineXYpos[Bline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					Black_XY.push_back(LinePos);
				
				LinePos.clear();

				for (int k = 0; k < Wline.size(); k++)
				{
					XY xy = DiaLineXYpos[Wline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					White_XY.push_back(LinePos);
			}
			
			--L_dia;
		}
	}

	//오른쪽 대각선 체크
	Upper = true;

	for (int i = 0; i < Square_Number; i++)
	{
		string str;
		vector<XY> DiaLineXYpos;

		//상단 부분
		if (Upper)
		{
			int R_dia = Square_Number - 1;
			vector<XY> Dia_XY = GetDiagonal_XY(i);

			for (int j = Dia_XY.size() - 1; j >= 0; j--)
			{
				XY xy;
				
				xy.x = Dia_XY[j].x + R_dia;
				xy.y = Dia_XY[j].y;

				DiaLineXYpos.push_back(xy);
				
				str.push_back(Plate[Dia_XY[j].y][Dia_XY[j].x + R_dia]);
				
				R_dia -= 2;
			}

			vector<int> Bline = GetLine(str, 'B');
			vector<int> Wline = GetLine(str, 'W');

			Bmax = GetMax(Bmax, Bline.size());
			Wmax = GetMax(Wmax, Wline.size());

			if (OmokAI::GetInst()->AIMode)
			{
				vector<XY> LinePos;

				for (int k = 0; k < Bline.size(); k++)
				{
					XY xy = DiaLineXYpos[Bline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					Black_XY.push_back(LinePos);
				
				LinePos.clear();

				for (int k = 0; k < Wline.size(); k++)
				{
					XY xy = DiaLineXYpos[Wline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					White_XY.push_back(LinePos);
			}

			if (i == Square_Number - 1)
			{
				i = 0;
				str.clear();
				Upper = false;

				if (OmokAI::GetInst()->AIMode)
					DiaLineXYpos.clear();
			}
		}

		//하단 부분
		if (!Upper)
		{
			int R_dia = Square_Number - 1;
			vector<XY> Dia_XY = GetDiagonal_XY(i);

			for (int j = 0; j < Dia_XY.size(); j++)
			{
				XY xy;

				xy.x = Dia_XY[j].x;
				xy.y = Dia_XY[j].y + R_dia;

				DiaLineXYpos.push_back(xy);
				
				str.push_back(Plate[Dia_XY[j].y + R_dia][Dia_XY[j].x]);
				
				R_dia -= 2;
			}

			vector<int> Bline = GetLine(str, 'B');
			vector<int> Wline = GetLine(str, 'W');

			Bmax = GetMax(Bmax, Bline.size());
			Wmax = GetMax(Wmax, Wline.size());

			if (OmokAI::GetInst()->AIMode)
			{
				vector<XY> LinePos;

				for (int k = 0; k < Bline.size(); k++)
				{
					XY xy = DiaLineXYpos[Bline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					Black_XY.push_back(LinePos);
				
				LinePos.clear();

				for (int k = 0; k < Wline.size(); k++)
				{
					XY xy = DiaLineXYpos[Wline[k]];

					LinePos.push_back(xy);
				}

				if (LinePos.size() > 0)
					White_XY.push_back(LinePos);
			
			}
		}
	}

	ReadLineInfo Black_L = OmokAI::GetInst()->CheckMax_Vec(Black_XY, 'B');
	ReadLineInfo White_L = OmokAI::GetInst()->CheckMax_Vec(White_XY, 'W');
	vector<XY> B_XY = Black_L.Line;
	vector<XY> W_XY = White_L.Line;

	Result.Black_Middle = false;
	Result.White_Middle = false;

	if (OmokAI::GetInst()->AIMode)
	{
		if (B_XY.size() > 2)
		{
			for (int i = 0; i < B_XY.size(); i++)
			{
				if (Square::GetInst()->GetPlateColor(B_XY[i].x, B_XY[i].y) == 'N')
				{
					XY xy;
					
					Result.Black_Middle = true;
					xy.x = B_XY[i].x;
					xy.y = B_XY[i].y;
					Result.BlackMiddle_Pos.push_back(xy);
				}
			}
		}
		
		if (W_XY.size() > 2)
		{
			for (int i = 0; i < W_XY.size(); i++)
			{
				if (Square::GetInst()->GetPlateColor(W_XY[i].x, W_XY[i].y) == 'N')
				{
					XY xy;
					
					Result.White_Middle = true;
					xy.x = W_XY[i].x;
					xy.y = W_XY[i].y;
					Result.WhiteMiddle_Pos.push_back(xy);
				}
			}
		}
	}

	if (OmokAI::GetInst()->AIMode && (B_XY.size() > 0 || W_XY.size() > 0))
	{
		int B_SIZE = Black_L.Line_Size;
		int W_SIZE = White_L.Line_Size;

		if (B_SIZE == W_SIZE)
		{
			Result.Color = 'N';
			Result.Num = B_SIZE;
		}
		else
		{
			if (B_SIZE > W_SIZE)
			{
				Result.Color = 'B';
				Result.Num = B_SIZE;
			}
			else
			{
				Result.Color = 'W';
				Result.Num = W_SIZE;
			}
		}
	}
	else
	{
		if (Bmax == Wmax)
		{
			Result.Color = 'N';
			Result.Num = Bmax;
		}
		else
		{
			if (Bmax > Wmax)
			{
				Result.Color = 'B';
				Result.Num = Bmax;
			}
			else
			{
				Result.Color = 'W';
				Result.Num = Wmax;
			}
		}
	}

	Result.BlackXY = B_XY;
	Result.WhiteXY = W_XY;

	return Result;
}

vector<XY> Event::GetDiagonal_XY(int data)
{
	vector<XY> Result;

	for (int i = 0; i <= data; i++)
	{
		for (int j = 0; j <= data; j++)
		{
			if (i + j == data)
			{
				XY Coordinates;
				
				Coordinates.x = j;
				Coordinates.y = i;
				
				Result.push_back(Coordinates);
			}
		}
	}

	return Result;
}

TURN Event::GetTurn()
{
	int B = 0;
	int W = 0;  
	
	for (int i = 0; i < Square::GetInst()->Squares.size(); i++)
	{
		if (Square::GetInst()->Squares[i].Color == 'B')
			++B;
		else if (Square::GetInst()->Squares[i].Color == 'W')
			++W;
	}

	if (B == W)
		return TURN::BLACK;
	if (B > W)
		return TURN::WHITE;
}

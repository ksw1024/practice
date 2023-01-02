#include "OmokAI.h"
#include "Event.h"
#include "Square.h"

void OmokAI::init(bool useAI, char Color)
{
	AIMode = useAI;
	AI_Color = Color;
}

LineType OmokAI::GetLineType(vector<XY> vec)
{
	if (2 > vec.size())
	{
		return LineType::None;
	}
	else
	{
		for (int i = 0; i < vec.size() - 1; i++)
		{
			if (vec[i].y == vec[i + 1].y)
				return LineType::Row;

			else if (vec[i].x == vec[i + 1].x)
				return LineType::Column;

			else if (vec[i].x + vec[i].y != vec[i + 1].x + vec[i + 1].y)
				return LineType::R_Diagonal;
		}
		
		return LineType::L_Diagonal;
	}
}

ReadLineInfo OmokAI::CheckMax_Vec(vector<vector<XY>> Lines, char Color)
{
	ReadLineInfo Result;
	vector<XY> Line;

	int Max_Vec = 0;
	int Max_Prev = 0;
	char _Color;
	bool Different = false;
	bool SideBlocked = false;

	if (Color == 'B')
		_Color = 'W';
	else
		_Color = 'B';

	for (int i = 0; i < Lines.size(); i++)
	{  
		if (GetLineType(Lines[i]) == LineType::Row && Lines.size() > 1)
		{
			int Size = 0;

			for (int j = 0; j < Lines[i].size(); j++)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][j].x, Lines[i][j].y) == Color)
					++Size;
			}

			if (Lines[i][0].x != 0 && Lines[i][Lines[i].size() - 1].x != Square_Number - 1)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][0].x - 1, Lines[i][0].y) != _Color
					|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x + 1, Lines[i][Lines[i].size() - 1].y) != _Color
					|| Size >= 5)
				{
					if ((Square::GetInst()->GetPlateColor(Lines[i][0].x - 1, Lines[i][0].y) == _Color
						|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x + 1, Lines[i][Lines[i].size() - 1].y) == _Color)
						&& Size < 5)
					{
						SideBlocked = true;
					}

					Max_Prev = Max_Vec;
					Max_Vec = Event::GetInst()->GetMax(Max_Vec, Size);
				}
				else if (Max_Vec == Size)
					Different = true;
			}
		}

		else if (GetLineType(Lines[i]) == LineType::Column && Lines.size() > 1)
		{
			int Size = 0;

			for (int j = 0; j < Lines[i].size(); j++)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][j].x, Lines[i][j].y) == Color)
					++Size;
			}

			if (Lines[i][0].y != 0 && Lines[i][Lines[i].size() - 1].y != Square_Number - 1)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][0].x, Lines[i][0].y - 1) != _Color
					|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x, Lines[i][Lines[i].size() - 1].y + 1) != _Color
					|| Size >= 5)
				{
					if ((Square::GetInst()->GetPlateColor(Lines[i][0].x, Lines[i][0].y - 1) == _Color
						|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x, Lines[i][Lines[i].size() - 1].y + 1) == _Color)
						&& Size < 5)
					{
						SideBlocked = true;
					}

					Max_Prev = Max_Vec;
					Max_Vec = Event::GetInst()->GetMax(Max_Vec, Size);
				}
				else if (Max_Vec == Size)
					Different = true;
			}
		}

		else if (GetLineType(Lines[i]) == LineType::L_Diagonal && Lines.size() > 1)
		{
			int Size = 0;

			for (int j = 0; j < Lines[i].size(); j++)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][j].x, Lines[i][j].y) == Color)
					++Size;
			}

			if ((((Lines[i][0].y - 1) * Square_Number + (Lines[i][0].x + 1)) > 0
				&& ((Lines[i][Lines[i].size() - 1].y + 1) * Square_Number + (Lines[i][Lines[i].size() - 1].x - 1)) > 0))
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][0].x + 1, Lines[i][0].y - 1) != _Color
					|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x - 1, Lines[i][Lines[i].size() - 1].y + 1) != _Color
					|| Size >= 5)
				{
					if ((Square::GetInst()->GetPlateColor(Lines[i][0].x + 1, Lines[i][0].y - 1) == _Color
						|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x - 1, Lines[i][Lines[i].size() - 1].y + 1) == _Color)
						&& Size < 5)
					{
						SideBlocked = true;
					}
					
					Max_Prev = Max_Vec;
					Max_Vec = Event::GetInst()->GetMax(Max_Vec, Size);
				}
				else if (Max_Vec == Size)
					Different = true;
			}
		}

		else if (GetLineType(Lines[i]) == LineType::R_Diagonal && Lines.size() > 1)
		{
			int Size = 0;

			for (int j = 0; j < Lines[i].size(); j++)
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][j].x, Lines[i][j].y) == Color)
					++Size;
			}

			if ((((Lines[i][0].y + 1) * Square_Number + (Lines[i][0].x + 1)) > 0
				&& ((Lines[i][Lines[i].size() - 1].y - 1) * Square_Number + (Lines[i][Lines[i].size() - 1].x - 1)) > 0))
			{
				if (Square::GetInst()->GetPlateColor(Lines[i][0].x + 1, Lines[i][0].y + 1) != _Color
					|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x - 1, Lines[i][Lines[i].size() - 1].y - 1) != _Color
					|| Size >= 5)
				{
					if ((Square::GetInst()->GetPlateColor(Lines[i][0].x + 1, Lines[i][0].y + 1) == _Color
						|| Square::GetInst()->GetPlateColor(Lines[i][Lines[i].size() - 1].x - 1, Lines[i][Lines[i].size() - 1].y - 1) == _Color)
						&& Size < 5)
					{
						SideBlocked = true;
					}
					
					Max_Prev = Max_Vec;
					Max_Vec = Event::GetInst()->GetMax(Max_Vec, Size);
				}
				else if (Max_Vec == Size)
					Different = true;
			}
		}

		int _Size = 0;

		for (int j = 0; j < Lines[i].size(); j++)
		{
			if (Square::GetInst()->GetPlateColor(Lines[i][j].x, Lines[i][j].y) == Color)
				++_Size;
		}
		
		if (Max_Vec == _Size && Different == false)
		{
			if (Max_Prev == Max_Vec)
			{
				if (!SideBlocked)
				{
					Result.Line = Lines[i];
					Result.Line_Size = _Size;
				}
			}
			else
			{
				Result.Line = Lines[i];
				
				if (SideBlocked)
				{
					--_Size;
					Result.Line_Size = _Size;
				}
				else
				{
					Result.Line_Size = _Size;
				}
			}
		}
		
		if (Different == true)
				Different = false;
		
		if (SideBlocked == true)
			SideBlocked = false;
	}

	return Result;
}

MaxLineInfo OmokAI::Update()
{ 
	MaxLineInfo Maxline = Event::GetInst()->GetMaxLine();

	if (AIMode == true)
	{
		if (AI_Color == 'B')
		{
			if (Event::GetInst()->GetTurn()==TURN::BLACK)
			{
				for (int t = 0; t < Square::GetInst()->Squares.size(); t++)
				{
					if (Square::GetInst()->Squares[t].last)
						Square::GetInst()->Squares[t].last = false;
				}
				
				if (GetLineType(Maxline.BlackXY) == LineType::None && GetLineType(Maxline.WhiteXY) == LineType::None)
				{
					if (Maxline.Num == 0)
					{
						// 처음 시작
						Square::GetInst()->Squares[((Omok_Size * Omok_Size + Omok_Size) / 2)].Color = Event::GetInst()->Get_Color();
					}
					else if (Square::GetInst()->GetBlackNum() == 1)
					{
						// 게임 시작후 2번째 턴 착수
						if (Square::GetInst()->Squares[9 * Square_Number + 9].Color == 'N')
						{
							Square::GetInst()->Squares[9 * Square_Number + 9].Color = Event::GetInst()->Get_Color();
							Square::GetInst()->Squares[9 * Square_Number + 9].last = true;
						}
						else
						{
							Square::GetInst()->Squares[(9 * Square_Number + 9) + 2].Color = Event::GetInst()->Get_Color();
							Square::GetInst()->Squares[(9 * Square_Number + 9) + 2].last = true;
						}
					}
					else
					{
						// 흑 백 모두 최대가 1개인 경우
						XY Cor = GetmPos('B');
						Square::GetInst()->Squares[Cor.y * Square_Number + Cor.x].Color = Event::GetInst()->Get_Color();
						Square::GetInst()->Squares[Cor.y * Square_Number + Cor.x].last = true;
					}
				}
				else if (Maxline.Num < 3)
				{
					/*
						백 이 최대가 2개가 최대인 경우 따라서 막을 필요가 없는 경우 
						그래서 흑에서 한줄 비우고 떨어진 경우를 체크하고 만약 없다면 랜덤으로
						아무 흑돌의 1칸 주변에 흑돌을 착수함
					*/
					XY Cor = GetmPos('B');
					Square::GetInst()->Squares[Cor.y * Square_Number + Cor.x].Color = Event::GetInst()->Get_Color();
					Square::GetInst()->Squares[Cor.y * Square_Number + Cor.x].last = true;
				}
				else if (Maxline.Num > 2 && Maxline.Color == 'W')
				{
					if (Maxline.BlackXY.size() - Maxline.BlackMiddle_Pos.size() > 2)
					{
						if (Maxline.BlackXY.size() - Maxline.BlackMiddle_Pos.size() >= Maxline.WhiteXY.size() - Maxline.WhiteMiddle_Pos.size())
						{
							ReadLine(Maxline, 'B');
						}
						else
						{
							ReadLine(Maxline, 'W');
						}
					}
					else
					{
						ReadLine(Maxline, 'W');
					}
				}
				else if (Maxline.Num > 1 && (Maxline.Color == 'B' || Maxline.Color == 'N'))
				{
					ReadLine(Maxline, 'B');
				}
			}
		}
	}

	if (Maxline.Num >= 5 && Maxline.Color == 'B')
	{
		if (Maxline.BlackXY.size() > 0)
		{
			for (int i = 1; i < Maxline.BlackXY.size() - 1; i++)
			{
				if (Square::GetInst()->GetPlateColor(Maxline.BlackXY[i].x, Maxline.BlackXY[i].y) != 'B')
				{
					Maxline.Num = 0;
					break;
				}
			}
		}
	}
	
	if (Maxline.Num >= 5 && Maxline.Color == 'W')
	{
		if (Maxline.WhiteXY.size() > 0)
		{
			for (int i = 1; i < Maxline.WhiteXY.size() - 1; i++)
			{
				if (Square::GetInst()->GetPlateColor(Maxline.WhiteXY[i].x, Maxline.WhiteXY[i].y) != 'W')
				{
					Maxline.Num = 0;
					break;
				}
			}
		}
	}

	return Maxline;
}

void OmokAI::ReadLine(MaxLineInfo MaxLinedata, char Color)
{
	char _Color;
	bool isMid_Line;

	vector<XY> V_Middle_Pos;
	vector<XY> Line;

	if (Color == 'B')
	{
		_Color = 'W';
		Line = MaxLinedata.BlackXY;
		isMid_Line = MaxLinedata.Black_Middle;
		V_Middle_Pos = MaxLinedata.BlackMiddle_Pos;
	}
	else
	{
		_Color = 'B';
		Line = MaxLinedata.WhiteXY;
		isMid_Line = MaxLinedata.White_Middle;
		V_Middle_Pos = MaxLinedata.WhiteMiddle_Pos;
	}

	if (isMid_Line)
	{
		// 뜬줄 일때 각 띈 좌표에 대한 경우의 수 시뮬레이션
		vector<vector<XY>> v_BLines;
		vector<vector<XY>> v_WLines;

		vector<XY> v_Min;
		vector<XY> v_Max;
		
		XY BMaxPos;
		XY WMinPos;
		
		for (int i = 0; i < V_Middle_Pos.size(); i++)
		{
			Square::GetInst()->Squares[V_Middle_Pos[i].y * Square_Number + V_Middle_Pos[i].x].Color = 'B';

			MaxLineInfo testMax = Event::GetInst()->GetMaxLine();

			v_BLines.push_back(testMax.BlackXY);
			v_WLines.push_back(testMax.WhiteXY);

			Square::GetInst()->Squares[V_Middle_Pos[i].y * Square_Number + V_Middle_Pos[i].x].Color = 'N';
		}

		//공격상황 : 흑 최대(우선), 백 최소
		if (_Color == 'W')
		{
			int Min = 999;

			for (int i = 0; i < v_WLines.size(); i++)
			{
				if (v_WLines[i].size() < Min)
				{
					Min = v_WLines[i].size();
					v_Min = v_WLines[i];
					WMinPos = V_Middle_Pos[i];
				}
			}

			// 백을 최소로 만들 수 있는 좌표가 있을때
			if (Min != 999)
			{
				int Max = 0;

				for (int i = 0; i < v_BLines.size(); i++)
				{
					if (v_BLines[i].size() > Max)
					{
						Max = v_BLines[i].size();
						v_Max = v_BLines[i];
						BMaxPos = V_Middle_Pos[i];
					}
					else if (v_BLines[i].size() == Max && (V_Middle_Pos[i].x == WMinPos.x && V_Middle_Pos[i].y == WMinPos.y))
					{
						Max = v_BLines[i].size();
						v_Max = v_BLines[i];
						BMaxPos = V_Middle_Pos[i];
					}
				}

				Square::GetInst()->Squares[BMaxPos.y * Square_Number + BMaxPos.x].Color = Event::GetInst()->Get_Color();
			}
			// 백을 최소로 만들 수 있는 좌표가 없을때
			else
			{
				int Max = 0;

				for (int i = 0; i < v_BLines.size(); i++)
				{
					if (v_BLines[i].size() > Max)
					{
						Max = v_BLines[i].size();
						v_Max = v_BLines[i];
						BMaxPos = V_Middle_Pos[i];
					}
				}
				
				Square::GetInst()->Squares[BMaxPos.y * Square_Number + BMaxPos.x].Color = Event::GetInst()->Get_Color();
				Square::GetInst()->Squares[BMaxPos.y * Square_Number + BMaxPos.x].last = true;
			}
		}
		
		//수비 상황 : 흑 최대 백 최소(우선)
		else
		{
			int Max = 0;

			for (int i = 0; i < v_BLines.size(); i++)
			{
				if (v_BLines[i].size() > Max)
				{
					Max = v_BLines[i].size();
					v_Max = v_BLines[i];
					BMaxPos = V_Middle_Pos[i];
				}
			}

			//흑을 최대로 만들 수 있는 좌표가 있을때
			if (Max != 0)
			{
				int Min = 999;

				for (int i = 0; i < v_WLines.size(); i++)
				{
					if (v_WLines[i].size() < Min)
					{
						Min = v_WLines[i].size();
						v_Min = v_WLines[i];
						WMinPos = V_Middle_Pos[i];
					}
					else if (v_WLines[i].size() == Min && (V_Middle_Pos[i].x == BMaxPos.x && V_Middle_Pos[i].y == BMaxPos.y))
					{
						Min = v_WLines[i].size();
						v_Min = v_WLines[i];
						WMinPos = V_Middle_Pos[i];
					}
				}

				Square::GetInst()->Squares[WMinPos.y * Square_Number + WMinPos.x].Color = Event::GetInst()->Get_Color();
				Square::GetInst()->Squares[WMinPos.y * Square_Number + WMinPos.x].last = true;
			}
			// 흑을 최대로 만들 수 있는 좌표가 없을때
			else
			{
				int Min = 999;

				for (int i = 0; i < v_WLines.size(); i++)
				{
					if (v_WLines[i].size() < Min)
					{
						Min = v_WLines[i].size();
						v_Min = v_WLines[i];
						WMinPos = V_Middle_Pos[i];
					}
				}

				Square::GetInst()->Squares[WMinPos.y * Square_Number + WMinPos.x].Color = Event::GetInst()->Get_Color();
			}
		}
	}
	else if (GetLineType(Line) == LineType::Row)
	{
		int Size = Line.size();

		if (Line[0].x != 0 && Square::GetInst()->GetPlateColor(Line[0].x - 1, Line[0].y) != _Color)
		{
			Square::GetInst()->Squares[Line[0].y * Square_Number + Line[0].x - 1].Color
				= Event::GetInst()->Get_Color();

			Square::GetInst()->Squares[Line[0].y * Square_Number + Line[0].x - 1].last = true;
		}
		else if (Line[Size - 1].x != Square_Number - 1 && Square::GetInst()->GetPlateColor(Line[Size - 1].x + 1, Line[Size - 1].y) != _Color)
		{
			Square::GetInst()->Squares[Line[Size - 1].y * Square_Number + Line[Size - 1].x + 1].Color
				= Event::GetInst()->Get_Color();

			Square::GetInst()->Squares[Line[Size - 1].y * Square_Number + Line[Size - 1].x + 1].last = true;
		}
	}
	else if (GetLineType(Line) == LineType::Column)
	{
		int Size = Line.size();

		if (Line[0].y != 0 && Square::GetInst()->GetPlateColor(Line[0].x, Line[0].y - 1) != _Color)
		{
			Square::GetInst()->Squares[(Line[0].y - 1) * Square_Number + Line[0].x].Color
				= Event::GetInst()->Get_Color();

			Square::GetInst()->Squares[(Line[0].y - 1) * Square_Number + Line[0].x].last = true;
		}
		else if (Line[Size - 1].y != Square_Number - 1 && Square::GetInst()->GetPlateColor(Line[Size - 1].x, Line[Size - 1].y + 1) != _Color)
		{
			Square::GetInst()->Squares[(Line[Size - 1].y + 1) * Square_Number + Line[Size - 1].x].Color
				= Event::GetInst()->Get_Color();

			Square::GetInst()->Squares[(Line[Size - 1].y + 1) * Square_Number + Line[Size - 1].x].last = true;
		}
	}
	else if (GetLineType(Line) == LineType::L_Diagonal)
	{
		int Size = Line.size();

		if (((Line[0].y - 1) * Square_Number + (Line[0].x + 1)) > 0
			&& ((Line[Line.size() - 1].y + 1)
				* Square_Number + (Line[Line.size() - 1].x - 1)) > 0)
		{
			if (Square::GetInst()->GetPlateColor(Line[0].x + 1, Line[0].y - 1) != _Color)
			{
				Square::GetInst()->Squares[(Line[0].y - 1) * Square_Number + (Line[0].x + 1)].Color = Event::GetInst()->Get_Color();
				
				Square::GetInst()->Squares[(Line[0].y - 1) * Square_Number + (Line[0].x + 1)].last = true;
			}
			else if (Square::GetInst()->GetPlateColor(Line[Line.size() - 1].x - 1, Line[Line.size() - 1].y + 1) != _Color)
			{
				Square::GetInst()->Squares[(Line[Line.size() - 1].y + 1) * Square_Number + (Line[Line.size() - 1].x - 1)].Color = Event::GetInst()->Get_Color();
				Square::GetInst()->Squares[(Line[Line.size() - 1].y + 1) * Square_Number + (Line[Line.size() - 1].x - 1)].last = true;
			}
		}
	}
	else if (GetLineType(Line) == LineType::R_Diagonal)
	{
		if (((Line[0].y + 1) * Square_Number + (Line[0].x + 1)) > 0
			&& ((Line[Line.size() - 1].y - 1)
				* Square_Number + (Line[Line.size() - 1].x - 1)) > 0)
		{
			if (Square::GetInst()->GetPlateColor(Line[0].x + 1, Line[0].y + 1) != _Color)
			{
				Square::GetInst()->Squares[(Line[0].y + 1) * Square_Number + (Line[0].x + 1)].Color = Event::GetInst()->Get_Color();
				Square::GetInst()->Squares[(Line[0].y + 1) * Square_Number + (Line[0].x + 1)].last = true;
			}
			else if (Square::GetInst()->GetPlateColor(Line[Line.size() - 1].x - 1, Line[Line.size() - 1].y - 1) != _Color)
			{
				Square::GetInst()->Squares[(Line[Line.size() - 1].y - 1) * Square_Number + (Line[Line.size() - 1].x - 1)].Color = Event::GetInst()->Get_Color();
				Square::GetInst()->Squares[(Line[Line.size() - 1].y - 1) * Square_Number + (Line[Line.size() - 1].x - 1)].last = true;
			}
		}
	}
}

XY OmokAI::GetmPos(char Color)
{
	// 모든 Color 색 주변 좌표를 체크하면서 가장 높은 사이즈가 되게하는 좌표를 반환함
	
	XY Coordinates;
	int MaxSize = 0;
	int Max_Prev = 0;

	for (int i = 0; i < Square_Number; i++)
	{
		for (int j = 0; j < Square_Number; j++)
		{
			if (Square::GetInst()->GetPlateColor(j, i) == Color)
			{
				XY xy;
				
				xy.x = j;
				
				xy.y = i;
				
				vector<XY> surXY = CheckDot(xy);

				for (int k = 0; k < surXY.size(); k++)
				{
					Square::GetInst()->Squares[surXY[k].y * Square_Number + surXY[k].x].Color = Color;

					MaxLineInfo testMax = Event::GetInst()->GetMaxLine();
					
					if (Color == 'B')
					{
						Max_Prev = MaxSize;
						MaxSize = Event::GetInst()->GetMax(MaxSize, testMax.BlackXY.size());

						if (Max_Prev != MaxSize)
						{
							Coordinates.x = surXY[k].x;
							Coordinates.y = surXY[k].y;
						}
					}
					
					if (Color == 'W')
					{
						Max_Prev = MaxSize;
						MaxSize = Event::GetInst()->GetMax(MaxSize, testMax.WhiteXY.size());

						if (Max_Prev != MaxSize)
						{
							Coordinates.x = surXY[k].x;
							Coordinates.y = surXY[k].y;
						}
					}
					
					Square::GetInst()->Squares[surXY[k].y * Square_Number + surXY[k].x].Color = 'N';
				}
			}
		}
	}

	return Coordinates;
}

vector<XY> OmokAI::CheckDot(XY Coordinates)
{
	vector<XY> SurroundXY;
	
	for (int i = 0; i < 3; i++)
	{
		if (Square::GetInst()->GetPlateColor((Coordinates.x - 1) + i, Coordinates.y - 1) == 'N')
		{
			XY xy;
			
			xy.x = (Coordinates.x - 1) + i;
			xy.y = Coordinates.y - 1;

			SurroundXY.push_back(xy);
		}
	}
	
	if (Square::GetInst()->GetPlateColor(Coordinates.x - 1, Coordinates.y) == 'N')
	{
		XY xy;
		
		xy.x = Coordinates.x - 1;
		xy.y = Coordinates.y;
		
		SurroundXY.push_back(xy);
	}
	else if (Square::GetInst()->GetPlateColor(Coordinates.x + 1, Coordinates.y) == 'N')
	{
		XY xy;
		
		xy.x = Coordinates.x + 1;
		xy.y = Coordinates.y;
		
		SurroundXY.push_back(xy);
	}
	
	for (int i = 0; i <= 3; i++)
	{
		if (Square::GetInst()->GetPlateColor((Coordinates.x - 1) + i, Coordinates.y + 1) == 'N')
		{
			XY xy;
			
			xy.x = (Coordinates.x - 1) + i;
			xy.y = Coordinates.y + 1;
			
			SurroundXY.push_back(xy);
		}
	}
	
	return SurroundXY;
}

// practice.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "practice.h"
#include "pch.h"
#include "Core.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRACTICE, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보 등록
    MyRegisterClass(hInstance);

    // 윈도우 생성 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    Core::GetInst()->Init(hWnd);

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRACTICE));

    MSG msg;

    /*
         // 기본 메시지 루프입니다 :
        
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        GetMessage : 메세지 큐에서 메세지가 확인될때까지 대기 그래서 비효율적임

        GetMessage의 문제점 : 윈도우의 어떤 메세지가 있을때만 코드가 작동함 그래서 
                             사용자가 내부적으로 만든 이벤트에는 반응하지 않고 오직 윈도우 이벤트에만 코드가 작동함
                             그래서 구조를 바꿔 줘야함 메세지가 있던 없던 반환을 하는 구조로
                             그게 PeekMessage 함수임
    */

    /*
        PeekMessage 함수 : Peek의 뜻은 몰래 보다라는 뜻 
                           그래서 GetMessage는 메세지를 큐에서 Get(가져온다)라는 뜻이고 
                           PeekMessage는 메세지를 슬쩍 본다는 뜻임(있든 없든 메세지를 봄)
        
        PM_REMOVE : 메세지가 있든 없든 항상 메세지를 보는데 만약 메세지가 있다면 메세지큐에서 제거함
                    만약 이코드를 안적어주면 메세지가 삭제가 되지 않고 계속 쌓여있게됨

        근데 GetMessage(&msg, nullptr, 0, 0) 함수는 반환값이 true,false 임
        그래서 WM_QUIT 이 들어오면 false를 반환함(메세지가 없음) 그래서 while 문의 조건문으로 쓸 수 있엇음 
        
        근데 PeekMessage 함수는 메세지가 없어도 반환함 하지만 이함수도 true,false를 반환함
        메세지가 있었으면 true, 없다면 false를 반환함
        그래서 메세지가 없는 데 처리하라는게 말이 안되기 때문에 while 문의 조건문으로 쓰기 힘듬
        그래서 if문을 while 문안에 만들어줌
    */

    while (true)
    {
        while (Core::GetInst()->isRun())
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                /*
                    메세지가 있다면 이 조건문 안으로 들어오게 됨 근데 만약 그 메세지가 WM_QUIT 라면 break로 while 문을 나감
                */
                if (msg.message == WM_QUIT)
                    break;

                if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            else
            {
                /*
                    메세지가 없다면 이곳으로 오게됨
                    그래서 사용자가 원하는 작업을 여기에서 실행 할 수 있음
                */
                Core::GetInst()->Progress();
            }
        }

        Core::GetInst()->Game_Restart();
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRACTICE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PRACTICE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   /*
        hInstance 와 hWnd 의 차이

        HWND : 핸들 윈도우 약자 , 윈도우의 핸들번호를 저장해서 사용 , 하나의 프로그램에서 많은양의 윈도우를 띄울수 있다.
               즉 윈도우창의 번호들(HWND) 로 구분하는것이다.
        
        HINSTANCE : 핸들 인스턴스  , 프로그램의 인스턴스 식별자 , 쉽게 보면 프로그램 자체의 실체화된 주소.
        
        결론 : HINSTANCE는 프로그램 자체의 핸들이며 , HWND는 프로그램안의 윈도우창의 번호이다
   */
      hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//int g_x = 0;
//int g_y = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역이 발생한 경우
        {
            PAINTSTRUCT ps;
            // hWnd 는 이 윈도의 아이디 값(아이디 값이 있어야 이 윈도우에 그릴 수 있음) 
            
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context: 그리기 위해 그림 도구를 사용하기 위해 
                                             // 필요한 정보들이 있는 아이디값 (비유하자면 미술도구를 사용하기전 미술가방같은 느낌)
            //DC의 펜은 기본펜(Black)
            //DC의 브러쉬는  기본 브러쉬(White)

            /*
                펜 스타일:
                PS_SOLID : 직선
                PS_DOT : 점선 
            */

            //   //직접 펜을 만들어서 DC에 지급  
            //   HPEN bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
            //   HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
                 
            //   /*
            //       SelectObject 함수 : DC에게 내가 직접 만든 펜으로 교체해주는 함수
            //                           하지만 이 함수는 꼭 펜이 아니라 모든 타입을 받을 수 있는 void 포인터 형식임(범용적으로 쓰이는 함수 여서)
            //                           그래서 항상 이 함수를 사용할땐 사용자가 적절하게 타입 캐스팅으로 변환해서 써줘야함
            //   */
                 
            //   HPEN x = (HPEN)SelectObject(hdc, bluePen);
            //   HBRUSH y = (HBRUSH)SelectObject(hdc, redBrush);  
            //   
            //   Rectangle(hdc, g_x - 10, g_y + 10, g_x + 100, g_y - 100);
                 
            //   /*
            //       만약 펜을 지우고 싶다면 
            //       SelectObject(hdc, bluePen); 코드로 원래 펜으로 되돌려주고
            //       DeleteObject(bluePen); 으로 내가 만들었던 펜을 지워줌
            //   */

            EndPaint(hWnd, &ps);
        }
        break;
    //case WM_KEYDOWN:
    //    {
    //        /*
    //            WM_KEYDOWN 뜻 : 아무키나 눌렸을때 반응함 따라서 아무키나 누르면 이 case 로 들어오게 해줌
    //                            이때 어떤키인지 알기 위해 부가인자 값이 WPARAM 과 LPARAM 임
    //                            만약 message가 마우스 클릭이라면 마우스 좌표가 LPARAM 으로 들어오고
    //                            키가 눌린 경우에는 어떤 키가 눌렸는지에 대한 추가정보가 WPARAM 으로 들어옴
    //        */
    //        switch (wParam)
    //        {
    //        case VK_UP: 
    //            break;
    //        case VK_DOWN: 
    //            break;
    //        case VK_LEFT: 
    //            break;
    //        case VK_RIGHT:
    //            break;
    //        default:
    //            break;
    //        }
    //    }
    //    break;
    //case WM_LBUTTONDOWN:
    //    {
    //        /*
    //            WM_LBUTTONDOWN 뜻 : 마우스를 아무곳에나 클릭하면 반응함
    //                                따라서 마우스를 클릭하면 이 case로 들어옴
    //            
    //            LOWORD 와 HIWORD : 마우스의 좌표자료를 가져오는 LPARAM은 4바이트짜리 자료형임 
    //                               그래서 x축 y축 좌표를 각각 2바이트씩 나눠서 표현함(0~2^16)
    //                               그래서 좌표를 가져오려면 LPARAM을 비트연산 해야하는데 이 연산을 
    //                               메크로 함수로 만들어 놓은게 LOWORD 와 HIWORD 임
    //                               LOWORD가 x좌표를 연산 , HIWORD 가 y좌표를 연산함
    //                               이때 이 좌표의 기준은 이 프로그램의 클라이언트가 기준임
    //        */
    //        g_x = LOWORD(lParam);
    //        g_y = HIWORD(lParam);
    //        /*
    //            컴퓨터는 무효화 영역이 발생해야지만 그릴 수 있음
    //            그래서 InvalidateRect 함수로 무효화 영역을 강제로 발생시켜서
    //            WM_PAINT case에 들어와서 그리는 코드가 발생하도록 함
    //        */
    //        InvalidateRect(hWnd, nullptr, false);
    //    }
    //     break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

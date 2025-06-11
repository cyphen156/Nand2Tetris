// Nand2Tetris.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Nand2Tetris.h"
#include "CH01_boolean.h"
#include "ALU.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 커스텀 변수를 정의합니다.
bool inputA = false;
bool inputB = false;
bool result = false;
bool inputSel = false;
bool result_or = false;
bool result_not = false;
bool result_xor = false;
bool result_nor = false;
bool result_nand = false;
bool result_mux = false;
bool result_demux_a = false;
bool result_demux_b = false;

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
    LoadStringW(hInstance, IDC_NAND2TETRIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NAND2TETRIS));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            
            // 메시지가 없을 때 수행할 작업이 있다면 여기에 작성합니다.
            // 예: 애니메이션 업데이트, 게임 루프 등
        }
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NAND2TETRIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_NAND2TETRIS);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // 입력 버튼
        CreateWindowW(L"button", L"A : 0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)ID_BTN_INPUT_A, hInst, NULL);
        CreateWindowW(L"button", L"B : 0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 60, 100, 25, hWnd, (HMENU)ID_BTN_INPUT_B, hInst, NULL);
        CreateWindowW(L"button", L"SEL = 0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 100, 100, 25, hWnd, (HMENU)ID_BTN_SEL_TOGGLE, hInst, NULL);

        // 연산 버튼
        CreateWindowW(L"button", L"AND", WS_CHILD | WS_VISIBLE, 140, 20, 240, 25, hWnd, (HMENU)ID_BTN_AND, hInst, NULL);
        CreateWindowW(L"button", L"OR", WS_CHILD | WS_VISIBLE, 140, 60, 240, 25, hWnd, (HMENU)ID_BTN_OR, hInst, NULL);
        CreateWindowW(L"button", L"NOT(A)", WS_CHILD | WS_VISIBLE, 140, 100, 240, 25, hWnd, (HMENU)ID_BTN_NOT, hInst, NULL);
        CreateWindowW(L"button", L"XOR", WS_CHILD | WS_VISIBLE, 140, 140, 240, 25, hWnd, (HMENU)ID_BTN_XOR, hInst, NULL);
        CreateWindowW(L"button", L"NOR", WS_CHILD | WS_VISIBLE, 140, 180, 240, 25, hWnd, (HMENU)ID_BTN_NOR, hInst, NULL);
        CreateWindowW(L"button", L"NAND", WS_CHILD | WS_VISIBLE, 140, 220, 240, 25, hWnd, (HMENU)ID_BTN_NAND, hInst, NULL);
        CreateWindowW(L"button", L"MUX", WS_CHILD | WS_VISIBLE, 140, 260, 240, 25, hWnd, (HMENU)ID_BTN_MUX, hInst, NULL);
        CreateWindowW(L"button", L"DEMUX", WS_CHILD | WS_VISIBLE, 140, 300, 240, 25, hWnd, (HMENU)ID_BTN_DEMUX, hInst, NULL);

        // 출력 Static
        CreateWindowW(L"static", L"출력", WS_CHILD | WS_VISIBLE, 420, 20, 200, 25, hWnd, (HMENU)ID_STATIC_OUTPUT, hInst, NULL);
        CreateWindowW(L"static", L"MUX 결과", WS_CHILD | WS_VISIBLE, 420, 60, 200, 25, hWnd, (HMENU)ID_STATIC_MUX_OUTPUT, hInst, NULL);
        CreateWindowW(L"static", L"DEMUX A", WS_CHILD | WS_VISIBLE, 420, 100, 200, 25, hWnd, (HMENU)ID_STATIC_DEMUX_A, hInst, NULL);
        CreateWindowW(L"static", L"DEMUX B", WS_CHILD | WS_VISIBLE, 420, 140, 200, 25, hWnd, (HMENU)ID_STATIC_DEMUX_B, hInst, NULL);
        
        // ----------------------------
        // ALU 입력/제어 입력 라인 (하단)
        // ----------------------------

        // ALU 입력 텍스트 박스: X
        CreateWindowW(L"static", L"X 입력:", WS_CHILD | WS_VISIBLE, 20, 360, 60, 25, hWnd, NULL, hInst, NULL);
        CreateWindowW(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 80, 360, 200, 25, hWnd, (HMENU)ID_EDIT_ALU_X, hInst, NULL);

        // ALU 입력 텍스트 박스: Y
        CreateWindowW(L"static", L"Y 입력:", WS_CHILD | WS_VISIBLE, 20, 400, 60, 25, hWnd, NULL, hInst, NULL);
        CreateWindowW(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 80, 400, 200, 25, hWnd, (HMENU)ID_EDIT_ALU_Y, hInst, NULL);

        // ALU 제어 신호 버튼들 (토글 방식)
        CreateWindowW(L"button", L"ZX", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 300, 360, 60, 25, hWnd, (HMENU)ID_ALU_ZX, hInst, NULL);
        CreateWindowW(L"button", L"NX", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 360, 360, 60, 25, hWnd, (HMENU)ID_ALU_NX, hInst, NULL);
        CreateWindowW(L"button", L"ZY", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 420, 360, 60, 25, hWnd, (HMENU)ID_ALU_ZY, hInst, NULL);
        CreateWindowW(L"button", L"NY", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 480, 360, 60, 25, hWnd, (HMENU)ID_ALU_NY, hInst, NULL);
        CreateWindowW(L"button", L"F", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 540, 360, 60, 25, hWnd, (HMENU)ID_ALU_F, hInst, NULL);
        CreateWindowW(L"button", L"NO", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 600, 360, 60, 25, hWnd, (HMENU)ID_ALU_NO, hInst, NULL);

        // ALU 실행 버튼
        CreateWindowW(L"button", L"ALU 계산", WS_CHILD | WS_VISIBLE, 300, 400, 120, 30, hWnd, (HMENU)ID_BTN_ALU_EXEC, hInst, NULL);

        // ALU 결과 출력 Static
        CreateWindowW(L"static", L"ALU 출력:", WS_CHILD | WS_VISIBLE, 20, 440, 100, 25, hWnd, NULL, hInst, NULL);
        CreateWindowW(L"static", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 120, 440, 400, 25, hWnd, (HMENU)ID_STATIC_ALU_OUT, hInst, NULL);

        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case ID_BTN_INPUT_A:
                inputA = !inputA;
                SetWindowText(GetDlgItem(hWnd, ID_BTN_INPUT_A), inputA ? L"A : 1" : L"A : 0");
                break;

            case ID_BTN_INPUT_B:
                inputB = !inputB;
                SetWindowText(GetDlgItem(hWnd, ID_BTN_INPUT_B), inputB ? L"B : 1" : L"B : 0");
                break;
            case ID_BTN_SEL_TOGGLE:
                inputSel = !inputSel;
                SetWindowText(GetDlgItem(hWnd, ID_BTN_SEL_TOGGLE), inputSel ? L"SEL=A" : L"SEL=B");
                break;
            
            case ID_BTN_AND:
                result = CH01_boolean::And(inputA, inputB);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result ? L"AND = 1" : L"AND = 0");
                break;

            case ID_BTN_OR:
                result_or = CH01_boolean::Or(inputA, inputB);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result_or ? L"OR = 1" : L"OR = 0");
                break;

            case ID_BTN_NOT:
                result_not = CH01_boolean::Not(inputA);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result_not ? L"NOT(A) = 1" : L"NOT(A) = 0");
                break;

            case ID_BTN_XOR:
                result_xor = CH01_boolean::Xor(inputA, inputB);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result_xor ? L"XOR = 1" : L"XOR = 0");
                break;

            case ID_BTN_NOR:
                result_nor = CH01_boolean::Nor(inputA, inputB);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result_nor ? L"NOR = 1" : L"NOR = 0");
                break;

            case ID_BTN_NAND:
                result_nand = CH01_boolean::Nand(inputA, inputB);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_OUTPUT), result_nand ? L"NAND = 1" : L"NAND = 0");
                break;

            case ID_BTN_MUX:
                result_mux = CH01_boolean::MUX(inputA, inputB, inputSel);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_MUX_OUTPUT), result_mux ? L"MUX = 1" : L"MUX = 0");
                break;

            case ID_BTN_DEMUX:
                CH01_boolean::Demux(inputA, inputSel, result_demux_a, result_demux_b);
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_DEMUX_A), result_demux_a ? L"DEMUX A = 1" : L"DEMUX A = 0");
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_DEMUX_B), result_demux_b ? L"DEMUX B = 1" : L"DEMUX B = 0");
                break;

            case ID_BTN_ALU_EXEC:
            {
                wchar_t bufX[65] = { 0 };
                wchar_t bufY[65] = { 0 };

                GetWindowText(GetDlgItem(hWnd, ID_EDIT_ALU_X), bufX, 65);
                GetWindowText(GetDlgItem(hWnd, ID_EDIT_ALU_Y), bufY, 65);

                int lenX = wcslen(bufX);
                int lenY = wcslen(bufY);
                int bitSize = max(lenX, lenY);

                if (bitSize < 1 || bitSize > 64)
                {
                    MessageBox(hWnd, L"입력 비트 수는 1~64 사이여야 합니다.", L"오류", MB_OK | MB_ICONERROR);
                    break;
                }

                bool x[64] = { false };
                bool y[64] = { false };
                bool out[64] = { false };
                bool zr = false;
                bool ng = false;

                // 입력 비트 문자열을 오른쪽 정렬하여 배열로 변환 (LSB가 인덱스 0)
                for (int i = 0; i < bitSize; ++i)
                {
                    if (i < lenX)
                        x[i] = (bufX[lenX - 1 - i] == L'1');
                    if (i < lenY)
                        y[i] = (bufY[lenY - 1 - i] == L'1');
                }

                // 제어 비트 확인
                bool zx = (SendMessage(GetDlgItem(hWnd, ID_ALU_ZX), BM_GETCHECK, 0, 0) == BST_CHECKED);
                bool nx = (SendMessage(GetDlgItem(hWnd, ID_ALU_NX), BM_GETCHECK, 0, 0) == BST_CHECKED);
                bool zy = (SendMessage(GetDlgItem(hWnd, ID_ALU_ZY), BM_GETCHECK, 0, 0) == BST_CHECKED);
                bool ny = (SendMessage(GetDlgItem(hWnd, ID_ALU_NY), BM_GETCHECK, 0, 0) == BST_CHECKED);
                bool f = (SendMessage(GetDlgItem(hWnd, ID_ALU_F), BM_GETCHECK, 0, 0) == BST_CHECKED);
                bool no = (SendMessage(GetDlgItem(hWnd, ID_ALU_NO), BM_GETCHECK, 0, 0) == BST_CHECKED);

                if (!ALU::Compute(x, y, zx, nx, zy, ny, f, no, out, zr, ng, bitSize))
                {
                    MessageBox(hWnd, L"ALU 연산 실패", L"에러", MB_OK | MB_ICONERROR);
                    break;
                }

                // 결과를 문자열로 변환
                wchar_t result[65] = { 0 };
                for (int i = 0; i < bitSize; ++i)
                {
                    result[bitSize - 1 - i] = out[i] ? L'1' : L'0';
                }

                // 결과 출력
                SetWindowText(GetDlgItem(hWnd, ID_STATIC_ALU_OUT), result);
            }
            break;

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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
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

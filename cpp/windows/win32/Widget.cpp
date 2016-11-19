#include <windows.h>

#define IDC_MAIN_BUTTON	101                             // Button identifier
#define IDC_MAIN_EDIT	102                             // Edit box identifier
HWND hEdit;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void error_handle();
void create_widget(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.cbWndExtra = NULL;
    wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wClass.hIcon = NULL;
    wClass.hIconSm = NULL;
    wClass.hInstance = hInst;
    wClass.lpfnWndProc = (WNDPROC)WinProc;
    wClass.lpszClassName = L"Window Class";
    wClass.lpszMenuName = NULL;
    wClass.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClassEx(&wClass))
        error_handle();

    HWND hWnd = CreateWindowEx(NULL,
        L"Window Class",
        L"Windows application",
        WS_OVERLAPPEDWINDOW,
        200,
        200,
        640,
        480,
        NULL,
        NULL,
        hInst,
        NULL);

    if (!hWnd)
        error_handle();

    ShowWindow(hWnd, nShowCmd);

    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        // WM_CREATE used to populate our window with all sorts of windows assets, initialize Winsock
        case WM_CREATE:
        {
                          create_widget(hWnd);
        }
        break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_MAIN_BUTTON:
                {
                    wchar_t buffer[256] = L"";
                    SendMessage(hEdit,
                        WM_GETTEXT,
                        sizeof(buffer) / sizeof(buffer[0]),
                        reinterpret_cast<LPARAM>(buffer));
                    MessageBox(NULL,
                        buffer,
                        L"Information",
                        MB_ICONINFORMATION);
                }
            break;
        }
        break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void create_widget(HWND hWnd){
    // Create an edit box
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE |
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        50,
        100,
        200,
        100,
        hWnd,
        (HMENU)IDC_MAIN_EDIT,
        GetModuleHandle(NULL),
        NULL);

    HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);

    SendMessage(hEdit,
        WM_SETFONT,
        (WPARAM)hfDefault,
        MAKELPARAM(FALSE, 0));

    SendMessage(hEdit,
        WM_SETTEXT,
        NULL,
        (LPARAM)"Insert text here...");

    // Create a push button
    HWND hWndButton = CreateWindowEx(NULL,
        L"BUTTON",
        L"OK",
        WS_TABSTOP | WS_VISIBLE |
        WS_CHILD | BS_DEFPUSHBUTTON,
        50,
        220,
        100,
        24,
        hWnd,
        (HMENU)IDC_MAIN_BUTTON,
        GetModuleHandle(NULL),
        NULL);
    SendMessage(hWndButton,
        WM_SETFONT,
        (WPARAM)hfDefault,
        MAKELPARAM(FALSE, 0));
}

void error_handle(){
    int nResult = GetLastError();

    MessageBox(NULL,
        L"Window creation failed",
        L"Window Creation Failed",
        MB_ICONERROR);
}
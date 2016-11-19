#include <windows.h>

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void error_handle();

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSEX wClass;
    ZeroMemory(&wClass, sizeof(WNDCLASSEX));
    wClass.cbClsExtra = NULL;                               // Additional parameters
    wClass.cbSize = sizeof(WNDCLASSEX);                     // Specifies the size of the window class
    wClass.cbWndExtra = NULL;                               // Additional parameters
    wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;            // Sets background color for the window
    wClass.hCursor = LoadCursor(NULL, IDC_ARROW);           // The cursor that will appear in the window
    wClass.hIcon = NULL;                                    // Icon for the window
    wClass.hIconSm = NULL;                                  // Small icon for the window
    wClass.hInstance = hInst;                               // Handle to the application instance
    wClass.lpfnWndProc = (WNDPROC)WinProc;                  // The callback procedure
    wClass.lpszClassName = L"Window Class";                 // The unique name of the window class
    wClass.lpszMenuName = NULL;                             // Used for menus
    wClass.style = CS_HREDRAW | CS_VREDRAW;                 // The look and feel of the window

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
        TranslateMessage(&msg);                             // translate virtual key messages to character messages
        DispatchMessage(&msg);                              // send messages to the callback procedure
    }

    return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void error_handle(){
    int nResult = GetLastError();

    MessageBox(NULL,
        L"Window creation failed",
        L"Window Creation Failed",
        MB_ICONERROR);
}
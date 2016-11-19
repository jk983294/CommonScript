#include <windows.h>

INT WINAPI wWinMain(HINSTANCE hInst,
    HINSTANCE hPrevInst,
    LPWSTR lpCmdLine,
    INT nShowCmd)
{
    int nResult = MessageBox(NULL,
        L"An example of Cancel,Retry,Continue",
        L"Hello Message Box!",
        MB_ICONERROR | MB_ABORTRETRYIGNORE);

    switch (nResult)
    {
    case IDABORT:
        // 'Abort' was pressed
        break;
    case IDRETRY:
        // 'Retry' was pressed
        break;
    case IDIGNORE:
        // 'Ignore' was pressed
        break;
    }

    return 0;
}
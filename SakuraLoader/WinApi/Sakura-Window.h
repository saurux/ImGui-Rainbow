#pragma once

#include <windows.h>
#include <windowsx.h>

#include "../WinGUI/Present.h"

int vCreateWindow()
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"Sakura";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx
    (
        WS_EX_LAYERED, // Hide Background
        wc.lpszClassName,    // name of the window class
        0,   // title of the window
        WS_POPUP,    // window style
        (GetSystemMetrics(SM_CXSCREEN) - Width) / 2,    // x-position of the window - center
        (GetSystemMetrics(SM_CYSCREEN) - Height) / 2,    // y-position of the window - center
        Width,    // width of the window
        Height,    // height of the window
        NULL,    // we have no parent window, NULL
        NULL,    // we aren't using menus, NULL
        NULL,    // application handle
        NULL);    // used with multiple windows, NULL

    SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);

    if (CreateDeviceD3D(hWnd) < 0)
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    bool bTexture = LoadTextureFromFile(("C:\\123.png"), &pTexture, &WarfaceX, &WarfaceY);
    IM_ASSERT(bTexture);

    PaintGui();

    //ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(pDevice, pDevContext);

    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide console

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        if (bIsOpen == false) ExitProcess(EXIT_SUCCESS);
        // Render IMGUI
       
        StartFrame(Present);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hWnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return msg.wParam;
}
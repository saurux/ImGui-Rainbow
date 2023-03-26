#pragma once

#include <d3dx9math.h>
#include <d3d11.h>
#include <d3dx11.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

#include <WinUser.h>
#include <strsafe.h>

#define STB_IMAGE_IMPLEMENTATION 1
#include <stb_image.h>

#include "Color.h"

ImFont* pFont;

int Width = 700;
int Height = 400;

IDXGISwapChain* pSwapChain;
ID3D11Device* pDevice;                     
ID3D11DeviceContext* pDevContext;
ID3D11RenderTargetView* pRenderBuffer;

bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    // Load from disk into a raw RGBA buffer
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create texture
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = image_width;
    desc.Height = image_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;

    ID3D11Texture2D* pTexture = NULL;
    D3D11_SUBRESOURCE_DATA subResource;
    subResource.pSysMem = image_data;
    subResource.SysMemPitch = desc.Width * 4;
    subResource.SysMemSlicePitch = 0;
    pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

    // Create texture view
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    ZeroMemory(&srvDesc, sizeof(srvDesc));
    srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = desc.MipLevels;
    srvDesc.Texture2D.MostDetailedMip = 0;
    pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
    pTexture->Release();

    *out_width = image_width;
    *out_height = image_height;
    stbi_image_free(image_data);

    return true;
}

void CleanupRenderTarget()
{
    if (pRenderBuffer) { pRenderBuffer->Release(); pRenderBuffer = NULL; }
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (pSwapChain) { pSwapChain->Release(); pSwapChain = NULL; }
    if (pDevContext) { pDevContext->Release(); pDevContext = NULL; }
    if (pDevice) { pDevice->Release(); pDevice = NULL; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderBuffer);
    pBackBuffer->Release();
}

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, &featureLevel, &pDevContext) != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (pDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_NCHITTEST:
    {
        ImVec2 Shit = ImGui::GetMousePos();
        if (Shit.y < 25 && Shit.x < Width - 25)
        {
            LRESULT hit = DefWindowProc(hWnd, msg, wParam, lParam);
            if (hit == HTCLIENT) hit = HTCAPTION;
            return hit;
        }
        else break;
    }

    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;

    default:
        ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
void RenderFrame(void)
{
    // clear the back buffer to a deep blue
    //pDevContext->ClearRenderTargetView(pRenderBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // do 3D rendering on the back buffer here

    // switch the back buffer and the front buffer
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    pDevContext->OMSetRenderTargets(1, &pRenderBuffer, NULL);
    pDevContext->ClearRenderTargetView(pRenderBuffer, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    pSwapChain->Present(1, 0); // Present with vsync
}

void BeginFrame()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void StartFrame(void (&RenderFunction)())
{
    BeginFrame();

    ImGui::PushFont(pFont);
    RenderFunction();
    ImGui::PopFont();

    RenderFrame();
}
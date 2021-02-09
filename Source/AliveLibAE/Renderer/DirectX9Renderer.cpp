#include "stdafx.h"
#include "DirectX9Renderer.hpp"

#ifdef _WIN32

#undef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0900
#include <d3d9.h>

struct CUSTOMVERTEX { FLOAT X, Y, Z, RHW; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

void DirectX9Renderer::Destroy()
{
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
}

bool DirectX9Renderer::Create(TWindowHandleType window)
{
    // Find the directx9 driver
    const int numDrivers = SDL_GetNumRenderDrivers();
    if (numDrivers < 0)
    {
        LOG_ERROR("Failed to get driver count " << SDL_GetError());
    }

    LOG_INFO("Got " << numDrivers << " drivers");

    int index = -1;
    for (int i = 0; i < numDrivers; i++)
    {
        SDL_RendererInfo info = {};
        if (SDL_GetRenderDriverInfo(i, &info) < 0)
        {
            LOG_WARNING("Failed to get render " << i << " info " << SDL_GetError());
        }
        else
        {
            LOG_INFO(i << " name " << info.name);
            if (info.name && strstr(info.name, "direct3d"))
            {
                index = i;
                break;
            }
        }
    }

    if (index == -1)
    {
        LOG_WARNING("DirectX9 SDL2 driver not found");
        return false;
    }

    mRenderer = SDL_CreateRenderer(window, index, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!mRenderer)
    {
        LOG_ERROR("Failed to create renderer " << SDL_GetError());
        return false;
    }

    mDevice = SDL_RenderGetD3D9Device(mRenderer);
    if (!mDevice)
    {
        Destroy();

        LOG_ERROR("Couldnt get DirectX9 device " << SDL_GetError());
        return false;
    }

    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window, &w, &h);
    float aspectX = (float)w / 640.0f;
    float aspectY = (float)h / 480.0f;

    // create the vertices using the CUSTOMVERTEX struct
    CUSTOMVERTEX vertices[] =
    {
        { 400.0f * aspectX, 62.5f * aspectY, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 650.0f * aspectX, 500.0f * aspectY, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 150.0f * aspectX, 500.0f * aspectY, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    // create a vertex buffer interface called v_buffer
    mDevice->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
        0,
        CUSTOMFVF,
        D3DPOOL_MANAGED,
        &v_buffer,
        NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

    return true;
}

void DirectX9Renderer::Clear(BYTE /*r*/, BYTE /*g*/, BYTE /*b*/)
{
    //mDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET | D3DCLEAR_STENCIL, D3DCOLOR_XRGB(r, g, b), 1.0f, 0);
}

void DirectX9Renderer::StartFrame(int /*xOff*/, int /*yOff*/)
{

}

void DirectX9Renderer::EndFrame()
{
    /*
    D3DVIEWPORT9 viewPort = {};
    viewPort.Width = 2000;
    viewPort.Height = 2000;
    HRESULT hr = mDevice->SetViewport(&viewPort);
    if (FAILED(hr))
    {
        abort();
    }*/

//    SDL_RenderPresent(mRenderer);
    mDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    mDevice->BeginScene();

    // select which vertex format we are using
    mDevice->SetFVF(CUSTOMFVF);

    // select the vertex buffer to display
    mDevice->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

    // copy the vertex buffer to the back buffer
    mDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

    mDevice->EndScene();

    mDevice->Present(NULL, NULL, NULL, NULL);
}

void DirectX9Renderer::BltBackBuffer(const SDL_Rect* /*pCopyRect*/, const SDL_Rect* /*pDst*/)
{

}

void DirectX9Renderer::OutputSize(int* w, int* h)
{
    SDL_GetRendererOutputSize(mRenderer, w, h);
}

bool DirectX9Renderer::UpdateBackBuffer(const void* /*pPixels*/, int /*pitch*/)
{
    return true;
}

void DirectX9Renderer::CreateBackBuffer(bool /*filter*/, int /*format*/, int /*w*/, int /*h*/)
{

}


void DirectX9Renderer::WindowSizeChanged(TWindowHandleType window)
{
    Destroy();
    Create(window);
}

void DirectX9Renderer::SetTPage(short /*tPage*/)
{

}

void DirectX9Renderer::SetClip(Prim_PrimClipper& /*clipper*/)
{

}

void DirectX9Renderer::Draw(Prim_Sprt& /*sprt*/)
{

}

void DirectX9Renderer::Draw(Prim_GasEffect& /*gasEffect*/)
{

}

void DirectX9Renderer::Draw(Prim_Tile& /*tile*/)
{

}

void DirectX9Renderer::Draw(Line_F2& /*line*/)
{

}

void DirectX9Renderer::Draw(Line_G2& /*line*/)
{

}

void DirectX9Renderer::Draw(Line_G4& /*line*/)
{

}

void DirectX9Renderer::Draw(Poly_F3& /*poly*/)
{

}

void DirectX9Renderer::Draw(Poly_G3& /*poly*/)
{

}

void DirectX9Renderer::Draw(Poly_F4& /*poly*/)
{

}

void DirectX9Renderer::Draw(Poly_FT4& /*poly*/)
{

}

void DirectX9Renderer::Draw(Poly_G4& /*poly*/)
{

}

const char* DirectXError(HRESULT hr)
{
    switch (hr)
    {
    case D3DERR_WRONGTEXTUREFORMAT: return "D3DERR_WRONGTEXTUREFORMAT";
    case D3DERR_UNSUPPORTEDCOLOROPERATION: return "D3DERR_UNSUPPORTEDCOLOROPERATION";
    case D3DERR_UNSUPPORTEDCOLORARG: return "D3DERR_UNSUPPORTEDCOLORARG";
    case D3DERR_UNSUPPORTEDALPHAOPERATION: return "D3DERR_UNSUPPORTEDALPHAOPERATION";
    case D3DERR_UNSUPPORTEDALPHAARG: return "D3DERR_UNSUPPORTEDALPHAARG";
    case D3DERR_TOOMANYOPERATIONS: return "D3DERR_TOOMANYOPERATIONS";
    case D3DERR_CONFLICTINGTEXTUREFILTER: return "D3DERR_CONFLICTINGTEXTUREFILTER";
    case D3DERR_UNSUPPORTEDFACTORVALUE: return "D3DERR_UNSUPPORTEDFACTORVALUE";
    case D3DERR_CONFLICTINGRENDERSTATE: return "D3DERR_CONFLICTINGRENDERSTATE";
    case D3DERR_UNSUPPORTEDTEXTUREFILTER: return "D3DERR_UNSUPPORTEDTEXTUREFILTER";
    case D3DERR_CONFLICTINGTEXTUREPALETTE: return "D3DERR_CONFLICTINGTEXTUREPALETTE";
    case D3DERR_DRIVERINTERNALERROR: return "D3DERR_DRIVERINTERNALERROR";
    case D3DERR_NOTFOUND: return "D3DERR_NOTFOUND";
    case D3DERR_MOREDATA: return "D3DERR_MOREDATA";
    case D3DERR_DEVICELOST: return "D3DERR_DEVICELOST";
    case D3DERR_DEVICENOTRESET: return "D3DERR_DEVICENOTRESET";
    case D3DERR_NOTAVAILABLE: return "D3DERR_NOTAVAILABLE";
    case D3DERR_OUTOFVIDEOMEMORY: return "D3DERR_OUTOFVIDEOMEMORY";
    case D3DERR_INVALIDDEVICE: return "D3DERR_INVALIDDEVICE";
    case D3DERR_INVALIDCALL: return "D3DERR_INVALIDCALL";
    case D3DERR_DRIVERINVALIDCALL: return "D3DERR_DRIVERINVALIDCALL";
    case D3DERR_WASSTILLDRAWING: return "D3DERR_WASSTILLDRAWING";
    case D3DOK_NOAUTOGEN: return "D3DOK_NOAUTOGEN";
    }
    return "Unknown";
}

void DirectX9Renderer::Upload(BitDepth /*bitDepth*/, const PSX_RECT& /*rect*/, const BYTE* /*pPixels*/)
{
    /*
    LPDIRECT3DSURFACE9 surface = nullptr;
    LPDIRECT3DTEXTURE9 texture = nullptr;
    HANDLE hShared = nullptr;
    HRESULT hr = mDevice->CreateTexture(rect.w, rect.h, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8, D3DPOOL_SYSTEMMEM, &texture, &hShared);
    LOG_ERROR(DirectXError(hr));
    
    hr = texture->GetSurfaceLevel(0, &surface);
    D3DSURFACE_DESC desc;
    hr = surface->GetDesc(&desc);
    D3DLOCKED_RECT lock;
    hr =surface->LockRect(&lock, nullptr, D3DLOCK_DISCARD);
    
    for (UINT y = 0; y < desc.Height; y++)
    {
        u32* line = &((u32*)lock.pBits)[lock.Pitch / 4 * y];
        for (UINT x = 0; x < desc.Width; x++, line++)
            bmp.setPixel(x, y, *line);
    }
    hr = surface->UnlockRect();
    hr = surface->Release();


    switch (bitDepth)
    {
    case IRenderer::BitDepth::e16Bit:
        break;

    case IRenderer::BitDepth::e8Bit:
        break;

    case IRenderer::BitDepth::e4Bit:
        break;
    }
    */
}

#endif

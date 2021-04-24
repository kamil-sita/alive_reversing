#include "stdafx.h"
#include "VGA.hpp"
#include "Function.hpp"
#include "../AliveLibAE/VGA.hpp"

namespace AO {

ALIVE_VAR(1, 0xA8A4C0, Bitmap, sVGA_bmp_primary_A8A4C0, {});

EXPORT s32 CC VGA_FullScreenSet_490160(bool bFullScreen)
{
    return VGA_FullScreenSet_4F31F0(bFullScreen);
}

EXPORT s32 CC VGA_DisplaySet_490230(u16 width, u16 height, char bpp, u8 backbufferCount, TSurfaceType** ppSurface)
{
    return VGA_DisplaySet_4F32C0(width, height, bpp, backbufferCount, ppSurface);
}

EXPORT s32 CC VGA_GetPixelFormat_490E60()
{
    return VGA_GetPixelFormat_4F3EE0();
}

EXPORT void VGA_Shutdown_4900E0()
{
    VGA_Shutdown_4F3170();
}

}

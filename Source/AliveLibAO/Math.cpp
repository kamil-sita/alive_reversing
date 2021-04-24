#include "stdafx_ao.h"
#include "Function.hpp"
#include "Math.hpp"
#include "../AliveLibAE/Math.hpp"
#include "../AliveLibAE/FixedPoint.hpp" // TODO: Move Square root funcs

namespace AO {

ALIVE_ARY(1, 0x4BBE30, u8, 256, sRandomBytes_4BBE30,
{
        // TODO : Check this is the same, seems to be at a glance
    0x35, 0x85, 0x49, 0xE2, 0xA7, 0x42, 0xDF, 0x0B, 0x2D, 0x23, 0xDD, 0xDE, 0x1F, 0x17, 0xBB, 0xCF,
    0x4E, 0xA3, 0x19, 0x04, 0x71, 0x12, 0xB5, 0x50, 0x43, 0x64, 0xA0, 0x15, 0xDB, 0x22, 0xB0, 0x83,
    0x39, 0xEA, 0xAF, 0xC3, 0xD0, 0xCE, 0x77, 0x14, 0xAD, 0x56, 0x80, 0x5F, 0x6E, 0xD2, 0xD9, 0xC0,
    0xE6, 0xF6, 0x70, 0xF9, 0x05, 0x5A, 0x33, 0xC5, 0x8C, 0x73, 0xCB, 0xFA, 0x81, 0x3E, 0xD8, 0x9E,
    0x26, 0xD6, 0x0C, 0xBA, 0xAA, 0xCD, 0x7E, 0x9D, 0xFF, 0x1D, 0x06, 0xC4, 0xED, 0xF2, 0xF4, 0x5B,
    0x94, 0x9B, 0xA1, 0x5E, 0xB8, 0x37, 0xC1, 0xF1, 0x57, 0x7B, 0xD7, 0xFB, 0x25, 0xCC, 0x91, 0xF0,
    0x62, 0x7F, 0xFC, 0x1A, 0x96, 0x72, 0x2F, 0xDA, 0x38, 0xA2, 0x3A, 0xBF, 0xB4, 0xB1, 0xE8, 0xBD,
    0x0F, 0xF7, 0xAE, 0xA6, 0x88, 0x74, 0x2C, 0x7D, 0x01, 0xEC, 0x07, 0x24, 0x40, 0x34, 0x5D, 0x59,
    0x9C, 0x7A, 0x9A, 0xEE, 0xE7, 0x46, 0x9F, 0x61, 0x63, 0x30, 0xB2, 0x97, 0xEF, 0xAC, 0x76, 0x8E,
    0x75, 0xE4, 0xD3, 0xA9, 0x2A, 0x41, 0x00, 0xA5, 0xBC, 0x66, 0x51, 0xCA, 0x1B, 0xB7, 0x7C, 0x0E,
    0x18, 0x6B, 0xC7, 0x78, 0x84, 0x6A, 0x6C, 0x82, 0x60, 0xD5, 0x1C, 0x13, 0x55, 0x52, 0xB9, 0x53,
    0x32, 0x1E, 0xB6, 0x28, 0x4B, 0x8F, 0x11, 0x8D, 0x8B, 0xFD, 0x10, 0x67, 0x3F, 0xD1, 0x36, 0x45,
    0x86, 0xC9, 0x4A, 0x54, 0x4F, 0xF8, 0x79, 0x29, 0x69, 0x08, 0xE9, 0x89, 0x20, 0xAB, 0x6D, 0xE3,
    0xC6, 0x98, 0x99, 0xE5, 0x93, 0x48, 0x09, 0xE1, 0xF3, 0x47, 0x4C, 0xFE, 0x8A, 0x95, 0x3C, 0xEB,
    0x2B, 0x03, 0xF5, 0xA8, 0x58, 0x3D, 0xC2, 0x31, 0x65, 0xDC, 0x27, 0xBE, 0x21, 0x68, 0xE0, 0xB3,
    0xC8, 0xA4, 0x02, 0x2E, 0xD4, 0x3B, 0x6F, 0x5C, 0x87, 0x0A, 0x92, 0x0D, 0x4D, 0x16, 0x44, 0x90,
});

ALIVE_VAR(1, 0x50A228, BYTE, sRandomSeed_50A228, 0);

BYTE Math_NextRandom()
{
    if (!RunningAsInjectedDll())
    {
        return sRandomBytes_4BBE30[sRandomSeed_50A228++];
    }
    return ::Math_NextRandom(); // Ae ver
}

short CC Math_RandomRange_450F20(signed short min, signed short max)
{
    AE_IMPLEMENTED();
    return Math_RandomRange_496AB0(min, max);
}

FP CC Math_Sine_451110(BYTE v)
{
    AE_IMPLEMENTED();
    return Math_Sine_496DD0(v);
}

FP CC Math_Cosine_4510A0(BYTE v)
{
    AE_IMPLEMENTED();
    return Math_Cosine_496CD0(v);
}


s32 CC Math_Distance_451270(s32 x1, s32 y1, s32 x2, s32 y2)
{
    s32 dx = x1 - x2;
    if (dx < 0)
    {
        dx = x2 - x1;
    }

    s32 dy = y1 - y2;
    if (y1 - y2 < 0)
    {
        dy = y2 - y1;
    }

    if (dx <= dy)
    {
        return dy + dx / 2;
    }
    else
    {
        return dx + dy / 2;
    }
}

s32 CC Math_SquareRoot_Int_4511B0(s32 a1)
{
    AE_IMPLEMENTED();
    return Math_SquareRoot_Int_496E70(a1);
}

FP CC Math_SquareRoot_FP_451210(FP v)
{
    if (v == FP_FromInteger(0))
    {
        return FP_FromInteger(0);
    }

    if (v == FP_FromInteger(1))
    {
        return FP_FromInteger(1);
    }

    FP v2 = v / FP_FromInteger(2);
    for (s32 i = 6; i > 0; i--)
    {
        FP v4 = v / v2;
        v2 = (v2 + v4) / FP_FromInteger(2);
    }
    return v2;
}

}

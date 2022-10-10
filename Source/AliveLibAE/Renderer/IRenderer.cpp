#include "../stdafx.h"
#include "IRenderer.hpp"
#include "SoftwareRenderer.hpp"
#include "DirectX9Renderer.hpp"

//#if RENDERER_OPENGL
#include "OpenGLRenderer.hpp"
//#endif

#include "../AliveLibCommon/FatalError.hpp"

static IRenderer* gRenderer = nullptr;

IRenderer* IRenderer::GetRenderer()
{
    return gRenderer;
}

void IRenderer::CreateRenderer(Renderers type)
{
    if (gRenderer)
    {
        ALIVE_FATAL("Renderer already created");
    }

    switch (type)
    {

#if SDL_VERTEX_IS_SUPPORTED
        case Renderers::Software:
            gRenderer = new SoftwareRenderer();
            break;
#endif

//#if RENDERER_OPENGL
        case Renderers::OpenGL:
            gRenderer = new OpenGLRenderer();
            break;
//#endif

#ifdef _WIN32
        // Windows only
        case Renderers::DirectX9:
            gRenderer = new DirectX9Renderer();
            break;
#endif

        default:
            ALIVE_FATAL("Unknown or unsupported renderer type");
            break;
    }
}

void IRenderer::FreeRenderer()
{
    delete gRenderer;
    gRenderer = nullptr;
}

#include "Engine.h"

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <list>

#define GLM_FORCE_RADIANS 
#include <glm/gtc/matrix_transform.hpp>
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <sdl/Sdl.h>

#include "Font.h"
#include "GlContext.h"
#include "Sdl.h"
#include "SdlWindow.h"
#include "SdlSurface.h"
#include "Updater.h"

static const int WindowWidth = 750;
static const int WindowHeight = 600;
static const float MaxFrameTicks = 300.0f;
static const float TextScale = 0.5f;

struct Engine::EngineImplementation
{
    Sdl m_sdl;
    SdlWindow m_sdlWindow;
    GlContext m_glContext;
    std::unique_ptr<SdlSurface> m_pSdlSurfaceContainer[Engine::TEXTURE_MAX];
    std::unique_ptr<SdlSurface> m_pFontSdlSurface;
    float m_fElapsedTicks;
    float m_fLastFrameSeconds;
    Updater* m_pUpdater;
    bool m_bQuit;
        
    float m_fMouseX;
    float m_fMouseY;
    bool m_bMouseButtonDown;

    EngineImplementation()
        : m_sdl(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE),
        m_sdlWindow(WindowWidth, WindowHeight),
        m_glContext(m_sdlWindow),
        m_fLastFrameSeconds(1.0f / 60.0f),
        m_fMouseX(WindowWidth * 0.5f),
        m_fMouseY(WindowHeight * 0.5f),
        m_bMouseButtonDown(false),
        m_bQuit(false),
        m_pUpdater(nullptr),
        m_fElapsedTicks(static_cast<float>(SDL_GetTicks()))
    {
    }

    void Start();
    void ParseEvents();
};

Engine::Engine(const char* assetsDirectory)
    : m_pImpl(new EngineImplementation)
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(1);

    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string assets(assetsDirectory);
    std::string splash = assets; splash += "/splash.png";
    std::string background_alpha = assets; background_alpha += "/BackGround.tif";
    std::string background = assets; background += "/BackGround.jpg";
    std::string blue = assets; blue += "/Blue.png";
    std::string green = assets; green += "/Green.png";
    std::string purple = assets; purple += "/Purple.png";
    std::string red = assets; red += "/Red.png";
    std::string yellow = assets; yellow += "/Yellow.png";
    std::string font = assets; font += "/berlin_sans_demi_72_0.png";

    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_SPLASH].reset(new SdlSurface(splash.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_BACKGROUND_ALPHA].reset(new SdlSurface(background_alpha.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_BACKGROUND].reset(new SdlSurface(background.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_BLUE].reset(new SdlSurface(blue.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_GREEN].reset(new SdlSurface(green.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_PURPLE].reset(new SdlSurface(purple.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_RED].reset(new SdlSurface(red.c_str()));
    m_pImpl->m_pSdlSurfaceContainer[Engine::TEXTURE_YELLOW].reset(new SdlSurface(yellow.c_str()));
    m_pImpl->m_pFontSdlSurface.reset(new SdlSurface(font.c_str()));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WindowWidth, WindowHeight, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

Engine::~Engine()
{
}

float Engine::GetLastFrameSeconds() const
{
    return m_pImpl->m_fLastFrameSeconds;
}

float Engine::GetMouseX() const
{
    return m_pImpl->m_fMouseX;
}

float Engine::GetMouseY() const
{
    return m_pImpl->m_fMouseY;
}

bool Engine::GetMouseButtonDown() const
{
    return m_pImpl->m_bMouseButtonDown;
}

void Engine::Quit()
{
    m_pImpl->m_bQuit = true;
}

void Engine::Start(Updater& updater)
{
    m_pImpl->m_pUpdater = &updater;
    m_pImpl->m_sdlWindow.Show();
    m_pImpl->Start();
}

int Engine::GetTextureHeight(Texture texture) const
{
    return m_pImpl->m_pSdlSurfaceContainer[texture]->Height();
}

int Engine::GetTextureWidth(Texture texture) const
{
    return m_pImpl->m_pSdlSurfaceContainer[texture]->Width();
}

void Engine::Render(Engine::Texture texture, const glm::mat4& transform)
{
    glLoadMatrixf(reinterpret_cast<const float*>(&transform));

    SdlSurface& surface = *m_pImpl->m_pSdlSurfaceContainer[texture];

    surface.Bind();

    glBegin(GL_QUADS);
    glTexCoord2i(0, 1); glVertex2i(0, surface.Height());
    glTexCoord2i(1, 1); glVertex2i(surface.Width(), surface.Height());
    glTexCoord2i(1, 0); glVertex2i(surface.Width(), 0);
    glTexCoord2i(0, 0); glVertex2i(0, 0);
    glEnd();
}

void Engine::Render(Texture texture, float x, float y, float rotation)
{
    glm::mat4 transformation;
    transformation = glm::translate(transformation, glm::vec3(x, y, 0.0f));
    if (rotation)
    {
        transformation = glm::rotate(transformation,
                                        rotation,
                                        glm::vec3(0.0f, 0.0f, 1.0f));
    }
    Render(texture, transformation);
}

Glyph& FindGlyph(char c)
{
    auto found = std::lower_bound(std::begin(Font), std::end(Font), c);
    if (found == std::end(Font) || c < *found)
    {
        found = std::lower_bound(std::begin(Font),
                                    std::end(Font),
                                    static_cast<int>('_'));
    }
    return *found;
}

float Engine::CalculateStringWidth(const char* text) const
{
    int advance = 0;
    for (; *text; ++text)
    {
        Glyph& g = FindGlyph(*text);
        advance += g.advance;
    }
    return advance*TextScale;
}
    
void Engine::Write(const char* text, const glm::mat4& transform)
{
    glLoadMatrixf(reinterpret_cast<const float*>(&transform));
    int advance = 0;
    for (; *text;++text)
    {
        Glyph& g = FindGlyph(*text);

        float fontTexWidth  = static_cast<float>(m_pImpl->m_pFontSdlSurface->Width());
        float fontTexHeight = static_cast<float>(m_pImpl->m_pFontSdlSurface->Height());

        float uvLeft = static_cast<float>(g.x) / fontTexWidth;
        float uvRight = static_cast<float>(g.x + g.width) / fontTexWidth;
        float uvBottom = static_cast<float>(g.y) / fontTexHeight;
        float uvTop = static_cast<float>(g.y + g.height) / fontTexHeight;

        float worldLeft = static_cast<float>(g.xoffset + advance);
        float worldRight = static_cast<float>(g.xoffset + g.width + advance);
        float worldBottom = static_cast<float>(g.yoffset);
        float worldTop = static_cast<float>(g.yoffset + g.height);

        m_pImpl->m_pFontSdlSurface->Bind();

        glBegin(GL_QUADS);
        glTexCoord2f(uvLeft / 2.0f, uvTop / 2.0f); glVertex2f(worldLeft * TextScale, worldTop * TextScale);
        glTexCoord2f(uvRight / 2.0f, uvTop / 2.0f); glVertex2f(worldRight * TextScale, worldTop * TextScale);
        glTexCoord2f(uvRight / 2.0f, uvBottom / 2.0f); glVertex2f(worldRight * TextScale, worldBottom * TextScale);
        glTexCoord2f(uvLeft / 2.0f, uvBottom / 2.0f); glVertex2f(worldLeft * TextScale, worldBottom * TextScale);
        glEnd();
        advance += g.advance;
    }
}

void Engine::Write(const char* text, float x, float y, float rotation) {
    glm::mat4 transformation;
    transformation = glm::translate(transformation, glm::vec3(x, y, 0.0f));
    if (rotation)
    {
        transformation = glm::rotate(transformation,
                                        rotation,
                                        glm::vec3(0.0f, 0.0f, 1.0f));
        transformation = glm::translate(transformation,
                                        glm::vec3(-CalculateStringWidth(text)/2.0f,
                                                    -20.0f, 0.0f));
    }
    Write(text, transformation);
}

int Engine::GetWidth() const
{
    return WindowWidth;
}

int Engine::GetHeight() const
{
    return WindowHeight;
}

void Engine::EngineImplementation::Start()
{
    while (!m_bQuit)
    {
        SDL_GL_SwapWindow(m_sdlWindow);
        glClear(GL_COLOR_BUFFER_BIT);

        ParseEvents();

        float currentTicks = static_cast<float>(SDL_GetTicks());
        float lastFrameTicks = currentTicks - m_fElapsedTicks;
        m_fElapsedTicks = currentTicks;

        lastFrameTicks = std::min(lastFrameTicks, MaxFrameTicks);
        m_fLastFrameSeconds = lastFrameTicks * 0.001f;

        if (m_pUpdater)
        {
            m_pUpdater->Update();
        }
    }
}

void Engine::EngineImplementation::ParseEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            case SDL_KEYDOWN:
                m_bQuit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_bMouseButtonDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                m_bMouseButtonDown = false;
                break;
            case SDL_MOUSEMOTION:
                m_fMouseX = static_cast<float>(event.motion.x);
                m_fMouseY = static_cast<float>(event.motion.y);
                break;
            default:
                break;
        }
    }
}

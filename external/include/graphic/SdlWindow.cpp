#include "SdlWindow.h"

#include <stdexcept>
#include <string>
#include <sdl/SDL.h>

SdlWindow::SdlWindow(unsigned int width, unsigned int height) :
    m_pSDLWindow(SDL_CreateWindow("KingTest",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width, height,
                                SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL),
               SDL_DestroyWindow)
{
    if (m_pSDLWindow == false)
    {
        throw std::runtime_error(std::string("Error creating window: ") + SDL_GetError());
    }
}

void SdlWindow::Show()
{
    SDL_ShowWindow(m_pSDLWindow.get());
}

SdlWindow::operator SDL_Window*()
{
    return m_pSDLWindow.get();
}
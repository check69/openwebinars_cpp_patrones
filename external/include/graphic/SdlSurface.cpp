#include "SdlSurface.h"

#include <stdexcept>
#include <string>
#include <glew/glew.h>
#include <sdl/SDL.h>
#include <sdl/SDL_image.h>

SdlSurface::SdlSurface(const char* filename) :
    m_pSurface(IMG_Load(filename), SDL_FreeSurface),
    m_pTextureId(new unsigned int, &DeleteTexture)
{
    if (m_pSurface == nullptr)
    {
        throw std::runtime_error(std::string("Unable to load texture ") + filename);
    }

    glGenTextures(1, m_pTextureId.get());
    glBindTexture(GL_TEXTURE_2D, *m_pTextureId);
    int mode;

    switch (m_pSurface->format->BytesPerPixel)
    {
        case 4:
            mode = GL_RGBA;
            break;
        case 3:
            mode = GL_RGB;
            break;
        case 1:
            mode = GL_LUMINANCE_ALPHA;
            break;
        default:
            throw std::runtime_error("Image with unknown channel profile");
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, mode, m_pSurface->w, m_pSurface->h, 0, mode, GL_UNSIGNED_BYTE, m_pSurface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void SdlSurface::DeleteTexture(unsigned int* textureId)
{
    glDeleteTextures(1, textureId);
}

void SdlSurface::Bind()
{
    glBindTexture(GL_TEXTURE_2D, *m_pTextureId);
}

int SdlSurface::Width() const
{
    return m_pSurface->w;
}

int SdlSurface::Height() const
{
    return m_pSurface->h;
}

SdlSurface::operator SDL_Surface*()
{
    return m_pSurface.get();
}
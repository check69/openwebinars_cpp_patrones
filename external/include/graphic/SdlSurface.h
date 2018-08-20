#pragma once

#include <memory>

struct SDL_Surface;

class SdlSurface
{
    public:
        SdlSurface(const char* filename);
        operator SDL_Surface*();
        void Bind();
        int Width() const;
        int Height() const;

    private:
        static void DeleteTexture(unsigned int* textureId);
        std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> m_pSurface;
        std::unique_ptr<unsigned int,void(*)(unsigned int*)> m_pTextureId;
};
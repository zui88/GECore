#include <GECore/Renderer/Texture2D.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "GECore/Core/Logger.h"

namespace GECore {

  bool Texture2D::operator==(Texture const &other) const {
    return m_RendererID == static_cast<Texture2D const &>(other).m_RendererID;
  }

  void Texture2D::open() {
    
  }

  void Texture2D::close() {
    glDeleteTextures(1, &m_RendererID); 
  }

  Texture2D::~Texture2D() {
  
  }

    void Texture2D::bind() const {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        //        GL 4.5
        //        glBindTextureUnit(m_Slot, m_RendererID);
    }

  RefTexture Texture2D::Create(const std::string path, unsigned int slot) {
    auto texture = CreateRef<Texture2D>(path.c_str(), slot);
        texture->setSlot(slot);
        return texture;
    }

    void Texture2D::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

    Texture2D::Texture2D() {}
	
    Texture2D::Texture2D(char const *path, uint32_t slot) : m_Slot{slot} {
        stbi_set_flip_vertically_on_load(1);
        int width, heigth;
        m_LocalBuffer = stbi_load(path, &width, &heigth, &m_BPP, 0);

        m_Width = width;
        m_Height = heigth;

        GE_CORE_ASSERT(m_LocalBuffer, "Texture '{0}' can not be loaded", path);

        glGenTextures(1, &m_RendererID);

        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        //      set options to texture unit
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        switch (m_BPP) {
            case 3:
                m_InternalFormat = GL_RGB8;
                m_DataFormat = GL_RGB;
                break;
            case 4:
                m_InternalFormat = GL_RGBA8;
                m_DataFormat = GL_RGBA;
                break;
        }

        // GE_CORE_TRACE("m_BPP: {0}", m_BPP);
        GE_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Texture Formatat not supported");

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0,
                     m_DataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer);

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            GE_CORE_ERROR("Texture2D @ OpenGL Error: {}", err);
        }

        stbi_image_free(m_LocalBuffer);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::setSlot(unsigned int slot) {
        m_Slot = slot;
        //        glBindTextureUnit(m_Slot, m_RendererID);
    }

    RefTexture Texture2D::Create(uint32_t width, uint32_t height) {
        auto texture = CreateRef<Texture2D>(width, height);

        texture->setData(nullptr, 0);
        return texture;
    }

    Texture2D::Texture2D(uint32_t width, uint32_t height, uint32_t slot)
            : m_Width{width}, m_Height{height}, m_Slot{slot} {

        m_DataFormat = GL_RGBA;
        m_InternalFormat = GL_RGBA8;

        glGenTextures(1, &m_RendererID);
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0,
                     m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    void Texture2D::setData(void *data, uint32_t size) {
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        GE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Buffer has to be the size of the entire texture");

        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

} // namespace GECore

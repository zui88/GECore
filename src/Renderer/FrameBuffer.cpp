
#include "GECore/Core/Logger.h"
#include "GECore/Renderer/FrameBuffer.h"

#include "glad/glad.h"

namespace GECore {

  /**
   * todo: Description
   */
  FrameBuffer::FrameBuffer(uint32_t width, uint32_t heigth, Mode mode)
    : m_RendererID{ 0 }, m_Width{ width }, m_Heigth{ heigth }, m_TextureFormatMode{ mode } {
    invalidate();
  }


  void FrameBuffer::resize(uint32_t width, uint32_t heigth) {
    m_Width = width;
    m_Heigth = heigth;
    invalidate();
  }


  void FrameBuffer::invalidate() {
    if (m_RendererID) {
      glDeleteFramebuffers(1, &m_RendererID);
      glDeleteTextures(m_TextureID.size(), &m_TextureID[0]);
    }
    GLenum internalTextureFormat;
    switch(m_TextureFormatMode) {
    case Mode::LDR : internalTextureFormat = GL_RGB; break;
    case Mode::HDR : internalTextureFormat = GL_RGB16F; break;
    default : internalTextureFormat = GL_RGB;
    }
    glGenFramebuffers(1, &m_RendererID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    // color buffer
    glGenTextures(2, &m_TextureID[0]);
    glBindTexture(GL_TEXTURE_2D, m_TextureID[0]);
    glTexStorage2D(GL_TEXTURE_2D, 0, internalTextureFormat, m_Width, m_Heigth);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // depth & stencil buffer
    glBindTexture(GL_TEXTURE_2D, m_TextureID[1]);
    glTexStorage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Width, m_Heigth);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID[0], 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_TextureID[1], 0);
    // check for completeness
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      GE_CORE_ERROR("Framebuffer creation failure");
      glDeleteFramebuffers(1, &m_RendererID);
      glDeleteTextures(m_TextureID.size(), &m_TextureID[0]);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  FrameBuffer::~FrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &m_RendererID);
    glDeleteTextures(m_TextureID.size(), &m_TextureID[0]);
  }

  void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    glViewport(0, 0, m_Width, m_Heigth);
  }

  void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  void FrameBuffer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |  GL_STENCIL_BUFFER_BIT);
  }

}

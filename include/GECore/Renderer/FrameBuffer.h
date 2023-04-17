#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <array>

namespace GECore {
  class FrameBuffer {
  public:

    enum class Mode { LDR, HDR };

    FrameBuffer(uint32_t width, uint32_t heigth, Mode mode = Mode::LDR);

    ~FrameBuffer();

    void resize(uint32_t width, uint32_t heigth);
    
    uint32_t getRendererID() const { return m_RendererID; }

    void bind() const;
    
    static void unbind();

    /**
     * Clear all buffers: color, depth, stencil
     */
    static void clear();
  
  private:
    void invalidate();

    uint32_t m_RendererID;
    uint32_t m_Width, m_Heigth;
    Mode m_TextureFormatMode;
    // color and stencil-depth texture
    std::array<uint32_t, 2> m_TextureID;
  };
}

#endif	// FRAMEBUFFER_H

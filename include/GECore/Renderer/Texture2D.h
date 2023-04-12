#pragma once

#include <string>
#include <memory>

#include "GECore/Core/Core.h"
#include "glad/glad.h"

namespace GECore {

    class Texture {
    public:
        virtual void bind() const = 0;

        virtual void unbind() const = 0;

        virtual void setData(void* data, uint32_t size) = 0;

        virtual uint32_t getWidth() const = 0;

        virtual uint32_t getHeight() const = 0;

        virtual bool operator==(Texture const &other) const = 0;
      
    };


    class Texture2D;
    typedef Ref<Texture2D> RefTexture;

    class Texture2D : public Texture {
    public:
        Texture2D();
	
	explicit Texture2D(char const *path, uint32_t slot = 0);

        Texture2D(uint32_t width, uint32_t height, uint32_t slot = 0);

        ~Texture2D();

        void bind() const override;

        void unbind() const override { Texture2D::Unbind(); }

        static void Unbind();

        void setData(void *data, uint32_t size) override;

        void setSlot(unsigned int slot);

        static RefTexture Create(uint32_t width, uint32_t height);

      static RefTexture Create(std::string const path, unsigned int slot = 0);

        [[nodiscard]] uint32_t getHeight() const override { return m_Height; }

        [[nodiscard]] uint32_t getWidth() const override { return  m_Width; }

        virtual bool operator==(Texture const &other) const override;

    private:

      void open();

      void close();

    public:
        uint32_t m_Width, m_Height;
        int m_BPP;
    private:
        uint32_t m_RendererID;
        unsigned char *m_LocalBuffer;
        unsigned int m_Slot;
        char const *m_Path;
        GLenum m_InternalFormat{ 0 }, m_DataFormat{ 0 };
    };

}

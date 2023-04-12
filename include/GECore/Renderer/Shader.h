#pragma once

#include "GECore/Core/Core.h"

#include "glm/mat4x4.hpp"
#include <glad/glad.h>
#include <zui/zui.h>

namespace GECore {

enum class SHADERTYPE : unsigned char { VERTEX, FRAGMENT };

struct uniform_location_loader : zui::loader<uniform_location_loader, int32_t> {
  [[nodiscard]] zui::handle<int32_t> static load(char const *name,
                                                 uint32_t renderer_id) {
    int32_t loc = glGetUniformLocation(renderer_id, name);
    return zui::make_handle<int32_t>(loc);
  }
};

class Shader;

typedef Ref<Shader> RefShader;

static std::hash<char const *> s_StrToInt;

class Shader {
  typedef zui::cache<int32_t> UniformLocationCache;

public:
  Shader(const char *name);

  ~Shader();

  void bind() const;

  static void unbind();

  void setInt(const char *name, int value) const;

  void setIntArray(const char *name, int32_t const *value, uint32_t count) const;

  // return true if name was found else false
  void setFloat3(char const *name, const glm::vec3 &value) const;

  void setFloat(char const *name, float value) const;

  void setFloat4(char const *name, const glm::vec4 &value) const;

  void setMat4(char const *name, const glm::mat4 &matrix) const;

  // get the program name
  uint32_t getID() const noexcept { return m_RendererID; }

  static RefShader Create(char const *filepath);

  static RefShader Create(char const *name, char const *vertSrc,
                          char const *fragSrc);

  template <int size>
  void setIntArry(const char *name, int const (&values)[size]) const {
    zui::handle<int32_t> uLoc = m_ULC.load<uniform_location_loader>(
        s_StrToInt(name), name, m_RendererID);
    if (GLNameLocCheck(*uLoc, name))
      glUniform1iv(*uLoc, size, &values[0]);
  }

  char const *getName() const noexcept { return m_Name; };

protected:
  Ref<std::string> load(uint32_t id, char const *filepath);

  GLuint compile(Ref<std::string> const &shaderSRC, SHADERTYPE ST);

  GLuint link(GLuint compiledVertexShader, GLuint compiledFragmentShader);

  void setID(uint32_t shaderID) noexcept { m_RendererID = shaderID; }

private:
  static bool GLNameLocCheck(int loc, const char *name);

private:
  mutable UniformLocationCache m_ULC;
  char const *m_Name;
  uint32_t m_RendererID{ 0 };
};


class ShaderLibrary {
  typedef zui::cache<std::string> ShaderFileCache;

public:
  // shader class needs a 'getName' function
  void add(RefShader const &shader);

  void add(char const *name, RefShader const &shader);

  // 'assets/shader.glsl.vert' strips out 'vert' as name
  void load(char const *filepath);

  // add a costom name
  void load(char const *name, char const *filepath);

  RefShader get(char const *name) const;

  bool exists(char const *name) const;

private:
  ShaderFileCache m_SFC;
};

} // namespace GECore

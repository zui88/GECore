#include "GECore/Renderer/Shader.h"
#include "GECore/Core/Core.h"
#include <GECore/Core/Logger.h>

#include <functional>

namespace GECore {

Shader::~Shader() { glDeleteShader(m_RendererID); }

  Shader::Shader(const char* name) : m_Name{name} {}  

RefShader Shader::Create(char const *name, char const *vertpath, char const *fragpath) {
  RefShader shader = CreateRef<Shader>(name);

  auto vertexSource = shader->load(s_StrToInt(vertpath), vertpath);
  GE_CORE_ASSERT(vertexSource, "{}: vertex shader source not found", name);
  auto compiledVertexSahder = shader->compile(vertexSource, SHADERTYPE::VERTEX);

  auto fragmentSource = shader->load(s_StrToInt(fragpath), fragpath);
  GE_CORE_ASSERT(fragmentSource, "{}: fragment shader source not found", name);
  auto compiledFragmentShader = shader->compile(fragmentSource, SHADERTYPE::FRAGMENT);

  auto shaderProgram = shader->link(compiledVertexSahder, compiledFragmentShader);

  shader->setID(shaderProgram);

  return shader;
}

  GLuint Shader::compile(Ref<std::string> const& shaderSRC, SHADERTYPE ST) {

    GE_CORE_ASSERT(!shaderSRC.is_empty(), "{0}: shader source is empty", m_Name);

  GLenum shaderType;
  switch (ST) {
  case SHADERTYPE::VERTEX:
    shaderType = GL_VERTEX_SHADER;
    break;
  case SHADERTYPE::FRAGMENT:
    shaderType = GL_FRAGMENT_SHADER;
    break;
  default:
    GE_CORE_ASSERT(false, "{0}: non supported shader type", m_Name);
    break;
  }

  GLuint shader = glCreateShader(shaderType);
  auto shaderc_str = static_cast<GLchar const*>(shaderSRC.get()->c_str());
  glShaderSource(shader, 1, &shaderc_str, nullptr);
  glCompileShader(shader);

  GLint isCompiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE) {
    GLint maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

    glDeleteShader(shader);

    GE_CORE_ASSERT(false, "{0}: shader compile error\n\n{1}", m_Name, &infoLog[0]);
  }
  return shader;
}

GLuint Shader::link(GLuint vertexShader, GLuint fragmentShader) {

  // Vertex and fragment shaders are successfully compiled.
  // Now time to link them together into a program.
  // Get a program object.
  GLuint program = glCreateProgram();

  // Attach our shaders to our program
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link our program
  glLinkProgram(program);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

    glDeleteProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GE_CORE_ASSERT("{0}: Linking error\n\n{1}", m_Name, &infoLog[0]);
    return 0;
  }
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);
  return program;
}

void Shader::bind() const { glUseProgram(m_RendererID); }

void Shader::unbind() { glUseProgram(0); }

bool Shader::GLNameLocCheck(int loc, const char *name) {
  switch (loc) {
  case -1:
    GE_CORE_ERROR("Name {0} in Shader not found", name);
    return false;
  case GL_INVALID_VALUE:
    GE_CORE_ERROR("Shader id not generated by opengl");
    return false;
  case GL_INVALID_OPERATION:
    GE_CORE_ERROR("Shader id is not a program object");
    return false;
  default:
    return true;
  }
}

  void Shader::setIntArray(const char *name, int32_t const *value, uint32_t count) const {
    zui::handle<int32_t> uLoc = m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
    if (GLNameLocCheck(*uLoc, name)) {
      glUniform1iv(*uLoc, count, value);
    }
  }

void Shader::setInt(const char *name, int value) const {
  zui::handle<int32_t> uLoc = m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
  if (GLNameLocCheck(*uLoc, name))
    glUniform1i(*uLoc, value);
}

void Shader::setFloat3(char const *name,
                       glm::vec3 const &value) const {
  zui::handle<int32_t> uLoc =
      m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
  if (GLNameLocCheck(*uLoc, name))
    glUniform3f(*uLoc, value.x, value.y, value.z);
}

Ref<std::string> Shader::load(uint32_t id, char const *filepath) {
  GE_CORE_ASSERT(filepath, "{0}: empty shader file path", m_Name);

  // auto path = zui::string::seperate(filepath, '/');
  // auto shaderName = path.back();
  // auto fileParts = zui::string::seperate(shaderName, '.');
  // path.pop_back();

  // for (auto const& p : path)
  //   GE_CORE_TRACE("{}: Shader-File-Path: {}", m_Name, p);

  // for (auto const& s : fileParts)
  //   GE_CORE_TRACE("{}: Shader-File-Parts: {}", m_Name, s);

  zui::file_loader fl;  
  // return fl.load(shaderName.c_str());
  return fl.load(filepath);
}

void Shader::setMat4(const char *name, const glm::mat4 &matrix) const {
  zui::handle<int32_t> uLoc = m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
  if (GLNameLocCheck(*uLoc, name))
    glUniformMatrix4fv(*uLoc, 1, GL_FALSE, &matrix[0][0]);
}

    void Shader::setFloat4(const char *name, const glm::vec4 &value) const {
        zui::handle<int32_t> uLoc =
                m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
        if (GLNameLocCheck(*uLoc, name))
            glUniform4f(*uLoc, value.x, value.y, value.z, value.w);
    }

    RefShader Shader::Create(const char *filepath) {
        GE_CORE_ERROR("Shader @ Create filepath not implemented!");
        return GECore::RefShader();
    }

    void Shader::setFloat(const char *name, float value) const {
        zui::handle<int32_t> uLoc =
                m_ULC.load<uniform_location_loader>(s_StrToInt(name), name, m_RendererID);
        if (GLNameLocCheck(*uLoc, name))
            glUniform1f(*uLoc, value);
    }

} // namespace GECore
#ifndef Vertex_H
#define Vertex_H

#include "glm/glm.hpp"

struct Vertex {
  glm::vec3 position;
  glm::vec2 texcoord;
  glm::vec4 color;
  float texindex;
  float tilingfactor = 1.0f;
};

#endif /* Vertex_H */

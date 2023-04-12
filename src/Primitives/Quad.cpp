#include "GECore/Primitives/Quad.h"

namespace GECore {

  void Quad::setTexIndex(float idx) {
    m_Vertices[0].texindex = idx;
    m_Vertices[1].texindex = idx;
    m_Vertices[2].texindex = idx;
    m_Vertices[3].texindex = idx;
  }

  void Quad::size(glm::vec2 const &s) {
    m_Vertices[1].position.x = m_Vertices[0].position.x + s.x;
    m_Vertices[2].position.x = m_Vertices[3].position.x + s.x;

    m_Vertices[2].position.y = m_Vertices[1].position.y + s.y;
    m_Vertices[3].position.y = m_Vertices[0].position.y + s.y;
  }


  void Quad::setTexCoords(glm::vec2 const *coords) {
    m_Vertices[0].texcoord = coords[0];
    m_Vertices[1].texcoord = coords[1];
    m_Vertices[2].texcoord = coords[2];
    m_Vertices[3].texcoord = coords[3];
  }


  void Quad::setTilingFactor(float tf) {
    m_Vertices[0].tilingfactor = tf;
    m_Vertices[1].tilingfactor = tf;
    m_Vertices[2].tilingfactor = tf;
    m_Vertices[3].tilingfactor = tf;
  }




} /* GECore */

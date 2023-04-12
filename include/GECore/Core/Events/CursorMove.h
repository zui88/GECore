#pragma once

#include "LayerEvent.h"

namespace GECore {

  struct cursor_move_e : layer_event {
    double xpos, ypos;
  };

}

#define CURSOR_EVT(X,Y) cursor_move_e{false,X,Y}

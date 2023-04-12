#pragma once

#include "LayerEvent.h"

namespace GECore {

  struct mouse_press_e : layer_event {
    int button;
  };

}

#define MOUSE_EVT(BT) mouse_press_e{false,BT}

#pragma once

#include "LayerEvent.h"

namespace GECore {

  struct keyboard_press_e : layer_event {
    int key, scancode;
  };

}

#define KEYBOARD_EVT(KY,SCN) keyboard_press_e{false,KY,SCN}

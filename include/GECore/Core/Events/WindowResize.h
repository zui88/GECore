#pragma once

namespace GECore {

  struct window_resize_e {
    int width, height;
  };

}

#define WIN_RESIZE_EVT(W,H) win_resize_e{W,H}

//
// Created by zui on 2/13/23.
//

#ifndef OGLGE_MOUSESCROLL_H
#define OGLGE_MOUSESCROLL_H

#include "LayerEvent.h"

namespace GECore {

    struct mouse_scroll_e : layer_event {
        double xoffset;
        double yoffset;
    };

}

#endif //OGLGE_MOUSESCROLL_H

#include "ground.h"
#include <gccore.h>
#include <grrlib.h>

// yeah the ground is hardcoded to be like this sue me
// its not going to change, like, ever. so its fine

void draw_ground() {
    GRRLIB_Rectangle(0, gy, 640, gheight, gcolor, true);
}
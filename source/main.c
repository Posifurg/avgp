// youre gonna see a lot of stupid comments lmao sorry im just excited this is my first actual homebrew app

#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <stdlib.h>
#include <math.h>

// cube_png.h cube_png.h cube_png.h cube_png.h cube_png.h cube_png.h cube_png.h cube_png.h cube_png.h
#include "cube_png.h"
#include "player.h"
#include "ground.h"

// immediately going to say this, but this is likely very spaghetti coded, so uhhhhh sorry

int main() {
    GRRLIB_Init();
    WPAD_Init();

    GRRLIB_texImg *cuberton = GRRLIB_LoadTexture(cube_png);

    startcube(cuberton);

    while (1) {
        WPAD_ScanPads();

        // i dont want to force shut down my wii every damn time
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) {
            break;
        }

        GRRLIB_FillScreen(0x000020FF);


        updcube();
        draw_ground();
        drawcube();

        // ok we're done doing things now RENDER IT
        GRRLIB_Render();
    }

    GRRLIB_FreeTexture(cuberton);
    GRRLIB_Exit();

    return 0;
}

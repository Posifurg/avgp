#include <grrlib.h>
#include <wiiuse/wpad.h>
#include "player.h"
#include "ground.h"

float playerX = 0;
float playerY = 0;

float plrXspd = 0.0f;
float plrYspd = 0;

float plrSizeX = 18.0f; // smaller because of weird wii outputting shit
float plrSizeY = 24.0f;

bool on_ground = false;
bool djump = false;
static GRRLIB_texImg *player_tex = NULL;
static u32 prevButtons = 0;

void startcube(GRRLIB_texImg *tex) {
    playerX = 320.0f;
    playerY = 240.0f;
    plrYspd = 0;
    player_tex = tex;
}

void player_eternalsuffering() {
    playerX = 320.0f - (plrSizeX / 2);
    playerY = 240.0f;
    plrYspd = 10.0;
    djump = true;
}

void updcube() {
    on_ground = ((playerY + plrSizeY) >= gy);
    u32 buttons = WPAD_ButtonsHeld(0);
    u32 buttonPress = buttons & ~prevButtons;

    if ((buttons & WPAD_BUTTON_RIGHT)) { // go right (horizontal wiimote)
        plrXspd = plrXspd + 0.4f;
        if (plrXspd > 6) {
            plrXspd = 6;
        }
    } else if ((buttons & WPAD_BUTTON_LEFT)) { // ditto, but left
        plrXspd = plrXspd - 0.4f;
        if (plrXspd < -6) {
            plrXspd = -6;
        }
    } else {
        plrXspd = 0.0f;
    }

    playerX += plrXspd;

    if (on_ground) {
        playerY = gy - plrSizeY;
        plrYspd = 0.6f;
    }

    if (buttonPress & WPAD_BUTTON_UP) {
        if (on_ground || djump) { // Simplified: can jump if grounded OR have djump available
            plrYspd = 10.0f;
            djump = on_ground; // Only enable djump if jumping from ground
        }
    }

    plrYspd -= 0.6f;
    playerY -= plrYspd;

    if (playerX < 0 || playerX + plrSizeX > 640) {
        player_eternalsuffering();
    }

    prevButtons = buttons;
}

void drawcube() {
    GRRLIB_DrawImg(playerX, playerY, player_tex, 0, plrSizeX / player_tex->w, plrSizeY / player_tex->h, 0xFFFFFFFF);
}
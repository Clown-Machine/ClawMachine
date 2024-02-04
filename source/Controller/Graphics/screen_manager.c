#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include "images/images.h"
#include <stdio.h>
#define DEBUG 1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

Graphics_Context g_sContext;

//List of available images
typedef enum Images
{
    LOGO, BLUETOOTH, THUMBSUP
} img_t;

/*List of available alignments*/
typedef enum TextMode
{
    LEFT, CENTERED
} textmode_t;

//Limits value on the Horizontal axis from 0 to SCREEN_WIDTH
uint8_t clampX(uint8_t x)
{
    if (x > SCREEN_WIDTH)
    {
        return SCREEN_WIDTH;
    }
    return x;
}
//Limits value on the Vertical axis from 0 to SCREEN_HEIGHT
uint8_t clampY(uint8_t y)
{
    if (y > SCREEN_HEIGHT)
    {
        return SCREEN_HEIGHT;
    }
    return y;
}

/*
 * Initializes the components used to manage the graphical aspect
 */
void _graphicsInit()
{
# ifndef SCREEN_MANAGER_INITIALIZED
# define SCREEN_MANAGER_INITIALIZED
# if DEBUG
    assert(clampX(10) == 10);
    assert(clampX(255) == SCREEN_WIDTH);
    assert(clampX(SCREEN_WIDTH) == SCREEN_WIDTH);
    assert(clampY(10) == 10);
    assert(clampY(255) == SCREEN_HEIGHT);
    assert(clampY(SCREEN_HEIGHT) == SCREEN_HEIGHT);
#endif

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);

    /* Initializes screen parameters*/
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);

    /* Clears screen*/
    Graphics_clearDisplay(&g_sContext);
#endif
}
/*
 * Clears everything from the screen
 */
void cleanScreen()
{
#ifndef SCREEN_MANAGER_INITIALIZED
    _graphicsInit();
#endif
    Graphics_clearDisplay(&g_sContext);
}

void blackenArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h){

#ifndef SCREEN_MANAGER_INITIALIZED
    _graphicsInit();
#endif
    x = clampX(x);
    y = clampY(y);
    uint8_t clamppedWidth = clampX(x+w);
    uint8_t clamppedHeight = clampY(y+h);

    tRectangle area = { x, y, clamppedWidth, clamppedHeight};

    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext, &area);
    Graphics_fillRectangle(&g_sContext, &area);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
}
/*
 * Writes a centered text at some (x,y) coordinates
 *
 * ! Parameters
 * text : Text to be printed
 * x: Horizontal position
 * y: Vertical position
 * mode: Alignment of the text
 */
void writeToScreen(char *text, uint8_t x, uint8_t y, textmode_t mode)
{
#ifndef SCREEN_MANAGER_INITIALIZED
    _graphicsInit();
#endif
    x = clampX(x);
    y = clampY(y);
    if (mode == CENTERED)
    {
        Graphics_drawStringCentered(&g_sContext, (int8_t*) text,
        AUTO_STRING_LENGTH,
                                    x, y, OPAQUE_TEXT);
    }
    else if (mode == LEFT)
    {
        Graphics_drawString(&g_sContext, (int8_t*) text,
        AUTO_STRING_LENGTH,
                            x, y, OPAQUE_TEXT);
    }
}

/*
 * Draws an image at some (x,y) coordinates
 *
 * ! Parameters
 * img : Image to be drawn
 * x: Horizontal position
 * y: Vertical position
 */
void drawImage(img_t img, uint8_t x, uint8_t y)
{
#ifndef SCREEN_MANAGER_INITIALIZED
_graphicsInit();
#endif
    x = clampX(x);
    y = clampY(y);
    tImage bitmap;
    switch (img)
    {
    case LOGO:
        bitmap = claw8BPP_UNCOMP;
        break;
    case BLUETOOTH:
        bitmap = bluetooth4BPP_UNCOMP;
        break;
    case THUMBSUP:
        bitmap = thumbsup4BPP_UNCOMP;
        break;
    default:
        bitmap = claw8BPP_UNCOMP;
    }
    Graphics_drawImage(&g_sContext, &bitmap, x, y);
}

/*
 * Draws a line
 *
 * ! Parameters
 * x1 : Horizontal starting position
 * y1: Vertical starting position
 * x2 : Horizontal ending position
 * y2: Vertical ending position
 */
void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
#ifndef SCREEN_MANAGER_INITIALIZED
_graphicsInit();
#endif
    x1 = clampX(x1);
    x2 = clampX(x2);
    y1 = clampY(y1);
    y2 = clampY(y2);
    Graphics_drawLine(&g_sContext, x1, y1, x2, y2);
}

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

//List of available colors
typedef enum Colors
{
    Aqua = GRAPHICS_COLOR_AQUA,
    Blue = GRAPHICS_COLOR_BLUE,
    Cyan = GRAPHICS_COLOR_CYAN,
    DarkGray = GRAPHICS_COLOR_DARK_GRAY,
    DarkGreen = GRAPHICS_COLOR_DARK_GREEN,
    DarkMagenta = GRAPHICS_COLOR_DARK_MAGENTA,
    DarkRed = GRAPHICS_COLOR_DARK_RED,
    Turquoise = GRAPHICS_COLOR_DARK_TURQUOISE,
    Gold = GRAPHICS_COLOR_GOLD,
    Gray = GRAPHICS_COLOR_GRAY,
    Green = GRAPHICS_COLOR_GREEN,
    Indigo = GRAPHICS_COLOR_INDIGO,
    Lime = GRAPHICS_COLOR_LIME,
    Pink = GRAPHICS_COLOR_PINK,
    Purple = GRAPHICS_COLOR_PURPLE,
    Red = GRAPHICS_COLOR_RED,
    Sienna = GRAPHICS_COLOR_SIENNA,
    Snow = GRAPHICS_COLOR_SNOW,
    Tomato = GRAPHICS_COLOR_TOMATO,
    White = GRAPHICS_COLOR_WHITE,
    Yellow = GRAPHICS_COLOR_YELLOW,
    Black = GRAPHICS_COLOR_BLACK
} colors_t;


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
    Graphics_setForegroundColor(&g_sContext, White);
    Graphics_setBackgroundColor(&g_sContext, Black);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);

    /* Clears screen*/
    Graphics_clearDisplay(&g_sContext);
#endif
}

/*
 * Sets color of everything that is going to be written or drawn to the screen
 * ! Parameters:
 * color: Color to be set as foreground
 */
void setForegroundColor(colors_t color)
{
#ifndef SCREEN_MANAGER_INITIALIZED
    _graphicsInit();
#endif
    Graphics_setForegroundColor(&g_sContext, color);
}

/*
 * Sets color of background
 * * ! Parameters:
 * color: Color to be set as background
 */
void setBackgroundColor(colors_t color)
{
#ifndef SCREEN_MANAGER_INITIALIZED
    _graphicsInit();
#endif
    Graphics_setBackgroundColor(&g_sContext, color);
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

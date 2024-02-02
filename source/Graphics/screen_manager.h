#ifndef SCREEN_MNG
#define SCREEN_MNG

#include <ti/grlib/grlib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

typedef enum Images
{
    LOGO, BLUETOOTH, THUMBSUP
} img_t;

typedef enum TextMode
{
    LEFT, CENTERED
} textmode_t;

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

void _graphicsInit(void);
void setForegroundColor(colors_t color);
void setBackgroundColor(colors_t color);
void cleanScreen(void);

void writeToScreen(char *string, uint8_t x, uint8_t y, textmode_t mode);
void drawImage(img_t img, int x, int y);
void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif

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
void _graphicsInit(void);
void cleanScreen(void);

void blackenArea(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void writeToScreen(char *string, uint8_t x, uint8_t y, textmode_t mode);
void drawImage(img_t img, int x, int y);
void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif

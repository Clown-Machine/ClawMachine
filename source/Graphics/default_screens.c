#include "screen_manager.h"
#include "Controller/include/ControllerFSM.h"
#include <stdio.h>
extern Mode_t current_mode;
// SELECTION of the option in the menu screen
uint8_t SELECTION = 0;
void _screenInit()
{
#ifndef DEFAULT_SCREENS_INITIALIZED
#define DEFAULT_SCREENS_INITIALIZED
    _graphicsInit();
#if DEBUG
    assert(screenMoveUp() == 1);
    assert(screenMoveUp() == 2);
    assert(screenMoveUp() == 3);
    assert(screenMoveUp() == 3);
    assert(screenMoveDown() == 2);
    assert(screenMoveDown() == 1);
    assert(screenMoveDown() == 0);
    assert(screenMoveDown() == 0);

#endif
#endif
}

// Screen to show while waiting for bluetooth pairing
void screenBluetoothPairing()
{
#ifndef DEFAULT_SCREENS_INITIALIZED
    _screenInit();
#endif
    setForegroundColor(White);
    setBackgroundColor(Black);

    drawImage(BLUETOOTH, SCREEN_WIDTH / 2 - 32, 0);
    writeToScreen("Check that the", SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2,
                  CENTERED);
    writeToScreen("Bluetooth modules", SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2 + 10,
                  CENTERED);
    writeToScreen("are paired", SCREEN_WIDTH / 2,
    SCREEN_HEIGHT / 2 + 20,
                  CENTERED);

    writeToScreen("Press B1 to continue", SCREEN_WIDTH / 2,
    SCREEN_HEIGHT - 20,
                  CENTERED);

}
// Selects the option higher than the current one
void screenMoveUp()
{
    if (SELECTION > 0)
    {
        SELECTION -= 1;
    }
}
// Selects the option lower than the current one
void screenMoveDown()
{
    if (SELECTION < 3)
    {
        SELECTION += 1;
    }
}

// Screen to show while selecting the target position for the claw to reach in Automatic mode
void screenMenuPosition()
{
#ifndef DEFAULT_SCREENS_INITIALIZED
    _screenInit();
#endif
    cleanScreen();
    setForegroundColor(White);
    setBackgroundColor(Black);
    writeToScreen("Select a position", SCREEN_WIDTH / 2, 10, CENTERED);
    drawLine(0, 25, SCREEN_WIDTH, 25);
    uint8_t offset = 20;
    uint8_t base = 30;
    writeToScreen("O", 30, base + offset * SELECTION, CENTERED);
    writeToScreen("Position: A", SCREEN_WIDTH / 2 + 10, base + offset,
                  CENTERED);

    writeToScreen("Position: B", SCREEN_WIDTH / 2 + 10, base + 2 * offset,
                  CENTERED);

    writeToScreen("Position: C", SCREEN_WIDTH / 2 + 10, base + 3 * offset,
                  CENTERED);

    writeToScreen("Position: D", SCREEN_WIDTH / 2 + 10, base + 4 * offset,
                  CENTERED);
}

// Screen to show while user is in Manual Mode
void screenIntroduction()
{
#ifndef DEFAULT_SCREENS_INITIALIZED
    _screenInit();
#endif
    cleanScreen();
    writeToScreen("Press B1", 5, 10, LEFT);
    writeToScreen("to switch mode", 5, 20, LEFT);
    writeToScreen("Press B2 ", 5, 35, LEFT);
    writeToScreen("to save position", 5, 45, LEFT);
    writeToScreen("Press B3 ", 5, 60, LEFT);
    writeToScreen("to control the claw", 5, 70, LEFT);

    writeToScreen("Current mode:", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 35,
                  CENTERED);
    if (current_mode == MANUAL_MODE)
    {
        writeToScreen("MANUAL", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 25, CENTERED);
    }
    else
    {
        writeToScreen("AUTOMATIC", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 25, CENTERED);
    }

    writeToScreen("Move joystick to use", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10,
                  CENTERED);
}
// Screen to show while position is being saved
void screenSavingPosition()
{
#ifndef DEFAULT_SCREENS_INITIALIZED
    _screenInit();
#endif
    cleanScreen();
    writeToScreen("Saved new position", SCREEN_WIDTH / 2, 40, CENTERED);
    drawImage(THUMBSUP, SCREEN_WIDTH / 2 - 24, SCREEN_HEIGHT - 60);
}

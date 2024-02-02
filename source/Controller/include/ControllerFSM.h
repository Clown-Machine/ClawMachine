#ifndef CONTROLLER_FSM_H
#define CONTROLLER_FSM_H

#include <Controller/include/ControllerSetup.h>
#include <Controller/include/InterruptHandler.h>
#include <Graphics/default_screens.h>

#define SLOW 7
#define FAST 15

typedef enum{
    INIT_MODE,
    MANUAL_MODE,
    AUTOMATIC_MODE,
    SELECT_MODE,
    NUM_MODE
}Mode_t;

typedef enum{
    HORIZONTAL_MODE,
    VERTICAL_MODE,
    SCREEN_MODE,
    NUM_MOVEMENT
}Movement_t;

typedef enum {
    SW_NONE,
    SW1_PRESSED,
    SW2_PRESSED,
    SW3_PRESSED,
} Event_t;

void fn_INIT_MODE();
void fn_MANUAL_MODE();
void fn_AUTOMATIC_MODE();
void fn_SELECT_MODE();

void fn_SCREEN_MODE();
void fn_HORIZONTAL_MODE();
void fn_VERTICAL_MODE();

typedef struct{
    Mode_t mode;
    void (*mode_function)(void);
} ModeMachine_t;

typedef struct{
    Movement_t movement;
    void (*movement_function)(void);
} MovementMachine_t;

void Controller();
void VerticalMovement_setMessage(uint16_t gripper, uint16_t z);
void HorizontalMovement_setMessage(uint16_t x, uint16_t y);

#endif

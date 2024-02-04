#include "include/ControllerFSM.h"
#define DEBUG_CONTROLLER 0
/// @brief Finite state machine for the controller
/// @details The controller has:
///             4 modes: INIT_MODE, MANUAL_MODE, AUTOMATIC_MODE, SELECT_MODE
///             3 movements: HORIZONTAL_MODE, VERTICAL_MODE, SCREEN_MODE
///             3 events: SW_NONE, SW1_PRESSED, SW2_PRESSED, SW3_PRESSED

Mode_t current_mode = INIT_MODE;
Movement_t current_movement = SCREEN_MODE;
Event_t event = SW_NONE;

uint8_t saved_position = 0;
uint16_t i = 0;

extern uint16_t resultsBuffer[2];

ModeMachine_t fsm[] = { { INIT_MODE, fn_INIT_MODE }, 
                        { MANUAL_MODE, fn_MANUAL_MODE },
                        { AUTOMATIC_MODE, fn_AUTOMATIC_MODE },
                        { SELECT_MODE, fn_SELECT_MODE } };

MovementMachine_t mfsm[] = { //movement finite state machine
        { HORIZONTAL_MODE, fn_HORIZONTAL_MODE }, 
        { VERTICAL_MODE, fn_VERTICAL_MODE },
        { SCREEN_MODE, fn_SCREEN_MODE } };

void fn_INIT_MODE()
{
    if (event == SW1_PRESSED)
    {
        event = SW_NONE;
        current_mode = MANUAL_MODE;
        #if DEBUG_CONTROLLER
            printf("MANUAL_MODE\n");
        #endif
        // horizontal movement is enabled by default
        current_movement = HORIZONTAL_MODE;
    }
}

void fn_MANUAL_MODE()
{
    if (event == SW1_PRESSED)
    {
        event = SW_NONE;
        // change mode to automatic
        current_mode = AUTOMATIC_MODE;
        #if DEBUG_CONTROLLER
            printf("AUTOMATIC_MODE\n");
        #endif
        current_movement = SCREEN_MODE;
        stopCartMovements();
        stopGripperMovements();
        screenMenuPosition();
    }
    else if (event == SW2_PRESSED)
    {
        event = SW_NONE;
        // change mode to select
        current_mode = SELECT_MODE;
        #if DEBUG_CONTROLLER
            printf("SELECT_MODE\n");
        #endif
        current_movement = SCREEN_MODE;
        stopCartMovements();
        stopGripperMovements();
        screenMenuPosition();
    }

}

void fn_AUTOMATIC_MODE()
{
    if (event == SW1_PRESSED)
    {
        event = SW_NONE;
        // change mode to manual
        current_mode = MANUAL_MODE;
        #if DEBUG_CONTROLLER
            printf("MANUAL_MODE\n");
        #endif
        current_movement = HORIZONTAL_MODE;
        screenIntroduction();
    }
    if(event == SW2_PRESSED){
        event = SW_NONE;
        goToTarget(saved_position);
    }
}

void fn_SELECT_MODE()
{
    if (event == SW1_PRESSED)
    {
        event = SW_NONE;
        // change mode to manual
        current_mode = MANUAL_MODE;
        #if DEBUG_CONTROLLER
            printf("MANUAL_MODE\n");
        #endif
        current_movement = HORIZONTAL_MODE;
        screenIntroduction();
    }
    else if (event == SW2_PRESSED)
    {
        // select saved position and send message
        event = SW_NONE;
        saveTarget(saved_position);
        screenSavingPosition();
        for(i = 3000; i > 0; i--);
        screenMenuPosition();
    }
}


uint8_t has_moved = 0;
void fn_SCREEN_MODE()
{

    // based on x and y values set direction and velocity of vertical movement and gripper

    // moving in the screen based on resutsBuffer[1]
    uint16_t y_value = resultsBuffer[1];
    if (y_value > 10000)
    {
        // move up in the screen if movement is allowed
        if (has_moved == 0)
        {
            #if DEBUG_CONTROLLER
                printf("Move up\n");
            #endif
            screenMoveUp();
            screenMenuPosition();
            if(saved_position > 0){
                saved_position--;
            }
        }
        has_moved = 1;
    }
    else if (y_value < 5000)
    {
        // move down in the screen if movement is allowed
        if (has_moved == 0)
        {
            #if DEBUG_CONTROLLER
                printf("Move down\n");
            #endif
            screenMoveDown();
            screenMenuPosition();
            if(saved_position < 3){
                saved_position++;
            }
        }
        has_moved = 1;
    }
    else
    {
        #if DEBUG_CONTROLLER
            printf("Reset\n");
        #endif
        has_moved = 0;
    }
}


void fn_HORIZONTAL_MODE()
{
    if (event == SW3_PRESSED)
    {
        event = SW_NONE;
        // stop all horizontal movements
        stopCartMovements();
        // vertical movement is enabled
        current_movement = VERTICAL_MODE;
        #if DEBUG_CONTROLLER
            printf("VERTICAL_MODE\n");
        #endif
    }
    else
    {
        int16_t x_value = resultsBuffer[0];
        uint16_t y_value = resultsBuffer[1];
        #if DEBUG_CONTROLLER
            printf("x_axis = %d\n", x_value);
            printf("y_axis = %d\n", y_value);
        #endif
        // based on x and y values set direction and velocity
        HorizontalMovement_setMessage(x_value, y_value);
    }
}
void fn_VERTICAL_MODE()
{
    if (event == SW3_PRESSED)
    {
        event = SW_NONE;
        // stop all vertical movements
        stopGripperMovements();
        // horizontal movement is enabled
        current_movement = HORIZONTAL_MODE;
        #if DEBUG_CONTROLLER
            printf("HORIZONTAL_MODE\n");
        #endif
    }
    else
    {
        uint16_t x_value = resultsBuffer[0];
        uint16_t y_value = resultsBuffer[1];
        #if DEBUG_CONTROLLER
            printf("x_axis = %d\n", x_value);
            printf("y_axis = %d\n", y_value);
        #endif
        VerticalMovement_setMessage(x_value, y_value);
    }
}

void Controller()
{
    if (current_mode < NUM_MODE && current_movement < NUM_MOVEMENT)
    {
        (*fsm[current_mode].mode_function)();
        (*mfsm[current_movement].movement_function)();
    }
    else
    {
//        fprintf(stderr, "Invalid mode\n");
    }
}

void VerticalMovement_setMessage(uint16_t gripper, uint16_t z)
{
    uint16_t gripperVelocity = 0;
    // set vertical movement
    if (z > 14000)
    {
        /* direction: UP */
        moveGripperUp(FAST);
        // high velocity
        #if DEBUG_CONTROLLER
            printf("Move up: FAST\n");
        #endif
    }
    else if (z > 10000 && z < 14000)
    {
        /* direction: UP */
        moveGripperUp(SLOW);
        // low velocity
        #if DEBUG_CONTROLLER
            printf("Move up: SLOW\n");
        #endif
    }
    else if (z < 7000 && z > 2000)
    {
        /* direction: DOWN */
        moveGripperDown(SLOW);
        // low velocity
        #if DEBUG_CONTROLLER
            printf("Move down: SLOW\n");
        #endif
    }
    else if (z < 2000)
    {
        /* direction: DOWN */
        moveGripperDown(FAST);
        // high velocity
        #if DEBUG_CONTROLLER
            printf("Move down: FAST\n");
        #endif
    }
    else
    {
        moveGripperUp(0);
        moveGripperDown(0);
    }

    // set gripper movement - velocity rate between 0 and 15
    float gripper_value = (float) (gripper);
    if (gripper > 9000)
    {
        gripperVelocity = ((gripper_value - 9000.0) / 7500.0) * 16.0;
        #if DEBUG_CONTROLLER
            printf("OPENING GRIPPER gripperVelocity = %d\n", gripperVelocity);
        #endif
        closeGripper(gripperVelocity);
    }
    else if (gripper < 7000)
    {
        gripperVelocity = 16.0 - (gripper_value / 7000.0) * 16.0;
        #if DEBUG_CONTROLLER
            printf("CLOSING GRIPPER gripperVelocity = %d\n", gripperVelocity);
        #endif
        openGripper(gripperVelocity);
    }
    else
    {
        openGripper(0);
        closeGripper(0);
    }
}

void HorizontalMovement_setMessage(uint16_t x, uint16_t y)
{
    // based on x and y values set direction and velocity
    // set movement along x axis
    if (x > 13500)
    {
        /* direction: RIGHT */
        moveXForward(FAST); // high velocity
        #if DEBUG_CONTROLLER
            printf("Move right: FAST\n");
        #endif
    }
    else if (x > 10000 && x < 13500)
    {
        /* direction: RIGHT */
        moveXForward(SLOW); // low velocity
        #if DEBUG_CONTROLLER
            printf("Move right: SLOW\n");
        #endif
    }
    else if (x < 7000 && x > 2000)
    {
        /* direction: LEFT */
        moveXBackwards(SLOW); // low velocity
        #if DEBUG_CONTROLLER
            printf("Move left: SLOW\n");
        #endif
    }
    else if (x < 2000)
    {
        /* direction: LEFT */
        moveXBackwards(FAST); // high velocity
        #if DEBUG_CONTROLLER
            printf("Move left: FAST\n");
        #endif
    }
    else
    {
        moveXForward(0);
        moveXBackwards(0);
    }

    // set movement along y axis
    if (y > 14000)
    {
        /* direction: FORWARD */
        moveYForward(FAST); // low velocity
        #if DEBUG_CONTROLLER
            printf("Move forward: FAST\n");
        #endif
    }
    else if (y > 10000 && y < 14000)
    {
        /* direction: FORWARD */
        moveYForward(SLOW); // high velocity
        #if DEBUG_CONTROLLER
            printf("Move forward: SLOW\n");
        #endif
    }
    else if (y < 7000 && y > 2000)
    {
        /* direction: BACKWARD */
        moveYBackwards(SLOW); // low velocity
        #if DEBUG_CONTROLLER
            printf("Move backward: SLOW\n");
        #endif
    }
    else if (y < 2000)
    {
        /* direction: BACKWARD */
        moveYBackwards(FAST); // high velocity
        #if DEBUG_CONTROLLER
            printf("Move backward: FAST\n");
        #endif
    }
    else
    {
        moveYForward(0);
        moveYBackwards(0);
    }
}

void stopCartMovements()
{
    moveXBackwards(0);
    moveXForward(0);
    moveYBackwards(0);
    moveYForward(0);
}

void stopGripperMovements()
{
    moveGripperUp(0);
    moveGripperDown(0);
    openGripper(0);
    closeGripper(0);
}

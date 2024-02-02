#include <Controller/include/ControllerFSM.h>

/// @brief Finite state machine for the controller
/// @details The controller has:
///             4 modes: INIT_MODE, MANUAL_MODE, AUTOMATIC_MODE, SELECT_MODE
///             3 movements: HORIZONTAL_MODE, VERTICAL_MODE, SCREEN_MODE
///             3 events: SW_NONE, SW1_PRESSED, SW2_PRESSED, SW3_PRESSED
//TODO: ASk Sara about sending message function
Mode_t current_mode = MANUAL_MODE;
Movement_t current_movement = SCREEN_MODE;
Event_t event = SW_NONE;

extern uint16_t resultsBuffer[2];

ModeMachine_t fsm[] = {
        {INIT_MODE, fn_INIT_MODE},
        {MANUAL_MODE, fn_MANUAL_MODE},
        {AUTOMATIC_MODE, fn_AUTOMATIC_MODE},
        {SELECT_MODE, fn_SELECT_MODE}
};

MovementMachine_t mfsm[] = { //movement finite state machine
        {HORIZONTAL_MODE, fn_HORIZONTAL_MODE},
        {VERTICAL_MODE, fn_VERTICAL_MODE},
        {SCREEN_MODE, fn_SCREEN_MODE}
};

void fn_INIT_MODE(){
    if(event == SW1_PRESSED){
        event = SW_NONE;
        current_mode = MANUAL_MODE;
        printf("MANUAL_MODE\n");
        // horizontal movement is enabled by default
        current_movement = HORIZONTAL_MODE;
    }
}

void fn_MANUAL_MODE(){
    if(event == SW1_PRESSED){
        event = SW_NONE;
        // change mode to automatic
        current_mode = AUTOMATIC_MODE;
        printf("AUTOMATIC_MODE\n");
        current_movement = SCREEN_MODE;
    }
    else if(event == SW2_PRESSED){
        event = SW_NONE;
        // change mode to select
        current_mode = SELECT_MODE;
        printf("SELECT_MODE\n");
        current_movement = SCREEN_MODE;
    }
    
}

void fn_AUTOMATIC_MODE(){
    if(event == SW1_PRESSED){
        event = SW_NONE;
        // change mode to manual
        current_mode = MANUAL_MODE;
        printf("MANUAL_MODE\n");
        current_movement = HORIZONTAL_MODE;
    }
}

void fn_SELECT_MODE(){
    if(event == SW1_PRESSED){
        event = SW_NONE;
        // change mode to manual
        current_mode = MANUAL_MODE;
        printf("MANUAL_MODE\n");
        current_movement = HORIZONTAL_MODE;
    }
    else if(event == SW2_PRESSED){
        // select saved position and send message
        event = SW_NONE;
        printf("Select and send message\n");
        // selezionare e inviare messaggio....
    }
}

void fn_SCREEN_MODE(){
    // based on x and y values set direction and velocity of vertical movement and gripper
    // screenMoveUp() per andare sopra
    // screenMoveDown() per andare sotto
    // screenMenuPosition per disegnare selezione

    // moving in the screen based on resutsBuffer[1]
    uint16_t y_value = resultsBuffer[1];
    if(y_value > 10000){
        printf("Move up\n");
        // move up in the screen if movement is allowed
        screenMoveUp();
        screenMenuPosition();
    }
    else if(y_value < 5000){
        printf("Move down\n");
        // move down in the screen if movement is allowed
        screenMoveDown();
        screenMenuPosition();
    }
}
void fn_HORIZONTAL_MODE(){
    if(event == SW3_PRESSED){
        event = SW_NONE;
        // vertical movement is enabled
        current_movement = VERTICAL_MODE;
        printf("VERTICAL_MODE\n");
    }
    else{
        int16_t x_value = resultsBuffer[0];
        uint16_t y_value = resultsBuffer[1];
        // printf("x_axis = %d\n", x_value);
        // printf("y_axis = %d\n", y_value);
        // based on x and y values set direction and velocity
        HorizontalMovement_setMessage(x_value, y_value);
    }
}
void fn_VERTICAL_MODE(){
    if(event == SW3_PRESSED){
        event = SW_NONE;
        // horizontal movement is enabled
        current_movement = HORIZONTAL_MODE;
        printf("HORIZONTAL_MODE\n");
    }
    else{
        uint16_t x_value = resultsBuffer[0];
        uint16_t y_value = resultsBuffer[1];
        // printf("x_axis = %d\n", x_value);
        // printf("y_axis = %d\n", y_value);
        VerticalMovement_setMessage(x_value, y_value);
    }
}

void Controller(){
    if(current_mode < NUM_MODE && current_movement < NUM_MOVEMENT){
        (*fsm[current_mode].mode_function)();
        (*mfsm[current_movement].movement_function)();
    }
    else{
        fprintf(stderr, "Invalid mode\n");
    }
}

void VerticalMovement_setMessage(uint16_t gripper, uint16_t z){
    uint16_t gripperVelocity = 0;
    // set vertical movement
    if(z > 13500){
        /* direction: UP */
        // moveGripperUp(FAST) // high velocity
        printf("Move up: FAST\n");
    }
    else if(z > 10000 && z < 13500){
        /* direction: UP */
        // moveGripperUp(SLOW) // low velocity
        printf("Move up: SLOW\n");
    }
    else if(z < 7000 && z > 3000){
        /* direction: DOWN */
        // moveGripperDown(SLOW) // low velocity
        printf("Move down: SLOW\n");
    }
    else if(z < 3000){
        /* direction: DOWN */
        // moveGripperDown(FAST) // high velocity
        printf("Move down: FAST\n");
    }
    else{
        // stopZ()
    }

    // set gripper movement - velocity rate between 0 and 15
    float gripper_value = (float)(gripper);
    if(gripper > 9000){
        gripperVelocity = ((gripper_value - 9000.0)/7500.0)*16.0;
        printf("OPENING GRIPPER gripperVelocity = %d\n", gripperVelocity);
        // closeGripper(gripperVelocity)
    }
    else if(gripper < 7000){
        gripperVelocity = 16.0 - (gripper_value/7000.0)*16.0;
        printf("CLOSING GRIPPER gripperVelocity = %d\n", gripperVelocity);
        // openGripper(gripperVelocity)
    }    
}

void HorizontalMovement_setMessage(uint16_t x, uint16_t y){
    // based on x and y values set direction and velocity
    if(x > 13500){
        /* direction: RIGHT */
        // moveXForward(FAST) // high velocity
        printf("Move right: FAST\n");
    }
    else if(x > 10000 && x < 13500){
        /* direction: RIGHT */
        // moveXForward(SLOW) // low velocity
        printf("Move right: SLOW\n");
    }
    else if(x < 7000 && x > 3000){
        /* direction: LEFT */
        // moveXBackward(SLOW) // low velocity
        printf("Move left: SLOW\n");
    }
    else if(x < 3000){
        /* direction: LEFT */
        // moveXBackward(FAST) // high velocity
        printf("Move left: FAST\n");
    }
    else{
        // stopX()
    }

    // sendMessage(HORIZONTAL, message[1], message[2]);
    if(y > 13500){
        /* direction: FORWARD */
        // moveYForward(FAST) // low velocity
        printf("Move forward: SLOW\n");
    }
    else if(y > 10000 && y < 13500){
        /* direction: FORWARD */
        // moveYForward(SLOW) // high velocity
        printf("Move forward: SLOW\n");
    }
    else if(y < 7000 && y > 3000){
        /* direction: BACKWARD */
        // moveYBackward(SLOW) // low velocity
        printf("Move backward: SLOW\n");
    }
    else if(y < 3000){
        /* direction: BACKWARD */
        // moveYBackward(FAST) // high velocity
        printf("Move backward: FAST\n");
    }
    else{
        // stopY()
    }
}

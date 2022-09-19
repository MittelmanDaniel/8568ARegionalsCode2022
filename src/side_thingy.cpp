#include "main.h"

pros::Motor side_motor(19, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

bool side_up=true;
void side_control() {

  // Toggle for mogo
  if (master.get_digital_new_press(DIGITAL_DOWN)) {
    side_up=!side_up;
  } 
  if (side_up){
    //mogo_in();
    side_motor.move_absolute(-100,100);
  }
  else if (!side_up){
    //mogo_out();
    side_motor.move_absolute(-500,100);
  }
}

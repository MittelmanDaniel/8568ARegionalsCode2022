#include "main.h"

//pros::Controller partner (pros::E_CONTROLLER_PARTNER);

const int num_of_pos = 6; // Number of lift positions
//OG 30
 int lift_heights[6] = {29,120, 358, 500, 678, 828}; // Lift Positions


// Driver Control Variables
int up_lock = 0;
int down_lock = 0;
int lift_state = 0;


pros::Motor lift(8, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);

void set_HOLDYHOLD(){
  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

int currentDesiredPos=lift_heights[0] ;

void set_lift(int input)  { lift = input; }

void zero_lift()    { lift.tare_position(); }
int  get_lift()     { return lift.get_position(); }
int  get_lift_vel() { return lift.get_actual_velocity(); }

int set_lift_position(int target, int speed) {
  return lift.move_absolute(target, speed);
}



void raise_Lift_Heights(){
  currentDesiredPos+=5;
}

void lower_Lift_Heights(){
  currentDesiredPos-=5;
}

bool chasey_chasey=false;

void flip_Chasey(){
  chasey_chasey=!chasey_chasey;
}

///
// Driver Control
//  - when R1 is pressed, bring the lift up the position ladder
//  - when R2 is pressed, bring the lift down the position ladder
///




void
lift_control() {
  //CHASEY CONTROLS
  if(chasey_chasey){
    if(master.get_digital(DIGITAL_R1)){
      set_lift(120);
    }
    else if(master.get_digital(DIGITAL_R2)){
      set_lift(-120);
    }
    else{
      set_lift(0);
    }
  }

  //MODE_CONTROLS
  if(!chasey_chasey){
  // Lift Up
  if (master.get_digital(DIGITAL_R1) && up_lock==0) {
    // If lift is at max height, bring it down to 0
    if(lift_state==num_of_pos-1){
      lift_state = lift_state;
    }

    // Otherwise, bring the lift up
    else{
      lift_state++;
    }

    currentDesiredPos=lift_heights[lift_state];

    up_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_R1)) {
    up_lock = 0;
  }

  // Lift Down
  if (master.get_digital(DIGITAL_R2) && down_lock==0) {
    // If the lift is down, bring the lift to max height
    if (lift_state==0){
      lift_state = lift_state;
    }
    // Otherwise, bring the lift down
    else{
      lift_state--;
    }
    currentDesiredPos=lift_heights[lift_state];

    down_lock = 1;
  }
  else if (!master.get_digital(DIGITAL_R2)) {
    down_lock = 0;
  }

  // Set the lift to the current position in the array
  set_lift_position(currentDesiredPos, 125);
  }
}

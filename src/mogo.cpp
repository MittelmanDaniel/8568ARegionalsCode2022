#include "main.h"


const int MOGO_OUT  = 340; // Intaking Mogos


// Driver Control Variables
bool mogo_up = true;
bool is_at_neut = false;
int mogo_lock   = 0;
int controller_mogo_timer = 0;
int mogo_out_timer = 0;

bool is_up = false;
bool is_out = false;

bool mogo_partner_Listen=false;

pros::Motor mogo(5, MOTOR_GEARSET_36, false, MOTOR_ENCODER_DEGREES);




void set_mogo(int input)  { if(mogo_partner_Listen) {mogo = input;} }

void zero_mogo()    { mogo.tare_position(); }
int  get_mogo()     { return mogo.get_position(); }
int  get_mogo_vel() { return mogo.get_actual_velocity(); }

void
set_mogo_position(int target, int speed) {
  mogo.move_absolute(target, speed);
}

void doTheThing(){
  mogo.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}




///
// Driver Control
//  - when L1 is pressed, toggle between in and out.
///
//do pid


void make_listen_partner(){
  mogo_partner_Listen=true;
  doTheThing();
}
bool getIsListening(){
  return mogo_partner_Listen;
}


void
mogo_control() {

  // Toggle for mogo
  if (master.get_digital_new_press(DIGITAL_L1)) {
    mogo_partner_Listen=false;
    mogo_up = !mogo_up;

    mogo_partner_Listen=false;
  }

  // Bring moog to position based on mogo_up
  if(!mogo_partner_Listen){
    if (mogo_up){
      set_mogo_position(310,125);
    }
    else if (!mogo_up){

      set_mogo_position(690,125);
    }
  }

}

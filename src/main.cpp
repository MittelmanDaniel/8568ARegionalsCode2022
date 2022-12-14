#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////



// Chassis constructor

//CREATE MOGO CHASSIS TO FLIP MOTORS
Drive chassis(// Left Chassis Ports (negative port will reverse it!)
//   the first port is the sensored port (when trackers are not used!)
{3, 4}

// Right Chassis Ports (negative port will reverse it!)
//   the first port is the sensored port (when trackers are not used!)
,{-1, -2}

// IMU Port
,9

// Wheel Diameter (Remember, 4" wheels are actually 4.125!)
//    (or tracking wheel diameter)
,4.125

// Cartridge RPM
//   (or tick per rotation if using tracking wheels)
,200

// External Gear Ratio (MUST BE DECIMAL)
//    (or gear ratio of tracking wheel)
// eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
// eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
,1

// Uncomment if using tracking wheels
/*
// Left Tracking Wheel Ports (negative port will reverse it!)
,{1, 2}

// Right Tracking Wheel Ports (negative port will reverse it!)
,{3, 4}
*/

// Uncomment if tracking wheels are plugged into a 3 wire expander
// 3 Wire Port Expander Smart Port
// ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();

  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0.0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. (Comment this line out if you have an SD card!)
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  //chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);
  //chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_X,    pros::E_CONTROLLER_DIGITAL_B);

  // Autonomous Selector using LLEMMU
  ez::as::auton_selector.add_autons({
    //Auton("PID_TESTER\n\n TO TEST PID", driveTesting),
    Auton("Prog Skills\n\nDo Stuff. ", Prog_Skills),
    Auton("High Plat Auton\n\n Get the middle and side neutral goals, then 3 rings on alliance goal", drive_example),
    Auton("Low Plat Auton\n\nGrab Neutral and then rings.", low_Side_Auton),
    Auton("Prog Skills\n\nDo Stuff. ", Prog_Skills),
    //Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    //Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
    //Auton("Combine all 3 movements", combining_movements),
    //Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  //initialize Pneum pneum
  PneumInit();
}
//ghsfukbvhkgactlgabcsilr im in
//hi past Danny this is future Daniel. always listen to luke and keenan
//they know everything and have a higher combined gpa than you,
/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.
  set_HOLDYHOLD();
  ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

bool pickEmUp=false;


pros::Controller partner (pros::E_CONTROLLER_PARTNER);


void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  chassis.set_active_brake(0.1);
  while (true) {

    chassis.tank(); // Tank control
    // chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .


      conveyor_control();

      //PARTNER CONTROLLER RING CONTROLS
        if(partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)  ){
          pickEmUp=!pickEmUp;
        }
        if (pickEmUp){
          set_conveyor(127);
        }
        else{
          set_conveyor(0);
        }


        if(partner.get_digital(DIGITAL_L2)){
           make_listen_partner();
           set_mogo(80);
        }
        else if(partner.get_digital(DIGITAL_L1)){
          make_listen_partner();
           set_mogo(-80);
        }
        else if(getIsListening()){
          set_mogo(0);
        }



      mogo_control();







      if(partner.get_digital(DIGITAL_R2)){
         lower_Lift_Heights();
      }
      if(partner.get_digital(DIGITAL_R1)){
         raise_Lift_Heights();
      }
      if(partner.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
        flip_Chasey();
        partner.rumble("****");
      }
      lift_control();



    //}
    //else{

      pneumCtrl();
      //autoPneum();
      side_control();
      //autoPneum();
    //}
    //z::print_to_screen(std::to_string(get_mogo()));
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

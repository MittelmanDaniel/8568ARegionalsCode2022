#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 110;
const int SWING_SPEED = 90;

const int DOWN_MOGO =685;
const int UP_MOGO=280;

const int num_of_pos = 6; // Number of lift positions
//OG 30
const int lift_heights[num_of_pos] = {30,120, 368, 500, 678, 828}; // Lift Positions

///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(6, 6);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 50, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.56, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.56, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 16, 0.18, 90, 7);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
  chassis.set_exit_condition(chassis.turn_exit,  300, 1,  1000, 3, 300,300);
  //chassis.set_exit_condition(chassis.drive_exit, 80,  50, 300, 150, 100, 100);
}

void AUTO_CRAZY_SPEED() {
  chassis.set_slew_min_power(100, 100);
  chassis.set_slew_distance(3, 3);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 38, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 3.46, 0, 8, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 3.46, 0, 8, 0);
  chassis.set_pid_constants(&chassis.turnPID, 12, 0.08, 45, 5);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
  chassis.set_exit_condition(chassis.turn_exit,  300, 1,  1000, 3, 300,300);
  //chassis.set_exit_condition(chassis.drive_exit, 80,  50, 300, 150, 100, 100);
}

void Lukey_Pukey() {
  chassis.set_slew_min_power(90, 90);
  chassis.set_slew_distance(5, 5);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 38, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.86, 0.4, 12, 4*chassis.get_tick_per_inch());
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.86, 0.4, 12, 4*chassis.get_tick_per_inch());
  chassis.set_pid_constants(&chassis.turnPID, 7, 0.033, 35, 5);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
  //chassis.set_exit_condition(chassis.turn_exit,  100, 3,  1000, 5, 100,100);
  //Exit_COnditions
  chassis.set_exit_condition(chassis.drive_exit, 10000,  20, 750, 50, 500, 500);
}


void one_mogo_constants() {
  chassis.set_slew_min_power(90, 90);
  chassis.set_slew_distance(5, 5);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 38, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.56, 0, 5, 15);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.56, 0, 5, 15);
  chassis.set_pid_constants(&chassis.turnPID, 16, 0.08, 80, 5);

  chassis.set_exit_condition(chassis.turn_exit,  500, 1,  1000, 3, 500,500);
  //chassis.set_exit_condition(chassis.turn_exit,  100, 3,  1000, 5, 100,100);
  //chassis.set_exit_condition(chassis.drive_exit, 80,  50, 300, 150, 100, 100);

  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void mogo_in_tray() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(6, 6);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 38, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 2.56, 0, 8, 15);
  chassis.set_pid_constants(&chassis.backward_drivePID, 2.56, 0, 8, 15);
  chassis.set_pid_constants(&chassis.turnPID, 16, 0.08, 70, 5);

  chassis.set_exit_condition(chassis.turn_exit,  500, 1,  1000, 3, 500,500);
  //chassis.set_exit_condition(chassis.drive_exit, 80,  50, 300, 150, 100, 100);
  chassis.set_exit_condition(chassis.swing_exit, 700, 1,  700, 2,   1000, 1000);

  chassis.set_pid_constants(&chassis.swingPID, 14, 2.94, 120, 5);
}



void two_mogo_constants() {
  chassis.set_slew_min_power(90, 90);
  chassis.set_slew_distance(5, 5);
  chassis.set_pid_constants(&chassis.headingPID, 24, 0.001, 35, 5);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.56, 0, 5, 15);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.56, 0, 5, 15);
  chassis.set_pid_constants(&chassis.turnPID, 16, 0.36, 50, 5);

  chassis.set_exit_condition(chassis.turn_exit,  500, 1,  1000, 3, 700,700);
  //chassis.set_exit_condition(chassis.drive_exit, 80,  50, 300, 150, 100, 100);
  chassis.set_exit_condition(chassis.swing_exit, 500, 1,  700, 5,   1000, 1000);


  chassis.set_pid_constants(&chassis.swingPID, 7, 0.14, 38, 7);
}

///REUSED functions

///
// Interference example
///
void tug (int attempts) {

   master.print(0, 0, "TUG");

  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-36, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 127);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}


///
// Debug
///

void Error_Debug_Printer(){
   //master.clear();
   while(true){

     master.print(0, 0, "Heading: %f", chassis.imu.get_yaw() );
     pros::delay(1500);
     master.print(0, 0, "Output: %f", chassis.forward_drivePID.output );
     pros::delay(1500);

     master.print(0,0,"Error: %f", chassis.forward_drivePID.error);
     pros::delay(1500);
     pros::delay(ez::util::DELAY_TIME);
   }
}

void DRIVE_Debug_Printer(){
   //master.clear();
   while(true){

     master.print(0, 0, " Left Error: %f", chassis.leftPID.error);
     pros::delay(1500);
     master.print(0, 0, "Left_Power: %f", chassis.leftPID.output );
     pros::delay(1500);

     master.print(0, 0, "Right Error: %f", chassis.rightPID.error );
     pros::delay(1500);
     master.print(0, 0, "Right_Velocity: %f", chassis.leftPID.output );
     pros::delay(1500);

     pros::delay(ez::util::DELAY_TIME);
   }
}

void debugger_ONCE(){
    master.print(0, 0, "Heading: %f", chassis.imu.get_yaw() );
}
///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  AUTO_CRAZY_SPEED();
  //make pneum open
  PneumInit();

  //set lift to grab height
  set_lift_position(lift_heights[0], 120);
  //goforward to grab
  chassis.set_drive_pid(44, DRIVE_SPEED, true);

  chassis.wait_until(36);

  while(!isOut){
    autoPneum();
    pros::delay(ez::util::DELAY_TIME);
  }

  chassis.wait_drive();

  one_mogo_constants();

  set_lift_position(lift_heights[1], 120);
  debugger_ONCE();

  if (chassis.interfered) {

  }

  chassis.set_drive_pid(-48, DRIVE_SPEED, true);

  if(chassis.interfered){
    master.print(0, 0, "HEAVE");
    tug(1000);
  }

  chassis.wait_until(-26);
  //set_lift_position(lift_heights[0], 120);
  PneumInit();

  default_constants();

  chassis.wait_drive();



  set_lift_position(lift_heights[0], 120);
  //CHANGE CONSTANTS
  //one_mogo_constants();
  //pros::delay(150);


//OLD TURN AND DROP

/*
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();


  set_lift_position(lift_heights[2], 120);
  //pros::delay(500);



  PneumInit();
  //pros::delay(500);
  set_lift_position(lift_heights[0], 120);
  //pros::delay(500);

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
*/

  chassis.set_turn_pid(-33.5, TURN_SPEED);
  chassis.wait_drive();

  debugger_ONCE();

  PneumInit();
  //ez::print_ez_template();
  chassis.set_drive_pid(58, DRIVE_SPEED, true);
  debugger_ONCE();
  while(!isOut){
    autoPneum();
    pros::delay(ez::util::DELAY_TIME);
  }

  chassis.wait_drive();
  one_mogo_constants();
  pros::delay(150);

  set_lift_position(lift_heights[1], 120);
  //pros::delay(500);
  //-64 old one
  chassis.set_drive_pid(-55, DRIVE_SPEED, true);

  set_mogo_position(DOWN_MOGO-20,120);

  chassis.wait_drive();


//OLD TURN AND PUSH

  chassis.set_turn_pid(-94, TURN_SPEED);
  chassis.wait_drive();

  debugger_ONCE();
/*
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  //PneumInit();
  //mogo_out(true);
*/
  set_mogo_position(DOWN_MOGO,120);
  pros::delay(150);

  chassis.set_drive_pid(-23, DRIVE_SPEED, true);
  chassis.wait_drive();



  //mogo_in(true);
  set_mogo_position(UP_MOGO,120);
  pros::delay(800);
  set_conveyor(127);
  pros::delay(900);
  chassis.set_drive_pid(18, DRIVE_SPEED, true);
  chassis.wait_drive();



  //Error_Debug_Printer();
  //chassis.set_drive_pid(-12, DRIVE_SPEED);
  //chassis.wait_drive();
  //turnToNeutralMOGO();
  //flipPneum();

  //chassis.set_drive_pid(-12, DRIVE_SPEED);
  //chassis.wait_drive();



    //chassis.set_turn_pid(180, TURN_SPEED);

    //chassis.wait_drive();

    //chassis.set_turn_pid(0, TURN_SPEED);

    //Error_Debug_Printer();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at

  //set lift to grab height
  set_lift_position(31, 120);
  //goforward to grab
  chassis.set_drive_pid(53, DRIVE_SPEED, true);

  chassis.wait_until(40);

  while(!isOut){
    autoPneum();
    pros::delay(ez::util::DELAY_TIME);
  }

  chassis.wait_drive();

  one_mogo_constants();

  set_lift_position(120, 120);

  chassis.set_drive_pid(-53, DRIVE_SPEED, true);
  chassis.wait_until(-45);
  PneumInit();
  default_constants();
  set_lift_position(30, 120);
  chassis.wait_drive();

  chassis.set_turn_pid(-88, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(8, DRIVE_SPEED, true);
  chassis.wait_drive();

  set_mogo_position(DOWN_MOGO,120);
  pros::delay(800);
  chassis.set_drive_pid(-18, DRIVE_SPEED, true);
  chassis.wait_drive();

  pros::delay(800);

  set_mogo_position(UP_MOGO,120);
  pros::delay(500);

  chassis.set_drive_pid(10, DRIVE_SPEED, true);
  chassis.wait_drive();

  set_mogo_position(UP_MOGO,120);

  //set_mogo_position(155,100);
  pros::delay(500);
  set_conveyor(127);
  //chassis.set_turn_pid(45, TURN_SPEED);
  //chassis.wait_drive();

  //chassis.set_turn_pid(0, TURN_SPEED);
  //chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void checkGoal_and_Move(){

}

void Prog_Skills(){
  chassis.set_pid_constants(&chassis.headingPID, 38, 0, 120, 5);
  //SET MOGO TRAY DOWN AND GO PICK UP MOGO
  set_mogo_position(DOWN_MOGO,120);
  pros::delay(1500);
  chassis.set_drive_pid(-13, 50);
  chassis.wait_drive();

  //PICK UP MOGO
  set_mogo_position(UP_MOGO,120);
  pros::delay(750);


  //////////////
  /// SWITCHIHNG CONSTANTS
  ///////////////
  mogo_in_tray();
  chassis.set_pid_constants(&chassis.headingPID, 34, 0, 120, 5);

  //DRIVE away from platform
  chassis.set_drive_pid(9.5, 50);
  chassis.wait_drive();
  mogo_in_tray();
  pros::delay(150);
  //chassis.set_turn_pid( -68, TURN_SPEED);
  //chassis.wait_drive();

  //SWING TO FACE NEUTRAL
  chassis.set_swing_pid(ez::LEFT_SWING, 90+24.3, SWING_SPEED);
  //Error_Debug_Printer();
  chassis.wait_drive();

  master.print(0, 0, "Heading: %f", chassis.imu.get_yaw() );

  pros::delay(60);



  set_lift_position(lift_heights[0], 100);
  pros::delay(150);
  PneumInit();

  //GO GRAB FIRST NEUTRAL

  //ez::print_ez_template();
  chassis.set_drive_pid(65, DRIVE_SPEED, true);
  int timepassed=0;
  chassis.wait_until(45);
  while(!isOut){
    autoPneum();
    /*
    bool alreadySwung=false;
    if(timepassed>4000 && !alreadySwung){

      chassis.set_swing_pid(ez::LEFT_SWING, 90+24.3+10, SWING_SPEED);
      chassis.wait_drive();
      autoPneum();
      chassis.set_swing_pid(ez::LEFT_SWING, 90+24.3, SWING_SPEED);
      chassis.wait_drive();

      chassis.set_swing_pid(ez::RIGHT_SWING, 90+24.3-10, SWING_SPEED);
      chassis.wait_drive();
      autoPneum();
      chassis.set_swing_pid(ez::RIGHT_SWING, 90+24.3, SWING_SPEED);
      chassis.wait_drive();
      alreadySwung=true;
    }
    */
    if(isOut){
      set_lift_position(lift_heights[1], 120);
    }
    pros::delay(ez::util::DELAY_TIME);
    timepassed+=ez::util::DELAY_TIME;


  }

  chassis.wait_drive();





////////////////////////
//SWITCHING CONSTANTS///
////////////////////////

  two_mogo_constants();

  //add +25 if needed
  //chassis.set_turn_pid( -60-180+25, TURN_SPEED);
  //chassis.wait_drive();

  //TURN FOR GOOD PLATFORM PLACEMENT
  chassis.set_turn_pid( 90+24+5, TURN_SPEED);
  chassis.wait_drive();

  chassis.wait_drive();
  GrabMogo();
  set_lift_position(lift_heights[4], 120);
  pros::delay(800);

  //DRIVE TO PLATFORM
  chassis.set_drive_pid(27,DRIVE_SPEED,true);
  chassis.wait_drive();

  //PLACE DOWN PLATFORM
  set_lift_position(lift_heights[2], 120);
  pros::delay(750);

  //chassis.set_turn_pid(-270,TURN_SPEED);
  //chassis.wait_drive();
  //pros::delay(500);

  PneumInit();
  pros::delay(150);

  //GO BACK AND DROP MOGO
  chassis.set_drive_pid(-4,DRIVE_SPEED);
  chassis.wait_drive();


////SWITCHING CONSTANTS
  mogo_in_tray();

  set_lift_position(lift_heights[3], 120);

  chassis.set_drive_pid(-13.5,DRIVE_SPEED,true);
  chassis.wait_drive();

  chassis.set_turn_pid( 180+45, TURN_SPEED);
  chassis.wait_drive();

  master.print(0, 0, "Heading: %f", chassis.imu.get_yaw() );

  set_lift_position(lift_heights[0], 120);
  set_mogo_position(DOWN_MOGO,120);
  pros::delay(750);

  //chassis.set_drive_pid(-8, DRIVE_SPEED, true);
  //chassis.wait_drive();

  default_constants();
  chassis.set_drive_pid(55,DRIVE_SPEED,true);

  while(!isOut){
    autoPneum();
    if(isOut){
      set_lift_position(lift_heights[1], 120);
    }
  }

  chassis.wait_until(30);
  set_mogo_position(UP_MOGO,120);
  chassis.wait_drive();

  one_mogo_constants();





  chassis.set_turn_pid( 270+28, TURN_SPEED);
  chassis.wait_drive();


  set_lift_position(lift_heights[3], 120);
  pros::delay(750);

  //DRIVE TO PLATFORM
  chassis.set_drive_pid(30,50,true);
  chassis.wait_drive();

  //PLACE DOWN PLATFORM
  set_lift_position(lift_heights[2], 120);
  pros::delay(750);

  //chassis.set_turn_pid(-270,TURN_SPEED);
  //chassis.wait_drive();
  //pros::delay(500);

  PneumInit();
  pros::delay(150);

  //GO BACK AND DROP MOGO
  chassis.set_drive_pid(-4,DRIVE_SPEED);
  chassis.wait_drive();

  set_lift_position(lift_heights[3], 80);

  default_constants();
  chassis.set_drive_pid(-7,DRIVE_SPEED,true);
  chassis.wait_drive();

  chassis.set_turn_pid(360, TURN_SPEED);
  chassis.wait_drive();

  set_mogo_position(DOWN_MOGO,120);
  pros::delay(300);

  chassis.set_drive_pid(-34,DRIVE_SPEED,true);
  chassis.wait_drive();

  set_mogo_position(UP_MOGO,120);
  pros::delay(300);

  mogo_in_tray();

  set_lift_position(lift_heights[0], 120);
  pros::delay(300);

  chassis.set_drive_pid(14,DRIVE_SPEED,true);
  chassis.wait_drive();

  chassis.set_turn_pid(360+90, TURN_SPEED);
  chassis.wait_drive();

  //set_conveyor(127);

  chassis.set_drive_pid(54,DRIVE_SPEED,true);



  timepassed=0;

  while(!isOut){
    autoPneum();
    if(isOut){
      set_lift_position(lift_heights[1], 120);
    }
  }

  chassis.wait_drive();

  two_mogo_constants();

  chassis.set_turn_pid(360+45, TURN_SPEED);
  chassis.wait_drive();


  set_lift_position(lift_heights[3], 120);
  pros::delay(750);

  //DRIVE TO PLATFORM
  chassis.set_drive_pid(23,DRIVE_SPEED,true);
  chassis.wait_drive();

  //PLACE DOWN PLATFORM
  set_lift_position(lift_heights[2], 120);
  pros::delay(750);
  PneumInit();
  pros::delay(150);
  //GO BACK AND DROP MOGO
  chassis.set_drive_pid(-4,DRIVE_SPEED);
  chassis.wait_drive();


  set_lift_position(lift_heights[3], 80);
  mogo_in_tray();
  chassis.set_drive_pid(-6,DRIVE_SPEED,true);
  chassis.wait_drive();


  chassis.set_turn_pid(360,TURN_SPEED);
  chassis.wait_drive();

  set_lift_position(lift_heights[0], 80);
  pros::delay(300);

  chassis.set_drive_pid(60,DRIVE_SPEED,true);

  chassis.wait_until(50);

  timepassed=0;

  while(!isOut){
    autoPneum();
    if(isOut){
      set_lift_position(lift_heights[1], 120);
    }
  }

  chassis.wait_drive();

  two_mogo_constants();

  set_lift_position(lift_heights[3], 120);


  chassis.set_turn_pid(360+135,TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(20,DRIVE_SPEED,true);
  chassis.wait_drive();

  PneumInit();
  pros::delay(150);

  mogo_in_tray();
  //GO BACK AND DROP MOGO
  chassis.set_drive_pid(-6,DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(360,TURN_SPEED);
  chassis.wait_drive();
  set_lift_position(lift_heights[0], 120);
  pros::delay(750);

  chassis.set_drive_pid(20,DRIVE_SPEED,true);

  chassis.wait_until(8);

  timepassed=0;

  while(!isOut){
    autoPneum();
    if(isOut){
      set_lift_position(lift_heights[1], 120);
    }
  }

  chassis.wait_drive();

  two_mogo_constants();

  chassis.set_turn_pid(270,TURN_SPEED);
  chassis.wait_drive();
  set_mogo_position(DOWN_MOGO,120);
  one_mogo_constants();


  chassis.set_drive_pid(55,DRIVE_SPEED,true);
  chassis.wait_until(40);
  set_lift_position(lift_heights[3], 120);
  chassis.wait_drive();
  //set_mogo_position(UP_MOGO,120);
  //pros::delay(300);
  chassis.set_turn_pid(270-45,TURN_SPEED);
  chassis.wait_drive();

  chassis.set_pid_constants(&chassis.forward_drivePID, 3.46, 0, 8, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 3.46, 0, 8, 0);

  chassis.set_drive_pid(65,DRIVE_SPEED,true);
  chassis.wait_until(58);

  PneumInit();

  chassis.wait_drive();

  PneumInit();

  chassis.set_drive_pid(-4,DRIVE_SPEED,true);
  chassis.wait_drive();




}



void low_Side_Auton(){

    //set lift to grab height
    set_lift_position(lift_heights[0], 120);
    //goforward to grab
    chassis.set_drive_pid(53, DRIVE_SPEED, true);

    chassis.wait_until(40);

    while(!isOut){
      autoPneum();
      pros::delay(ez::util::DELAY_TIME);
    }

    chassis.wait_drive();

    one_mogo_constants();

    set_lift_position(lift_heights[1], 120);

    chassis.set_drive_pid(-53, DRIVE_SPEED, true);
    chassis.wait_until(-45);
    PneumInit();
    default_constants();
    set_lift_position(30, 120);
    chassis.wait_drive();

    chassis.set_turn_pid(-88, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(8, DRIVE_SPEED, true);
    chassis.wait_drive();

    set_mogo_position(DOWN_MOGO,120);
    pros::delay(800);
    chassis.set_drive_pid(-18, DRIVE_SPEED, true);
    chassis.wait_drive();

    pros::delay(800);

    set_mogo_position(UP_MOGO,120);
    pros::delay(500);

    chassis.set_drive_pid(10, DRIVE_SPEED, true);
    chassis.wait_drive();

    set_mogo_position(UP_MOGO,120);

    //set_mogo_position(155,100);
    pros::delay(500);
    set_conveyor(127);

}

void driveTesting(){
    chassis.toggle_auto_print(true);
    Lukey_Pukey();

    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    DRIVE_Debug_Printer();
    chassis.wait_drive();

}

void tunerTime(){

    set_mogo_position(DOWN_MOGO,120);
    pros::delay(750);
    chassis.set_drive_pid(-12, DRIVE_SPEED);
    chassis.wait_drive();

    set_mogo_position(UP_MOGO,120);
    pros::delay(750);
    set_mogo_position(UP_MOGO,120);
    pros::delay(750);
    mogo_in_tray();

    chassis.set_drive_pid(6, DRIVE_SPEED, true);
    chassis.wait_drive();

    pros::delay(750);
    //chassis.set_turn_pid( -68, TURN_SPEED);
    //chassis.wait_drive();
    chassis.set_swing_pid(ez::LEFT_SWING, 90+24, SWING_SPEED);
    Error_Debug_Printer();
    chassis.wait_drive();

    set_lift_position(lift_heights[0], 100);
    pros::delay(750);
    PneumInit();

}

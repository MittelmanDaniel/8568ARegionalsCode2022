#include "main.h"

#define FAR_VISION_PORT 11

pros::Vision vision_sensor (FAR_VISION_PORT,pros::E_VISION_ZERO_CENTER);
pros::vision_signature_s_t NEUTRAL = pros::Vision::signature_from_utility(1, 1723, 2169, 1946, -5067, -4731, -4898, 2.9, 0);

void turnToNeutralMOGO(){
  int centerofmogo;
  double GoP=0.0002;
  //abs(centerofmogo) > 3
  do{
    //1=neutral
    pros::vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);
    centerofmogo=rtn.x_middle_coord;
    master.print(0, 0, "CenterofMogo: %d:",centerofmogo);
    chassis.left_motors[0].move_velocity(centerofmogo*GoP);
    chassis.left_motors[1].move_velocity(centerofmogo*GoP);

    chassis.right_motors[0].move_velocity(-centerofmogo*GoP);
    chassis.right_motors[1].move_velocity(-centerofmogo*GoP);

  } while( true);
}

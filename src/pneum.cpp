#include "main.h"

#define DIGITAL_SENSOR_PORT 'A'
pros::ADIDigitalOut piston (DIGITAL_SENSOR_PORT);
pros::Distance distanceSensor(14);
bool isOut=false;

void PneumInit(){
  piston.set_value(false);
  isOut=false;
}
void flipPneum(){
    if(!isOut){
      piston.set_value(true);
      isOut=true;
    }
    else{
      piston.set_value(false);
      isOut=false;
    }

}

void ReleaseMogo(){
  piston.set_value(false);
  isOut=false;
}
void GrabMogo(){
  piston.set_value(true);
  isOut=true;
}

int timePassed=0;


void pneumCtrl(){
  // The first value is sensor value
  if(distanceSensor.get() <11 && distanceSensor.get() > 0 && isOut==false && timePassed>750){
    piston.set_value(true);
    isOut=true;
    master.rumble(".");


    //return true;
  }


  if(master.get_digital_new_press(DIGITAL_L2)){

    flipPneum();
    timePassed=0;
  }
  timePassed+=ez::util::DELAY_TIME;
}


void autoPneum(){
    //master.print(0, 0, "Distance: %d:",distanceSensor.get());

  if(distanceSensor.get() <11 && distanceSensor.get() > 0 && isOut==false){

    piston.set_value(true);
    isOut=true;
    master.rumble(".");
    ez::print_to_screen("SCHWIFTY");


    //return true;
  }
  //return false;
  //pros::delay(ez::util::DELAY_TIME);
}

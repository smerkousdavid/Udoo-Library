//This document was made so you wouldn't have to hassle typing all the needed
//Crap ehich just wastes time

#include <Udoo.h> //Import Udoo library

Udoo udoo; //New Instance

void setup() {
  ////////////////////////////////////////////
  
  //^^^ Pinmode and other small things ^^^///
  udoo.init(); //ALWAYS needed, this is the part that tells the linux to start
  //////////////////////////////////////////
  
  
  //^^^ Udoo commands that start with udoo ^^^//
  //^^^ You can still run other commands EXCEPT SERIAL!! and pins 0, 1//
  udoo.stop(); //Tell the linux side to shut it and close the processor line
  //vvvv Commands that might require Serialvvv//
  
  // REMEMVER YOU CAN"T RUN udoo.init(); again!!! as soon as you say
  //stop it won't run again
  
}
void loop() {
  //Forever looping, well until you tell the udoo to cram it or it burns out

}

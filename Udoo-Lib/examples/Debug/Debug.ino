#include <Udoo.h>

Udoo udoo;

void setup() {
  udoo.init(); //Must call this before any other udoo commands but can be placed after regular commands
  udoo.debug("LINE 1"); //The debug command auto creates new line
  udoo.debug("Hello World!");
  for(int a = 0; a < 3; a++)
  {
   udoo.debug("Place string here: " + String(a)); //Make sure it's a String
     //Imaginary a++;                             //Well Strings are easy so that's fun
  }  //Yaaayy ^
}

void loop() {
    //Do nothing...
}

#include <Udoo.h>

Udoo udoo;

void setup() {
  udoo.init(); //Must call this before any other udoo commands but can be placed after regular commands
  udoo.debug("LINE 1"); //The debug command auto creates new line
  udoo.debug("Hello World!\nLine three");//You can also manually insert new line
  udoo.stop(); //Stop serial line
}

void loop() {
    //Do nothing...
}

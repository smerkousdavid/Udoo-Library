#include <Udoo.h>

Udoo udoo;

void setup() {
  udoo.init(); //Allways needed before any other Udoo command
  udoo.linuxCommand("cd /home/ubuntu/Desktop && sudo echo Test file > testfile.txt && echo This command came from the Arduino side"); //Run a Command on the linux side
  udoo.stop(); //Stop Serial line if you want to use it for something else
}

void loop() {
  //Nothing

}

#include <Udoo.h> //Import Udoo library

Udoo udoo; //instance(Don't you love colors

void setup() {
  udoo.init(); //Allways needed before any other Udoo command
  udoo.linuxCommand("echo This command came from the Arduino side"); //Run a Command on the linux side
    //Run commands like in the Terminal ^^^
    //Remember it runs in seperate thread
}

void loop() {
  //Nothing

}

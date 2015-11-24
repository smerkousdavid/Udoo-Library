#include <Udoo.h>

Udoo udoo;
Usb usb;

void setup() {
  udoo.init(); //Must call this before any other udoo commands
  usb.start("/dev/tty", 115200); //First input is port second it bitrate (Current set won't work)
  usb.send("Hello from udoo Serial to Serial"); //Please don't use newline
  udoo.debug("Got from usb: "+ usb.read()); //wait until readline on usb port(Serial)
  usb.stop(); //Close the line

}

void loop() {
}

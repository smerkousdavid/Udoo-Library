#include "Arduino.h"
#include "Udoo.h"

Udoo builtinUsb;
#define wait Usb::waiter

String Usb::read()
{
  builtinUsb.parseWrite("SERIALread","");
  return String(builtinUsb.parseRead("SERIALread"));
}

void Usb::write(String toWrite)
{
  builtinUsb.parseWrite("SERIALwrite", String(toWrite));
  wait();
}

void Usb::start(String port, int bit)
{
  builtinUsb.parseWrite("SERIALstart", port+"<%=BIT=%>"+String(bit));
  wait();
}

void Usb::stop()
{
  builtinUsb.parseWrite("SERIALstop", "");
  wait();
}

void Usb::waiter()
{
  builtinUsb.waiting();
}

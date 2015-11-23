#include "Arduino.h"
#include "Udoo.h"

Udoo builtinStor;
#define wait Storage::waiter

void Storage::readFile(String directory)
{
  builtinStor.parseWrite("READfile",directory);
  return builtinStor.parseRead("PULLfile");
}

void Storage::writeFile(String directory, String toWrite)
{
  builtinStor.parseWrite("WRITEfile", directory+"<%=TOWRITE=%>"+toWrite);
  wait();
}

String Storage::appendTo(String directory, String toWrite)
{
  builtinStor.parseWrite("APPENDfile", directory+"<%=TOWRITE=%>"+toWrite);
  wait();
}

void Storage::readLine(String directory, int line)
{
  builtinStor.parseWrite("READline", directory+"<%=LINES=%>"+String(line));
  return builtinStor.parseRead("PULLline");
}

void Storage::waiter()
{
  builtinStor.waiting();
}

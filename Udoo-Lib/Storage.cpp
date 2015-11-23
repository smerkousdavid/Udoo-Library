#include "Arduino.h"
#include "Udoo.h"

Udoo builtinStor;
#define wait Storage::waiter

String Storage::readFile(String directory)
{
  builtinStor.parseWrite("READfile",directory);
  String replacer = String(builtinStor.parseRead("PULLfile"));
  replacer.replace("\\n","\n");
  return replacer;
}

void Storage::writeFile(String directory, String toWrite)
{
  toWrite.replace("\n","\\n");
  builtinStor.parseWrite("WRITEfile", directory+"<%=TOWRITE=%>"+String(toWrite));
  wait();
}

void Storage::appendTo(String directory, String toWrite)
{
  toWrite.replace("\n","\\n");
  builtinStor.parseWrite("APPENDfile", directory+"<%=TOWRITE=%>"+String(toWrite));
  wait();
}

String Storage::readLine(String directory, int line)
{
  builtinStor.parseWrite("READline", directory+"<%=LINES=%>"+String(line));
  return builtinStor.parseRead("PULLline");
}

void Storage::waiter()
{
  builtinStor.waiting();
}

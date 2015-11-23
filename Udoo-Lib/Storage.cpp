#include "Arduino.h"
#include "Udoo.h"

Udoo builtinStor;
#define wait Storage::waiter

String Storage::readFile(String directory)
{
  builtinStor.parseWrite("READfile",directory);
  return String(builtinStor.parseRead("PULLfile")).replace('<%=newline=%>','\n');
}

void Storage::writeFile(String directory, String toWrite)
{
  builtinStor.parseWrite("WRITEfile", directory+"<%=TOWRITE=%>"+String(toWrite).replace('\n','<%=newline=%>'));
  wait();
}

void Storage::appendTo(String directory, String toWrite)
{
  builtinStor.parseWrite("APPENDfile", directory+"<%=TOWRITE=%>"+String(toWrite).replace('\n','<%=newline=%>'));
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

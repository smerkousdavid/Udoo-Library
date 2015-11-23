#include <Udoo.h>

Udoo udoo;
Storage storage;
String file = "/home/ubuntu/Desktop/TEST.txt";

void setup() {
   udoo.init(); //Start serial line
  /*
    Writing to A file
  */
  storage.writeFile(file, "Line 1\nLine 2"); //This will rewrite/create a file and input some initial stuff
  storage.appendTo(file, "Line 3");
  storage.appendTo(file, "Line 4\nLine 5"); //Append without rewriting to a file
  //These autoclose so there isn't a close function
  
  /*
    Reading from a file
  */
  Strign fileText = storage.readFile(file); //This will return everyline in the file even images(as base)
  udoo.debug("In the file: "+fileText);
  String oneLine = storage.readLine(file, 0); //Pull first line from file
  String lineTwo = storage.readLine(file, 1); //Pull second line from file
  
  udoo.debug("First line: "+oneLine+"\nSecond Line: "+lineTwo);
}

void loop() {
  //Nothing
}

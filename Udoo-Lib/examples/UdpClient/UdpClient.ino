#include <Udoo.h> //Import the Udoo Library

Udoo udoo; //Create a new Instance

void setup() {
  udoo.init(); //Must call this before any other udoo commands
  udoo.udpClient("192.168.1.250", 8080); //Set Ip and port for udpClient

}

void loop() {
  udoo.clientSendUdp("From Udoo"); //Send String to Server
  udoo.debug(udoo.clientRecvUdp()); //Since theserial port is used you
                                 //must use udoo.debug to print information
                                 //The clientRecv returns a Full String for Udp
  delay(5000); //Remember not to spam the server
  //Udp packets don't need to be closed
}

#include <Udoo.h> //Import the Udoo Library

Udoo udoo; //Create a new Instance

void setup() {
  udoo.init(); //Must call this before any other udoo commands
  udoo.tcpClient("192.168.1.250", 8080); //Set Ip and port for TcpClient

}

void loop() {
  udoo.clientSend("From Udoo"); //Send String to Server
  udoo.debug(udoo.clientRecv()); //Since theserial port is used you
                                 //must use udoo.debug to print information
                                 //The clientRecv returns a Full String for TCP
  udoo.tcpClose(); //Yout must close a TCP socket
  delay(5000); //Remember not to spam the server
}

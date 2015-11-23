#include <Udoo.h>

Udoo udoo;
TcpClient client;

void setup() {
  udoo.init(); //Must call this before any other udoo commands
  client.connect("192.168.1.250", 8080); //Set Ip and port for TcpClient

}

void loop() {
  client.send("From Udoo"); //Send String to Server
  udoo.debug(client.recv()); //Recieve from server then send to console
  client.close(); //Close the socket
  delay(1000);
}

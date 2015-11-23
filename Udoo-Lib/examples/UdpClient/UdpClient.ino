#include <Udoo.h>

Udoo udoo;
UdpClient client;

void setup() {
  udoo.init(); //Must call this before any other udoo commands
  client.connect("192.168.1.250", 8080); //Set Ip and port for udpClient

}

void loop() {
  client.send("From Udoo"); //Send String to Server (Udp client should send first)
  udoo.debug(client.recv()); //Recieve from Server and print result to console
  delay(1000);
}

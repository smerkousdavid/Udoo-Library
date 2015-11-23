#include <Udoo.h>

Udoo udoo;
UdpServer server;

void setup() {
  udoo.init(); //Start serial line with Linux
  server.start(8080); //Start Udp Server on port 8080

}

void loop() {
  String response = server.recv(); //Must recieve first before sending for udp
  debug("Got from client: "+response); //Send to debuging
  server.send("From the Udoo"); //Send message back to client
}

void debug(String message)
{
 udoo.debug(message); 
}

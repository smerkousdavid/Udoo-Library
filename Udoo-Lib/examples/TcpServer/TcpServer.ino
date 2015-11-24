#include <Udoo.h>

Udoo udoo;
TcpServer server;

void setup() {
    udoo.init(); //Must be called before any udoo commands
    server.start(8080); //Start tcp server
    //To stop a server use server.stop()
    String ip = udoo.getIp(); //Get the current Linux side Ip address
    debug(ip); //Debug on the console the current ip (Function below)
    
}

void loop() {
  server.clientWait(10); //Wait until a client connects, then delay 10 mileseconds
  debug("Got Client");
  debug(server.recv()); //Recieve from server and print to console
  server.send("Got it bud!"); //Send back to Client
  server.close(); //Close the client connection

}

void debug(String toDebug) {
  udoo.debug(toDebug); //Just a function to make the call smaller
}

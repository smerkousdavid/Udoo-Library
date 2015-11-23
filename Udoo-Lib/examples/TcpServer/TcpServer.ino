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
  server.clientWait(); //Wait until a client connects
  debug("Got Client");
  debug(udoo.recv()); //Recieve from server and print to console
  udoo.send("Got it bud!"); //Send back to Client
  udoo.close(); //Close the client connection

}

void debug(String toDebug) {
  udoo.debug(toDebug); //Just a function to make the call smaller
}

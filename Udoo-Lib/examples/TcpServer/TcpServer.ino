#include <Udoo.h> //Import Library

Udoo udoo; //New Instance

/*Now remember the Tcp server is a lot more complicated then
The client, While you can have multiple servers, it is extremely
Unrecommended, If any way possible use the Tcp client for 
reliability purposes

The reason why is because the Sam is only a single thread and it is a little
difficult a multithread process on the linux side, since a client is
single threaded I recommend using the Udoo as a client, Unless you
develop custom code for a TCP Server, Since i made this library in less
than a Day it is still under dev
*/

void setup() {
    udoo.init(); //Must be called before any udoo commands
    udoo.tcpServer(8080); //Tell the Linux script to get a Server ready on port 
    String ip = udoo.getIp(); //Get the current Linux side Ip address
    debug(ip); //Debug on the console the current ip
    if(ip.indexOf("0") == 0) //The script will return 0 if not connected
    {
       debug("Not connected to the Internet/Router");
       while(1); //No point on moving one
    }
    
    
}

void loop() {
  udoo.waitForClient(); //Remember to call this to make sure you have a connection
  debug("Got Client");
  debug(udoo.recvFromClient()); //Wait until the Client sends some data
  delay(500); //Don't rush things
  udoo.sendToClient("Got it"); //Send back to the client to say A OK
  udoo.closeTheClient(); //Make sure you close the client connection

}

void debug(String toDebug) {
  udoo.debug(toDebug); //Just a function to make the call smaller
}

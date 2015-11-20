#include <Udoo.h> //Import library

Udoo udoo; //New Instance

//If you can try to use Udp Client I recommend it becuase the
//Servers are hard to access on multithreads, which the arduino is single
//So trying to call the linux server witht the single line can get tricky and
//Since clients are single threaded I recommend using the client

void setup() {
  udoo.init(); //Has to be called
  udoo.udpServer(8080); //Tell the linux side to prepare a Udp Server

}

void loop() {
  String response = udoo.recvFromClientUdp(); //Recommended to receive first, so that the program can get the client IP
                            //Other wise when sending first manually input the client Ip
  delay(100);
  String ip = udoo.udpGetClientIp(); //Only needed when you want to send something back AND you received something first
  debug("Got a response of: " + response + " from: " + ip);
  delay(20);
  udoo.sendToClientUdp(ip, "From the Udoo"); //Send back to received IP and send a String
  //THE IP MUST BE A TUPLE LIKE This "('ip address', port)" < add appos around ip
                    
  //No need to Close the Udp Packet
  delay(100); //Add some delays, so the script can update  

}

void debug(String message)
{
 udoo.debug(message); 
}

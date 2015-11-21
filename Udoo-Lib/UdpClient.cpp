#include "Arduino.h"
#include "Udoo.h"

Udoo builtinUDP;
#define wait UdpClient::waiter

void UdpClient::connect(String ip, int port)
{
  builtinUDP.parseWrite("Udpstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void UdpClient::send(String toSend)
{
  builtinUDP.parseWrite("Udpsend", toSend);
  wait();
}

String UdpClient::recv()
{
  builtinUDP.parseWrite("Udprecv","");
  return builtinUDP.readLine();
}

void UdpClient::close()
{
  builtinUDP.parseWrite("Udpclose","");
  wait();
}

void UdpClient::waiter()
{
  builtinUDP.waiting();
}

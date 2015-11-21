#include "Arduino.h"
#include "Udoo.h"

Udoo builtinUDP;
#define wait UdpClient::waiter

void UdpClient::connect(String ip, int port)
{
  builtinUDP.parseWrite("UDPstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void UdpClient::send(String toSend)
{
  builtinUDP.parseWrite("UDPsend", toSend);
  wait();
}

String UdpClient::recv()
{
  builtinUDP.parseWrite("UDPrecv","");
  return builtinUDP.parseRead("UDPrecv");
}

void UdpClient::waiter()
{
  builtinUDP.waiting();
}

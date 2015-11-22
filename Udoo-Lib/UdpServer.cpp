#include "Arduino.h"
#include "Udoo.h"

Udoo builtinUDPS;
#define wait UdpServer::waiter

void UdpServer::start(int port)
{
  builtinUDPS.parseWrite("UDPSERVstart",String(port));
  wait();
}

void UdpServer::stop()
{
  builtinUDPS.parseWrite("UDPSERVstop","");
  wait();
}

void UdpServer::send(String toSend)
{
  builtinUDPS.parseWrite("UDPSERVsend", toSend);
  wait();
}

String UdpServer::recv()
{
  builtinUDPS.parseWrite("UDPSERVrecv","");
  return builtinUDPS.parseRead("UDPSERVrecv");
}

void UdpServer::waiter()
{
  builtinUDPS.waiting();
}

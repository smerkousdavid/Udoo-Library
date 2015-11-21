#include "Arduino.h"
#include "Udoo.h"

Udoo builtinUDP
#define wait UdpClient::waiter

void UdpClient::connect(String ip, int port)
{
  builtinUDP.writeLine("Udpstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void UdpClient::send(String toSend)
{
  builtinUDP.writeLine("Udpsend", toSend);
  wait();
}

String UdpClient::recv()
{
  builtinUDP.writeLine("Udprecv","");
  return builtinUDP.readLine();
}

void UdpClient::close()
{
  builtinUDP.writeLine("Udpclose","");
  wait();
}

void UdpClient::waiter()
{
  builtinUDP.waiting();
}

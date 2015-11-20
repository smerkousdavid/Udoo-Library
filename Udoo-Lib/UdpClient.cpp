#include "Arduino.h"
#include "Udoo.h"

Udoo builtin;
#define wait UdpClient::waiter

void UdpClient::connect(String ip, int port)
{
  builtin.writeLine("Udpstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void UdpClient::send(String toSend)
{
  builtin.writeLine("Udpsend", toSend);
  wait();
}

String UdpClient::recv()
{
  builtin.writeLine("Udprecv","");
  return builtin.readLine();
}

void UdpClient::close()
{
  builtin.writeLine("Udpclose","");
  wait();
}

void UdpClient::waiter()
{
  builtin.waiting();
}

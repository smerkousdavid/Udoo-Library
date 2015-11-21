#include "Arduino.h"
#include "Udoo.h"

Udoo builtinTCP;
#define wait TcpClient::waiter

void TcpClient::connect(String ip, int port)
{
  builtinTCP.parseWrite("TCPstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void TcpClient::send(String toSend)
{
  builtinTCP.parseWrite("TCPsend", toSend);
  wait();
}

String TcpClient::recv()
{
  builtinTCP.parseWrite("TCPrecv","");
  return builtinTCP.parseRead("TCPrecv");
}

void TcpClient::close()
{
  builtinTCP.parseWrite("TCPclose","");
  wait();
}

void TcpClient::waiter()
{
  builtinTCP.waiting();
}

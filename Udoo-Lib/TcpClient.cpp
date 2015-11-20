#include "Arduino.h"
#include "Udoo.h"

Udoo builtin;
#define wait TcpClient::waiter

void TcpClient::connect(String ip, int port)
{
  builtin.writeLine("TCPstart",ip+"<%=PORT=%>"+String(port));
  wait();
}

void TcpClient::send(String toSend)
{
  builtin.writeLine("TCPsend", toSend);
  wait();
}

String TcpClient::recv()
{
  builtin.writeLine("TCPrecv","");
  return builtin.readLine();
}

void TcpClient::close()
{
  builtin.writeLine("TCPclose","");
  wait();
}

void TcpClient::waiter()
{
  builtin.waiting();
}
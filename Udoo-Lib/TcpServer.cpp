#include "Arduino.h"
#include "Udoo.h"

Udoo builtinTCPS;
#define wait TcpServer::waiter

void TcpServer::start(int port)
{
  builtinTCPS.parseWrite("TCPSERVstart",String(port));
  wait();
}

void TcpServer::stop()
{
  builtinTCPS.parseWrite("TCPSERVstop","");
  wait();
}

void TcpServer::clientWait(int waitnum)
{
  while(builtinTCPS.parseRead("CLIENT").indexOf("CLIENT") == -1);
  delay(1);
  delay(waitnum);
}

void TcpServer::send(String toSend)
{
  builtinTCPS.parseWrite("TCPSERVsend", toSend);
  wait();
}

String TcpServer::recv()
{
  builtinTCPS.parseWrite("TCPSERVrecv","");
  return builtinTCPS.parseRead("TCPSERVrecv");
}

void TcpServer::close()
{
  builtinTCPS.parseWrite("TCPSERVclose","");
  wait();
}

void TcpServer::waiter()
{
  builtinTCPS.waiting();
}

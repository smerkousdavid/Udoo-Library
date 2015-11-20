/*
 Udoo Libaray Created by David Smerkous, This library was made so that you wouldn't have
to mess with all the Serial communication on the Sam and Imx6 side
*/

#ifndef Udoo_h
#define Udoo_h

#include "Arduino.h"

class Udoo
{
	public:
	void test();
	void init();
	void stop();
	void tcpClient(String ip, int port);
	void udpClient(String uip, int uport);
	void clientSend(String message);
	void clientSendUdp(String messageu);
	void linuxCommand(String command);
	String getIp();
	void tcpServer(int port);
	void waitForClient();
	void udpServer(int port);
	String clientRecv();
	String clientRecvUdp();
	void sendToClient(String toSend);
	void sendToClientUdp(String ip, String toSend);
	String udpGetClientIp();
	String recvFromClient();
	String recvFromClientUdp();
	void closeTheClient();
	void tcpClose();
	void debug(String mess);
	String readLine(void);
	void writeLine(String context, String toSend);
	void waiting();
	private:
	int _baud;
	void ready();
};

class TcpClient
{
	public:
	void connect(String ip, int port);
	void send(String toSend);
	String recv();
	void close();
	private:
	void waiter();
};

class UdpClient
{
	public:
	void connect(String ip, int port);
	void send(String toSend);
	String recv();
	void close();
	private:
	void waiter();
};


#endif

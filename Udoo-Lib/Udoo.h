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
	void init();
	void stop();
	void linuxCommand(String command);
	String getIp();
	void debug(String mess);
	String readLine();
	void parseWrite(String context, String toSend);
	String parseRead(String context);
	void waiting();
	private:
	int _baud;
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

class TcpServer
{
	public:
	void start(int port);
	void clientWait(int wait);
	void send(String toSend);
	String recv();
	void close();
	void stop();
	private:
	void waiter();
};

class UdpClient
{
	public:
	void connect(String ip, int port);
	void send(String toSend);
	String recv();
	private:
	void waiter();
};

class UdpServer
{
	public:
	void start(int port);
	void send(String toSend);
	void stop();
	String recv();
	private:
	void waiter();
};

class Storage
{
	public:
	String readFile(String directory);
	void writeFile(String directory, String toWrite);
	void appendTo(String directory, String toWrite);
	String readLine(String directory, int line);
	private:
	void waiter();
};

class Usb
{
	public:
	String read();
	void write(String toWrite);
	void start(String port, int bit);
	void stop();
	private:
	void waiter();
};

#endif

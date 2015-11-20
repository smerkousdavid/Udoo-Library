/* this is the core file which you shouldn't really mess with*/

#include "Arduino.h"
#include "Udoo.h"

String readString;
String defend = "<%=EOF=%>";

#define line Udoo::readLine
void Udoo::init()
{
	Serial.begin(115200);
	while(line() != "<%=OK=%>OK<%=EOF=%>");
	Serial.println("<%=OK=%>OK<%=EOF=%>");
	delay(500);
}
#undef line

#define ok Udoo::ready
void Udoo::stop()
{
	Serial.println("%=%END%=%");
	ok();
	delay(100);
	Serial.end();
}
#undef ok

#define ok Udoo::ready
void Udoo::tcpServer(int port)
{
	while(Serial.available());
	Serial.println("TCPS:"+String(port)+"%E%");
	ok();
}
#undef ok 

#define ok Udoo::ready
void Udoo::tcpClient(String ip, int port)
{
	while(Serial.available());
	Serial.println("TCPC:"+ip+"%PORT%"+String(port)+"%E%");
	ok();
}
#undef ok 

#define ok Udoo::ready
void Udoo::linuxCommand(String command)
{
	while(Serial.available());
	Serial.println("%=CUSCOM=%" + command +"%=E=%");
	ok();
}
#undef ok 

#define line Udoo::readLine
String Udoo::getIp()
{
	while(Serial.available());
	Serial.println("%=GETIP=%");
	return line();
}
#undef line

#define ok Udoo::ready
void Udoo::udpClient(String uip, int uport)
{
	while(Serial.available());
	Serial.println("UDPC:"+uip+"%PORT%"+String(uport)+"%E%");
	ok();
}
#undef ok 

#define ok Udoo::ready
void Udoo::sendToClient(String toSend)
{
	while(Serial.available());
	Serial.println("%=SSSEND=%"+toSend+"%=E=%");
	ok();
}
#undef ok

/*
#define ok Udoo::ready
void Udoo::sendToClientUdp(String ip, String toSend)
{
	while(Serial.available());
	Serial.println("%=USSEND=%"+ip+"%=MES=%"+toSend+"%=E=%");
	ok();
}
#undef ok
*/

#define line Udoo::readLine
String Udoo::recvFromClientUdp()
{
	while(Serial.available());
	Serial.println("%=USREC=%");
	return line();
}
#undef line

#define ok Udoo::ready
void Udoo::closeTheClient()
{
	while(Serial.available());
	Serial.println("%=DISCLIENT=%");
	ok();
}
#undef ok

#define line Udoo::readLine
String Udoo::recvFromClient()
{
	while(Serial.available());
	Serial.println("%=SSREC=%");
	//Serial.println("DEB:THERE WAS AN INTERNAL ERROR%=E=%");
	return line();
}
#undef line

#define ok Udoo::ready
void Udoo::waitForClient()
{
	ok();
}
#undef ok

#define ok Udoo::ready
void Udoo::udpServer(int uport)
{
	while(Serial.available());
	Serial.println("UDPS:"+String(uport)+"%E%");
	ok();
}
#undef ok 

#define ok Udoo::ready
void Udoo::clientSend(String message)
{
	while(Serial.available());
	Serial.println("CSD:"+message+"%=E=%");
	ok();
}
#undef ok 

#define ok Udoo::ready
void Udoo::sendToClientUdp(String ip, String toSend)
{
	while(Serial.available());
	Serial.println("%=USSEND=%"+ip+"%=MES=%"+toSend+"%=E=%");
	ok();
}
#undef ok

#define line Udoo::readLine
String Udoo::clientRecv()
{
	while(Serial.available());
	Serial.println("%=REC=%");
	delay(100);
	return line();
}
#undef line

#define line Udoo::readLine
String Udoo::clientRecvUdp()
{
	while(Serial.available());
	Serial.println("%=RECU=%");
	delay(100);
	return line();
}
#undef line

#define ok Udoo::ready
void Udoo::tcpClose()
{
	while(Serial.available());
	Serial.println("%=Close=%");
	ok();
}
#undef ok

#define line Udoo::readLine
String Udoo::udpGetClientIp()
{
	while(Serial.available());
	Serial.println("%=GETUDP=%");
	return line();
}
#undef line

void Udoo::debug(String message)
{
	while(Serial.available());
	Udoo::writeLine("DEBUG",message);
}

#define ok Udoo::ready
void Udoo::test()
{
	Serial.println("Test");
	ok();
}
#undef ok

#define line Udoo::readLine
void Udoo::ready()
{
	while(line().indexOf("K") == -1);	
	//delay(100);
	//Serial.println("DEB:THERE WAS AN INTERNAL ERROR%=E=%");
	delay(300);
}
#undef line

#define line Udoo::readLine
void Udoo::waiting()
{
	line();
}
#undef line

void Udoo::writeLine(String context, String toSend)
{
	Serial.println("<%="+context+"=%>"+toSend+defend);
}

String Udoo::readLine(void)
{
	while (!(Serial.available()));
	while(Serial.available())
	{
		delay(3);
		if(Serial.available() > 0)
		{
			char one = Serial.read();
			readString += (String)one;
		}
	}
	if(!Serial.available()&&readString.length() > 0)
	{
		String fin = (String)readString;
		readString="";
		return fin;
	}
	return "";
}

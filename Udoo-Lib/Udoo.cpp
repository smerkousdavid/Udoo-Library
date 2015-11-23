/* this is the core file which you shouldn't really mess with*/

#include "Arduino.h"
#include "Udoo.h"

String readString;
String defend = "<%=EOF=%>";

#define line Udoo::readLine
#define ready Udoo::waiting
#define reader Udoo::parseRead
#define writer Udoo::parseWrite

void Udoo::init()
{
	Serial.begin(115200);
	while(line().indexOf("OK") == -1);
	writer("OK","OK");
	delay(5);
}

void Udoo::stop()
{
	writer("END","");
	ready();
	delay(10);
	Serial.end();
}

void Udoo::linuxCommand(String command)
{
	writer("LINUX",command);
	ready();
}

String Udoo::getIp()
{
	writer("GETIP","");
	return reader("GETIP");
}

void Udoo::debug(String message)
{
	message.replace("\n","\\n");
	writer("DEBUG", message);
	ready();
}

void Udoo::waiting()
{
	while(line().indexOf("OK") == -1);
	delay(3);
}

String Udoo::parseRead(String context)
{
	String lines = line();
	if(lines.indexOf("<%="+context+"=%>") == -1) {return "";}
	return lines.substring(lines.indexOf("<%="+context+"=%>")+String("<%="+context+"=%>").length(),lines.indexOf(defend));
}

void Udoo::parseWrite(String context, String toSend)
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

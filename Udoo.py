#!/usr/bin/env python
__author__ = 'David'

from serial import Serial
from time import sleep
from socket import socket, AF_INET, SOCK_STREAM, SOCK_DGRAM, gethostbyname, gethostname
from subprocess import Popen, PIPE, STDOUT
from threading import Thread
from sys import argv, exit

'''VARS'''
defend = "<%=EOF=%>"

#CLIENT TCP
tsock = None
useTCP = False
TCPip = None
TCPport = None
TCon = False
#END

#CLIENT UDP
usock = None
useUDP = False
UDPip = None
UDPport = None
#END

ser = Serial("/dev/ttymxc3", 115200)

def find(full, finds):
    if full.find(finds) != -1:
        return True
    return False

def fFind(full, finds):
    if str("<%="+finds+"=%>") in full:
        return True
    return False
    	
def sub(full, starter, ender):
    return full[full.index("<%="+starter+"=%>")+(len("<%="+starter+"=%>")):full.index(ender)]

def readLine():
    return ser.readline()

def ready():
    writeLine("OKOKOK")

def writeLine(towrite):
    ser.write(towrite)

def customCommand(command):
    print Popen(command, shell=True, stdout=PIPE, stderr=STDOUT).communicate()[0]

def parseSend(type, toSend):
    global defend
    writeLine("<%="+type+"=%>"+toSend+defend)

def parseRec(type):
    global defend
    return sub(readLine(), type, defend)

def there():
    parseSend("OK", "OK")
    get = parseRec("OK")
    if find(get, "OK"):
        print "Found the SAM3x\n"
    else:
        print "Failed to find the SAM3x\nMake sure you put\nudoo.init()\nIn your arduino code\n Or reset device" \
        + "\nContinuing, this will use Serial line..."

########TCP CLIENT###############
def TCPstart(full):
    global TCPip, TCPport, useTCP, tsock, defend
    TCPip = str(sub(full, "TCPstart", "<%=PORT=%>"))
    TCPport = int(sub(full, "PORT", defend))
    print "The TCPsocket IP is " + TCPip + " and the port " + str(TCPport)
    useTCP = True
    called = True
    ready()

def TCPsend(toSend):
    global useTCP, TCPip, TCPport, TCon, tsock
    sending = str(toSend)
    if useTCP:
        print "Sending TCP packet: %s" % sending
        if not TCon:
            tsock = socket(AF_INET, SOCK_STREAM)
            tsock.connect((TCPip, TCPport))
            TCon = True
        tsock.send(sending)
    ready()

def TCPrecv():
    global useTCP, TCPip, TCPport, TCon, tsock
    if useTCP:
        print "Waiting for packet..."
        if not TCon:
            tsock = socket(AF_INET, SOCK_STREAM)
            tsock.connect((TCPip, TCPport))
            TCon = True
        recv = str(tsock.recv(1024))
        print "Got: %s" % recv
        writeLine(recv)
        #parseSend("TCPgot",recv)

def TCPclose():
    global tsock, TCon
    if TCon:
        print "Closing TCP client"
        tsock.close()
        TCon = False
    ready()
########END TCP CLIENT###############

########UDP CLIENT###############
def UDPstart(full):
    global UDPip, UDPport, useUDP, usock
    UDPip = str(sub(full, "UDPstart", "<%=PORT=%>"))
    UDPport = int(sub(full, "PORT", defend))
    print "The UDPsocket IP is " + UDPip + " and the port " + str(UDPport)
    useUDP = True
    called = True
    ready()

def UDPsend(toSend):
    global useUDP, UDPip, UDPport, usock
    sending = str(toSend)
    if useUDP:
    	print "Sending UDP packet: %s" % sending
    	usock = socket(AF_INET, SOCK_DGRAM)
    	usock.sendto(MESSAGE, (UDPip, UDPport))
    ready()

def UDPrecv():
    global useTCP, TCPip, TCPport, TCon, tsock
    if useTCP:
        print "Waiting for packet..."
        if not TCon:
            tsock = socket(AF_INET, SOCK_STREAM)
            tsock.connect((TCPip, TCPport))
            TCon = True
        recv = str(tsock.recv(1024))
        print "Got %s" % recv
        parseSend("TCPgot",recv)
	tsock.close()
########END UDP CLIENT###############


def val():
    global defend
    recv = str(readLine())
    if not find(recv, defend):
        return None
    
    ######TCP CLIENT
    if fFind(recv, "TCPsend"):
        TCPsend(sub(recv, "TCPsend", defend))
        
    if fFind(recv, "TCPclose"):
        TCPclose()
    
    if fFind(recv, "TCPstart"):
        TCPstart(recv)

    if fFind(recv, "TCPrecv"):
    	TCPrecv()
    	
    if fFind(recv, "DEBUG"):
    	print "Debug: %s" % str(sub(recv, "DEBUG", defend))
   
    ######END OF TCP CLIENT
    

def main():
    print "Welcome to the Udoo Libray by David Smerkous\nThis is the debug console, Taking care of everything for you" \
    + "\n\nSearching for the Sam3x (Arduino part)"
    there()
    print "\nWaiting for command...\n\n"
    while True:
        val()

def onExit():
    ser.close()

if __name__ == "__main__":
    try:
        main()
    finally:
        onExit()

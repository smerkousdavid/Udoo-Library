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

#SERVER TCP
SERVERTHREAD = None
useTCPserver = False
TCPSERVport = None
TCPsend = False
TCPrecv = False
TCPclose = False
TCPval = None

#CLIENT UDP
usock = socket(AF_INET, SOCK_DGRAM)
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
        #writeLine(recv)
        parseSend("TCPrecv",recv)

def TCPclose():
    global tsock, TCon
    if TCon:
        print "Closing TCP client"
        tsock.close()
        TCon = False
    ready()
########END TCP CLIENT###############

############TCP SERVER###############
def TCPserver():
    global useTCPserver, TCPSERVport, TCPsend, TCPrecv, TCPclose, TCPval
    tserv = socket(AF_INET, SOCK_STREAM)
    tserv.bind(('',TCPSERVport)
    print "Started TCP Server on port %d" % TCPSERVport
    closed = True
    while useTCPserver:
        print "\nWaiting for connection with client...\n"
        conn, addr = tserv.accept()
        print "Got client at %s" % str(addr[0])
        ready()
        closed = False
        while not TCPsend or TCPrecv or TCPclose:
            sleep(0.05)
            while not closed:
                if TCPsend:
                    print "Sending to client"
                    conn.send(TCPval)
                    ready()
                    TCPsend = False
                    TCPval = ""
                if TCPrecv:
                    print "Waiting for input"
                    got = conn.recv(1024)
                    print "Got from client %s" % str(got)
                    parseSend("TCPSERVrecv",str(got))
                    TCPrecv = False
                if TCPclose:
                    print "Closing the client"
                    conn.close()
                    ready()
                    TCPclose = False
                    closed = True
            closed = False
            print "Closed..."
    tserv.close()
#################END TCP SERVER####################    
    


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
    	usock.sendto(sending, (UDPip, UDPport))
    ready()

def UDPrecv():
    global useUDP, UDPip, UDPport, usock
    if useUDP:
        print "Waiting for packet..."
        recv = str(usock.recvfrom(1024)[0])
        print "Got %s" % recv
        parseSend("UDPrecv",recv)
########END UDP CLIENT###############


def val():
    global defend, useTCPserver, TCPSERVport, TCPsend, TCPrecv, TCPclose, TCPval 
    recv = str(readLine())
    if not find(recv, defend):
        return None
        
    ######TCP CLIENT#######
    if fFind(recv, "TCPsend"):
        TCPsend(sub(recv, "TCPsend", defend))
        
    if fFind(recv, "TCPclose"):
        TCPclose()
    
    if fFind(recv, "TCPstart"):
        TCPstart(recv)

    if fFind(recv, "TCPrecv"):
    	TCPrecv()
    #####END TCP CLIENT#####
    
    ######TCP SERVER#######
    if fFind(recv, "TCPSERVsend"):
        TCPval = sub(recv,"TCPSERVsend",defend)
        TCPsend = True
        
    if fFind(recv, "TCPSERVclose"):
        TCPclose = True
    
    if fFind(recv, "TCPSERVstop"):
        useTCPserver = False
    
    if fFind(recv, "TCPSERVstart"):
        useTCPserver = True
        TCPSERVport = int(str(sub(recv,"TCPSERVstart",defend)))
        SERVERTHREAD = Thread(target=TCPserver)
        SERVERTHREAD.start()
    
    if fFind(recv, "TCPSERVrecv"):
    	TCPrecv = True
    #####END TCP SERVER#####
    
    ######UDP CLIENT#######
    if fFind(recv, "UDPsend"):
        UDPsend(sub(recv, "UDPsend", defend))
    
    if fFind(recv, "UDPstart"):
        UDPstart(recv)

    if fFind(recv, "UDPrecv"):
    	UDPrecv()
    #####END TCP CLIENT#####
    
    if fFind(recv, "DEBUG"):
    	print "Debug: %s" % str(sub(recv, "DEBUG", defend))
    

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

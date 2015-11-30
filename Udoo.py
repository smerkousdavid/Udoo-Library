#!/usr/bin/env python
__author__ = 'David'

from serial import Serial
from time import sleep
from socket import socket, AF_INET, SOCK_STREAM, SOCK_DGRAM, gethostbyname, gethostname, SOL_SOCKET, SO_REUSEADDR, gethostbyname_ex
from subprocess import Popen, PIPE, STDOUT
from threading import Thread
from sys import argv, exit

'''VARS'''
#Global
defend = "<%=EOF=%>"

#USB
usb = None
#End USB

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
TCPval = "N/A" #None crashes it
#END

#SERVER UDP
SERVERTHREADUDP = None
useUDPserver = False
UDPSERVport = None
UDPsend = False
UDPrecv = False
UDPval = "N/A" #None crashes it
#END

#CLIENT UDP
usock = socket(AF_INET, SOCK_DGRAM)
useUDP = False
UDPip = None
UDPport = None
#END

try:
    ser = Serial("/dev/ttymxc3", 115200) #For udoo dual or quad
except:
    ser = Serial("/dev/ttyMCC", 115200) #For udoo neo

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
    try:
        parseSend("OK", "OK")
        get = parseRec("OK")
        if find(get, "OK"):
            print "Found the SAM3x\n"
    except:
        print "Failed to find the SAM3x\nMake sure you put\nudoo.init()\nIn your arduino code\n Or reset device" \
        + "\nContinuing, this will use Serial line..."

#####USB######
def serialStart(port, bitrate):
    global usb
    usb = Serial(port, bitrate)
    ready()

def serialWrite(toWrite):
    global usb
    usb.write(str(toWrite))
    ready()

def serialRead():
    global usb
    parseSend("SERIALread", str(usb.readline()))

def serialStop():
    global usb
    usb.close()
    ready()
####END USB####

######STORAGE#######
def readFile(directory):
    print "Reading from %s" % str(directory)
    with open(directory, "r") as read:
        toRet = read.read()
    parseSend("PULLfile",str(toRet).replace("\n","\\n"))
    read.close()

def writeFile(directory, toWrite):
    print "Writing to %s" % str(directory)
    with open(directory, "w") as write:
        write.write(str(toWrite).replace("\\n","\n"))
    write.close()
    ready()
    
def appendLine(directory, toAppend):
    print "Appending to %s" % str(directory)
    with open(directory, "a+") as append:
        append.write(str(toAppend).replace("\\n","\n"))
    append.close()
    ready()
    
def readFileLine(directory, lines):
    print "Pulling line: " +str(lines)+ " from %s" % str(directory)
    with open(directory, "r") as line:
        toRet = line.read().splitlines()[int(lines)].replace("\n","")
    line.close()
    parseSend("PULLline", toRet)
#####END STORAGE####


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
    tserv.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    tserv.bind(('',TCPSERVport))
    print "Started TCP Server on port %d" % (TCPSERVport)
    tserv.listen(1)
    closed = True
    TCPsend = False
    TCPclose = False
    TCPval = "N/A"
    TCPrecv = False
    while useTCPserver:
        print "\nWaiting for connection with client...\n"
        conn, addr = tserv.accept()
        print "Got client at %s" % str(addr[0])
        parseSend("CLIENT","CLIENTCON")
        closed = False
        while not TCPsend and not TCPrecv and not TCPclose:
            sleep(0.01)
        while not closed:
            if TCPsend:
                print "Sending to client"
                conn.sendall(TCPval)
                ready()
                TCPsend = False
                TCPval = ""
            if TCPrecv:
                print "Waiting for input"
                got = conn.recv(1024)
                print "Got from client %s" % str(got)
                TCPrecv = False
                parseSend("TCPSERVrecv",str(got))
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
    
############UDP SERVER###############
def UDPserver():
    global useUDPserver, UDPSERVport, UDPsend, UDPrecv, UDPval
    userv = socket(AF_INET, SOCK_DGRAM)
    userv.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    userv.bind(("",UDPSERVport))
    print "Started UDP Server on port %d" % (UDPSERVport)
    RECV = False
    UDPsend = False
    UDPval = "N/A"
    UDPrecv = False
    ready()
    while useUDPserver:
        while not UDPsend and not UDPrecv:
            sleep(0.001)
        if UDPsend and RECV:
            print "Sending to client"
            userv.sendto(UDPval, addr)
            ready()
            UDPsend = False
            UDPval = ""
        if UDPrecv:
            print "Waiting for input"
            data, addr = userv.recvfrom(1024)
            print "Got from client %s" % str(data)
            UDPrecv = False
            parseSend("UDPSERVrecv",str(data))
            RECV = True
        print "Closed..."
    userv.close()
#################END UDP SERVER####################    

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
    global defend, useTCPserver, TCPSERVport, TCPsend, TCPrecv, TCPclose, TCPval, useUDPserver, UDPSERVport, UDPsend, UDPrecv, UDPclose, UDPval  
    recv = str(readLine())
    if not find(recv, defend):
        return None
        
    #####STORAGE######
    if fFind(recv, "READfile"):
        readFile(str(sub(recv, "READfile", defend)))
    
    if fFind(recv, "WRITEfile"):
        direct = str(sub(recv,"WRITEfile","<%=TOWRITE=%>"))
        toWrite = str(sub(recv,"TOWRITE", defend))
        writeFile(direct, toWrite)
    
    if fFind(recv, "APPENDfile"):
        direct = str(sub(recv,"APPENDfile","<%=TOWRITE=%>"))
        toWrite = str(sub(recv,"TOWRITE", defend))
        appendLine(direct, toWrite)
    
    if fFind(recv, "READline"):
        direct = str(sub(recv,"READline","<%=LINES=%>"))
        lines = str(sub(recv,"LINES", defend))
        readFileLine(direct, int(lines))
    ###END STORAGE###
    
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
        TCPval = str(sub(recv, "TCPSERVsend", defend))
        sleep(0.07) #Make sure loop has finished
        TCPsend = True
        
    if fFind(recv, "TCPSERVclose"):
        TCPclose = True
    
    if fFind(recv, "TCPSERVstop"):
        useTCPserver = False
        ready()
    
    if fFind(recv, "TCPSERVstart"):
        useTCPserver = True
        TCPSERVport = int(str(sub(recv,"TCPSERVstart",defend)))
        SERVERTHREAD = Thread(target=TCPserver)
        SERVERTHREAD.start()
        sleep(0.5)
        ready()
    
    if fFind(recv, "TCPSERVrecv"):
    	TCPrecv = True
    #####END TCP SERVER#####
    
    ######UDP SERVER#######
    if fFind(recv, "UDPSERVsend"):
        UDPval = str(sub(recv, "UDPSERVsend", defend))
        sleep(0.07) #Make sure loop has finished
        UDPsend = True
    
    if fFind(recv, "UDPSERVstop"):
        useUDPserver = False
        ready()
    
    if fFind(recv, "UDPSERVstart"):
        useUDPserver = True
        UDPSERVport = int(str(sub(recv,"UDPSERVstart",defend)))
        SERVERTHREADUDP = Thread(target=UDPserver)
        SERVERTHREADUDP.start()
    
    if fFind(recv, "UDPSERVrecv"):
    	UDPrecv = True
    #####END UDP SERVER#####
    
    ######UDP CLIENT#######
    if fFind(recv, "UDPsend"):
        UDPsend(sub(recv, "UDPsend", defend))
    
    if fFind(recv, "UDPstart"):
        UDPstart(recv)

    if fFind(recv, "UDPrecv"):
    	UDPrecv()
    #####END TCP CLIENT#####
    
    ######USB########
    if fFind(recv, "SERIALstart"):
        serialStart(str(sub(recv, "SERIALstart", "<%=BIT=%>")), int(str(sub(recv,"BIT",defend))))
    
    if fFind(recv, "SERIALstop"):
        serialStop()
    
    if fFind(recv, "SERIALwrite"):
        serialWrite(str(sub(recv, "SERIALwrite", defend)))
    
    if fFind(recv, "SERIALread"):
        serialRead()
    ####END USB#####
    
    if fFind(recv, "DEBUG"):
    	print "Debug: %s" % str(sub(recv, "DEBUG", defend)).replace("\\n","\n")
    	ready()
    	
    if fFind(recv, "GETIP"):
        IP = ([l for l in ([ip for ip in gethostbyname_ex(gethostname())[2] if not ip.startswith("127.")][:1], [[(s.connect(('8.8.8.8', 80)), s.getsockname()[0], s.close()) for s in [socket(AF_INET, SOCK_DGRAM)]][0][1]]) if l][0][0]) #Got this snippet online
        parseSend("GETIP", str(IP))
        print "Current device IP: %s" % str(IP)
        
    if fFind(recv, "LINUX"):
        Thread(target=customCommand,args=[sub(recv, "LINUX", defend)]).start()
    

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

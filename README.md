# Udoo-Library 

The ultimate Udoo library that allows you to use the linux side as a library, just like a shield for the Sam3x!

###Note
For the Udoo neo to work install serial, the dual/quad should already have this

       sudo apt-get install python-serial

###What is it?
To start off if you were/are like me, I started off thinking the Udoo was this awesome thing that I could easily access the Linux side with a library, yet I got disappointed because I had to handle the Serial comm and It got really annoying, the more I messed around with it the more i felt like the Udoo was 2 micro-controllers/processors drifting apart, So I tried looked online and didn't find anything, for a library that handled the serial line. Then I decided to make one! 

###Now?
I have created a library for the Udoo that allows the Use of the multi threaded Imx6 to work with the single threaded Sam3x, Imagine the Linux side communications as a Library that just gets slapped on into Arduino IDE!! That's exactly what this is All you have to do is run a python script on one side, and the Serial comm/Networking/Storage/Audio Threads are handled for you, well on the other side there are many functions to call those threads on the Linux side. Which are simple to use for anyone.

###How to use it?
Download the zip on the GitHub repo. The Linux folder gets placed on your desktop, and... and.. that's pretty much it, just install pyserial if not already installed on the new OS for Udoo

The Udoo-Lib will go into the arduino libraries folder (I believe /home/ubuntu/Arduino/libraries/) or (/usr/share/arduino/libraries/)

Like so:

       sudo cp -r ~/Desktop/Udoo-Library-master/Udoo-Lib /usr/share/arduino/libraries/

If you don't know what to do

Here: 1. Open Arduino 

2. Go to file -> examples 

3. Select an example that you'll need 

4. Modify the Code 

5. If using tcp or udp make sure you have a server/client running on separate device 

6. Upload the Arduino sketch 

7. wait until the Sam resets, 

8. Grab a female to female jumper cable and use it as a switch to reset the Sam3x manually that is located next to the J16 slot, place one end into the male then to reset quickly insert into the other J16 port (male), then unplug one side to reset the Sam 

9. Run the Python Udoo.py sketch 

10. If: it found the Sam and there weren't any errors, then your good to go 

11. else: Reset (Sam3x) using jumper cables

12. still: contact me

###Help?
Since I just wrote this library in a couple of days, I need your guys help to fix it up and make it more efficient contact me through Gmail: smerkousdavid@gmail.com (best)

###Commands?
Look farther down for examples

Here are the base for the below commands <Return> <name(<Input>)>



#####Udoo Class:

       void init(void);       //MUST be called, this tells the Linux side script to start, practically put this anywhere you want, but must be before any other Udoo commands
       void stop(void);     //Stops Serial line so you can use it, but remember to call Serial.begin() after stop if you want to use the Serial line
       void debug(String text);    //Here is a substitute for debugging, since Serial line is used, you must use this command to print to Script console
       String getIp(void);     //Returns the current Ip of the udoo
       void linuxCommand(String command);     //Runs a terminal command on linux

#####TcpClient Class:

       void connect(String ip, int port);     //Tell the script to connect to a TCP server using the ip and port plugged in, only need to call this once
       void send(String text);      //Sends a whole line to the server
       String recv(void);     //Receive a full line from the server
       void close(void);     //Closes the Tcp connection 

#####TcpServer Class:

       void start(int port);      //Starts a Tcp Server on port
       void stop(void);      //Stops the Tcp Server
       void clientWait(int delay);      //Call this before a connection with client and insert delay time afterwards, I would put 10 milliseconds what worked best for me 
       void send(String message);     //Send a full line to the Client
       String recv(void);     //Receive a full line from the Client
       void close(void);      // Close the client connection

#####UdpClient Class:

       void connect(String ip, int port);       //Tell the script to connect to a UDP server using the ip and port plugged in, only need to call this once
       void send(String text);      //Sends a whole line to the server
       String recv(void);       //Receive a full line from the server

#####UdpServer Class:

       void start(int port);       //Starts a Udp Server on port
       void stop(void);       //Stops the Udp Server
       void send(String message);       //Send a full line to the Client
       String recv(void);       //Receive a full line from the Client

#####Storage Class:

       String readFile(String directory);       //Reads any file turns it into a string and includes newlines
       void writeFile(String directory, String toWrite);       //Creates/Overwrites a file on the Linux side with some initial text/image stuff
       void appendTo(String directory, String toWrite);      //Without overwriting, this function will add to the file
       String readLine(String directory, int lineNum);        //Retrieve a specific line from the file starts at 0

#####Usb Class:

       void start(String port, int bitrate);       //Starts a serial line with a Usb device on the Linux side
       void write(String toWrite);       //Writes a full line to the Serial line
       String read(String directory, String toWrite);        //Reads and returns a full line from the Serial line
       void stop(void);       //Stops that Serial line

# Udoo-Library 

The ultimate Udoo library that allows you to use the linux side as a library, just like a shield for the Sam3x!

###What is it?
To start off if you were/are like me, I started off thinking the Udoo was this awesome thing that I could easily access the Linux side with a library, yet I got disappointed because I had to handle the Serial comm and It got really annoying, the more I messed around with it the more i felt like the Udoo was 2 micro-controllers/processors drifting apart So I looked online and didn't find anything,

###Now?
But Now I have created a library for the udoo that allows the Use of the multi threaded Imx6 to work with the single threaded Sam3x, Imagine the Linux side communications as a Library that just gets slapped on into arduino IDE!! That's exaclty what this is All you have to do is run a python script on one side, and the Serial comm/Networking Threads are handled for you, well on the other side there are many functions to call those threads on the linux side

###How to use it?
The Linux folder gets placed on your desktop, and... and.. that's pretty much it, just install pyserial if not already installed on the new OS for Udoo

The Udoo-Lib will go into the arduino libraries folder (I believe /home/ubuntu/Arduino/libraries/)

If you don't know what to do

Here: 1. Open arduino 

2. go to file -> examples 

3. Select an example that you'll need 

4. Modify the Code 

5. If using tcp or udp make sure you have a server/client running on separate device 

6. Upload the Arduino sketch 

7. wait until the Sam resets, 

8. grab a female to female jumper cable and use it as a switch to reset the Sam3x manually that is located next to the J16 slot, place one end into the male then to reset quickly insert into the other J16 port to then release to reset the Sam 

9. Run the Python Udoo.py sketch 

10. If it found the Sam and there weren't any errors, then your good to go 

11. else: Reset (Sam3x) using jumper cables still: contact me

###Help?
Since I just write this library in a day I need your guys help to fix it up and make it more effiecent Contact me through github or gmail smerkousdavid@gmail.com (best)



###Commands?
Look farther down for examples

Here are the base for the below commands <Return> <name(<Input>)>

WORKING ON IT
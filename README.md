# GSM_sim900A_Arduino
Sending Data To Web Server Using GSM sim900A module and Arduino
Working of the Project :

After the Arduino is connected to the PC, and after verifying and uploading the code, we have to enter the data from the 4 X 4 matrix keypad. After entering we have to click on D button for “OK”. This initializes the GPRS and then sends the data to the ThingSpeak web server. There the graph is plotted according to the data and the gauge widget shows the present humidity percentage in the particular area.

The data can be exported into csv file or xls format for further inspection of data or study.



Result:

In the following result being shown below, humidity of 24.5 % is being typed from the keypad and button D is clicked to send the data.

After it is sent, the AT commands start and the GSM module responds to the commands respectively. The response for AT commands can be seen in the serial monitor.

After the data is sent successfully the ThingSpeak server, we can visit the channel through the following URL : https://thingspeak.com/channels/761938 

In the channel, we can see the graph plotted for values of humidity percentage vs time with a line graph. We can also see the gauge widget which shows the present humidity percentage . This pictorial representation makes it user-friendly for the user.


AT Commands
![alt tag](https://github.com/bansuri0100/GSM_sim900A_Arduino/blob/master/sketch_apr20a/screenshots/AT.PNG)
Hardware 
![alt tag](https://github.com/bansuri0100/GSM_sim900A_Arduino/blob/master/sketch_apr20a/screenshots/hardware.PNG)


# ESP-Arduino-Distance-Sensor
Title: Uploading Distance Data from an IR Sharp Sensor to ThingSpeak Using ESP32 and Arduino: A Step-by-Step Guide

Introduction:
In this step-by-step guide, we will explore how to retrieve distance data from a Sharp GP2Y0A21YK0F Analog Distance Sensor using an ESP32 board. We will then establish communication with an Arduino board to obtain the distance data upon receiving a request from the ESP32. Finally, we will display the data on an LCD screen and upload it to ThingSpeak, an IoT platform.

Equipment Needed:
To get started, gather the following components:

1. ESP32 board
2. Arduino UNO board
3. Sharp GP2Y0A21YK0F Analog Distance Sensor
4. Push button switch
5. LED 16x2
6. IIC interface for the LCD
7. Male-to-male jumper wires
8. Female-to-male jumper wires
9. Box (for housing)
10. Vero board

Procedure:

1. Connect the Sharp GP2Y0A21YK0F Analog Distance Sensor:
Begin by connecting the Sharp sensor to the ESP32 board. Ensure the appropriate voltage and ground connections are made, and connect the sensor's output pin to an analog input pin (pin A0) on the Arduino.

2. Setup the Button and LCD with ESP32:
Connect the one end of push button switch to ground and the other to pin 15 on the ESP32, this makes the switch a pull up swicth. Solder the LCD to the IIC interface, making the necessary connections for power and data. Connect the LED 16x2 module (now soldered to the IIC) to the ESP32 board. Use the appropriate digital pins for button input and LED output.
Follow this tutorial to understand the LCD-ESP connections
https://randomnerdtutorials.com/esp32-esp8266-i2c-lcd-arduino-ide/

3. Code Implementation:
Write the ESP32 code to send a request to the Arduino board when the button is pressed. Implement the appropriate code to establish communication between the ESP32 and Arduino using serial communication (the code is already written in esp_part.ino). Upon receiving the request, the Arduino should read the distance data from the Sharp sensor and send it back to the ESP32 (arduino_part.ino).

4. Display Distance Data on LCD:
Utilize the LCD library to display the received distance data on the connected screen. Initialize the LCD and implement a function to update and refresh the display with the current distance readings received from the Arduino.

5. Set Up ThingSpeak:
Create an account on the ThingSpeak platform if you haven't already. Set up a channel and obtain the necessary Write API Key for uploading data. Make sure to note down the relevant channel and field IDs.

6. Upload Data to ThingSpeak:
Modify the ESP32 code to include the necessary ThingSpeak library. Implement the code required to establish a Wi-Fi connection to ThingSpeak using the ESP32's Wi-Fi module. Update the code to send the received distance data to the appropriate channel and field using the Write API Key.

7. Verify and Test:
Upload the updated code to the ESP32 and Arduino UNO boards  and ensure that all connections are secure. Test the system by pressing the button on the ESP32 board. Verify that the distance data is displayed on the LCD screen and successfully uploaded to ThingSpeak.

Conclusion:
Congratulations! You have successfully implemented a system that retrieves distance data from a Sharp GP2Y0A21YK0F Analog Distance Sensor using an Arduino board and communicates with an ESP32 which obtains the data upon request. The data is then displayed on an LCD screen and uploaded to ThingSpeak, allowing for remote monitoring and analysis. This project offers exciting possibilities for various applications.

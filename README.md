About the Project:
The purpose of this project is to design and implement an IoT system that would correctly identify, monitor, store, and report the perceived peak temperature measurements within a particular location. 

The temperature monitoring system functionality includes: 
    Identifies, stores, monitors, and report temperature measurements in a specific location.
    Monitor and report weather parameters received over the mosquitto broker
    Display alerts when a specific set of temperature peaks are reached and detected. 

What Was Utilized: 
This had been accomplished through the use of several services and devices. Devices used include temperature and humidity sensors, alert system usage. Digital Ocean services used include Mosquitto Broker, MQTT, Node-Red and MySQL - phpMyAdmin

These devices and services used help with the communication and distribution of data that had been received from the microcontroller. 

How it works: 
The end-user must be registered to enter the application. The login process fetches the data from the database to ensure that only valid user can only enter the application. The end-user enters the IoT temperature monitoring application on there mobile device which is connected to Digital Ocean. Within Digital Ocean, the Mosquito Broker service is used to enable to use of MQTT. The server gets connected with the application through this. Sensor data is sent through a mosquitto broker for mqtt communication using Digital Ocean. Node-Red gets data from MySQL through queries. The user sets a threshold on the application which is sent to the database. When this threshold is reached a notification is sent and will activate the buzzer and send a warning message to the user. Once connected to the sensor, we can relay the temperature data. The temperature sensor is connected to the NodeMCU and the NodeMCU collects data from the sensor.The NodeMCU also connects directly to the Digital Ocean Node-Red & MQTT service. 

**TABLE OF CONTENTS** <br>
Section 1: Android app <br>
Section 2: Architecture design<br>
&nbsp;&nbsp;&nbsp;&nbsp;2.1   Architecture diagram and Description<br>
&nbsp;&nbsp;&nbsp;&nbsp;2.2   Deployment Design Decisions<br>
&nbsp;&nbsp;&nbsp;&nbsp;2.3   Sequence diagram<br>
&nbsp;&nbsp;&nbsp;&nbsp;2.4   Deployment Diagram<br>
Section 3: Arduino Code<br>
Section 4: Screen Dumps<br>
Section 5: Tests<br>

HOW TO RUN APP:
1. Open the project in Android Studio and build the project.
2. Run the project using an emulator device or Android device running a minimum API version of 30.
3. After the app has launched, you may register for an account.
4. Once account has been registered, you can log into the account.
5. After logging in, you will be taken to the main screen where you can start reading temperature data from the temperature sensor (if it's connected to the Internet).
6. You may enter a temperature limit value to set a desired monitoring temperature and then enter a threshold that the sensor can read above/below before sounding the alarm.
7. If the temperature falls above or below the limit threshold, an alarm will sound and a notification will be displayed on the app.

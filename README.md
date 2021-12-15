About the Project:
The purpose of this project is to design and implement an IoT system that would correctly identify, monitor, store, and report the perceived peak temperature measurements within a particular location. 

The temperature monitoring system functionality includes: 
    Identifies, stores, monitors, and report temperature measurements in a specific location.
    Monitor and report weather parameters received over the mosquitto broker
    Display alerts when a specific set of temperature peaks are reached and detected. 

What Was Utilized: 
This had been accomplished through the use of several services and devices. Devices used include temperature and humidity sensors, alert system usage. Digital Ocean services used include Mosquitto Broker, MQTT, Node-Red and MySQL - phpMyAdmin

These devices and services used help with the communication and distribution of data that had been received from the microcontroller. 

How Services Were Used: 


How it works: 
The end-user must be registered to enter the application. The login process fetches the data from the database to ensure that only valid user can only enter the application. The end-user enters the IoT temperature monitoring application on there mobile device which is connected to Digital Ocean. Within Digital Ocean, the Mosquito Broker service is used to enable to use of MQTT. The server gets connected with the application through this. Sensor data is sent through a mosquitto broker for mqtt communication using Digital Ocean. Node-Red gets data from MySQL through queries. The user sets a threshold on the application which is sent to the database. When this threshold is reached a notification is sent and will activate the buzze and send a warning message to the user. Once connected to the sensor, we can relay the temperature data. The temperature sensor is connected to the NodeMCU and the NodeMCU collects data from the sensor.The NodeMCU also connects directly to the Digital Ocean Node-Red & MQTT service. 

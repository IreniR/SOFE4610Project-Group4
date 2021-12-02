package com.example.temperaturemonitoringsystem;

import androidx.appcompat.app.AppCompatActivity;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    MemoryPersistence persistence = new MemoryPersistence();
    //TODO: fix persistence when app loses internet connection

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void connectToSensor (View view){
        String topic        = "tempData";
        //String content      = "OPEN";
        int qos             = 2;
        String broker       = "tcp://iotgrp4.com:8883";
        String clientId     = "TempMonitoringApp";
        String username     = "group4";
        String password     = "IOT123class";
        TextView connectionStatus = findViewById(R.id.temperature_value);

        try {
            MqttClient appClient = new MqttClient(broker, clientId, persistence);
            MqttConnectOptions connOpts = setUpConnectionOptions(username, password);
            System.out.println("Connecting to broker: "+broker);

            appClient.setCallback(new MqttCallback() {
                public void connectionLost(Throwable cause) {}

                public void messageArrived(String topic, MqttMessage message) throws Exception {
                    connectionStatus.setTextColor(Color.GREEN);
                    connectionStatus.setText(message.toString());
                    connectToSensor(view);
                }

                public void deliveryComplete(IMqttDeliveryToken token) {}
            });

            appClient.connect(connOpts);

            if (appClient.isConnected()){
                System.out.println("Connected!");
            }
            appClient.subscribe(topic);

        } catch(MqttException me) {
            System.out.println("reason " + me.getReasonCode());
            System.out.println("msg " + me.getMessage());
            System.out.println("loc " + me.getLocalizedMessage());
            System.out.println("cause " + me.getCause());
            System.out.println("excep " + me);
            me.printStackTrace();
        }
    }

    public void setThreshold (View view){
        String topic1        = "tempLimit";
        String topic2        = "tempThresh";
        int qos             = 2;
        String broker       = "tcp://iotgrp4.com:8883";
        String clientId     = "TempMonitoringApp";
        String username     = "group4";
        String password     = "IOT123class";
        EditText tempLimit = (EditText)findViewById(R.id.temperature_limit);
        String strTempLimit = tempLimit.getText().toString();
        EditText tempThresh = (EditText)findViewById(R.id.threshold_value);
        String strTempThresh = tempThresh.getText().toString();

        try {
            MqttClient appClient = new MqttClient(broker, clientId, persistence);
            MqttConnectOptions connOpts = setUpConnectionOptions(username, password);
            System.out.println("Connecting to broker: "+broker);
            appClient.connect(connOpts);

            if (appClient.isConnected()){
                System.out.println("Connected!");
            }
            MqttMessage message1 = new MqttMessage(strTempLimit.getBytes());
            message1.setQos(qos);
            appClient.publish(topic1, message1);
            MqttMessage message2 = new MqttMessage(strTempThresh.getBytes());
            message2.setQos(qos);
            appClient.publish(topic2, message2);
            appClient.disconnect();
        } catch(MqttException me) {
            System.out.println("reason " + me.getReasonCode());
            System.out.println("msg " + me.getMessage());
            System.out.println("loc " + me.getLocalizedMessage());
            System.out.println("cause " + me.getCause());
            System.out.println("excep " + me);
            me.printStackTrace();
        }
    }

    private static MqttConnectOptions setUpConnectionOptions(String username, String password) {
        MqttConnectOptions connOpts = new MqttConnectOptions();
        connOpts.setCleanSession(true);
        connOpts.setUserName(username);
        connOpts.setPassword(password.toCharArray());
        return connOpts;
    }
}
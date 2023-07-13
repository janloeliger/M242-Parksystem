package ch.parkhaus.controll.Mqtt;

import org.eclipse.paho.client.mqttv3.*;

public class MqttController implements MqttCallback {
    private MqttClient client;

    public void doDemo() {
        try {
            client = new MqttClient("tcp://cloud.tbz.ch:1883", "McQueen");
            client.connect();
            client.setCallback(this);
            client.subscribe("Lightning");
            MqttMessage message = new MqttMessage();
            message.setPayload("geparkt"
                    .getBytes());
            client.publish("Lightning", message);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void connectionLost(Throwable cause) {
        // TODO Auto-generated method stub

    }

    @Override
    public void messageArrived(String topic, MqttMessage message)
            throws Exception {
        System.out.println(message);
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
        // TODO Auto-generated method stub

    }

}
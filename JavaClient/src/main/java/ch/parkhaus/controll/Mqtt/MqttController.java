package ch.parkhaus.controll.Mqtt;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttTopic;

public class MqttController {
    private MqttClient mqtt;
    private MqttConnector connector;

    public MqttController() {
        connector = new MqttConnector();
    }

    public void connectToBroker() throws MqttException {
        mqtt = connector.getConnection();
        mqtt.connect();
    }

    public void closeConnection() throws MqttException {
        mqtt.disconnect();
        mqtt.close();
    }

    public void sendMessage(String topic, String messageString) throws MqttException {
        MqttMessage message = new MqttMessage(messageString.getBytes());
        mqtt.publish(topic, message);
    }
}

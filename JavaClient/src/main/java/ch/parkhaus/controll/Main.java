package ch.parkhaus.controll;

import ch.parkhaus.controll.Mqtt.MqttController;
import org.eclipse.paho.client.mqttv3.MqttException;

public class Main {
    public static void main(String[] args) {

        String topic = "parking";
        String messageString = "geparkt";
        MqttController controller = new MqttController();
        //controller.connectToBroker();
        //controller.sendMessage(topic, messageString);
        //controller.receiveMessage();
        controller.doDemo();

    }
}
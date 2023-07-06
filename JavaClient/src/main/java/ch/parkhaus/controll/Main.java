package ch.parkhaus.controll;

import ch.parkhaus.controll.Mqtt.MqttController;
import org.eclipse.paho.client.mqttv3.MqttException;

public class Main {
    public static void main(String[] args) {
        MqttController controller = new MqttController();
        try {
            controller.connectToBroker();
            controller.sendMessage("hs", "fetti Mensche");
        } catch (MqttException e) {
            e.printStackTrace();
        }

    }
}
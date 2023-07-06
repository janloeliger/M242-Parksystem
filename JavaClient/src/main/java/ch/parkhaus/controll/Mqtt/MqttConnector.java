package ch.parkhaus.controll.Mqtt;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MqttConnector {
    // Connection constants
    private static final String BROKER = "tcp://cloud.tbz.ch:1883";
    private static final String USERNAME = "";
    private static final String PASSWORD = "";
    private static final String CLIENT_ID = "parkhaus";



    public MqttConnector() {
    }

    public MqttClient getConnection() throws MqttException {
        MqttClient client = new MqttClient(BROKER, CLIENT_ID, new MemoryPersistence());
        MqttConnectOptions options = new MqttConnectOptions();
        options.setUserName(USERNAME);
        options.setPassword(PASSWORD.toCharArray());
        client.connect(options);
        return client;
    }
}

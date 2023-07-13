package ch.parkhaus.controll.Mqtt;

import ch.parkhaus.controll.TelegramController;
import org.eclipse.paho.client.mqttv3.*;

public class MqttController implements MqttCallback {
    private MqttClient client;
    private long timeParkedLeft;
    private long timeParkedRight;
    private boolean leftWarningMessage;
    private boolean rightWarningMessage;

    public void doDemo() {
        try {
            client = new MqttClient("tcp://cloud.tbz.ch:1883", "McQueen");
            client.connect();
            client.setCallback(this);
            client.subscribe("parking/links");
            client.subscribe("parking/rechts");
            MqttMessage message = new MqttMessage();
            message.setPayload("besetzt"
                    .getBytes());
            //client.publish("Lightning", message);
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
        checkMessage(message, topic);

    }

    public void checkMessage(MqttMessage message, String topic) {
        TelegramController telegramController = new TelegramController();

        String test = "Lightning";
        String isFree = "frei";
        String isParked = "besetzt";
        String isRight = "parking/rechts";
        String isLeft = "parking/links";
        String parkLeft = "";
        String parkRight = "";

        long currentTimeMillis = System.currentTimeMillis();
        int maximalTime = 2000;

        if (message.toString().equals(isParked) && topic.equals(isLeft)) {
            timeParkedLeft = System.currentTimeMillis();
            parkLeft = "Linkes Parkfeld ist besetzt";
            telegramController.startTelegramBot(parkLeft);
            System.out.println("Linkes Parkfeld ist besetzt");
        } else if (message.toString().equals(isFree) && topic.equals(isLeft)) {
            parkLeft = "Linkes Parkfeld ist frei";
            telegramController.startTelegramBot(parkLeft);
            System.out.println("Linkes Parkfeld ist frei");
            leftWarningMessage = false;
        } else if (message.toString().equals(isParked) && topic.equals(isRight)) {
            timeParkedRight = System.currentTimeMillis();
            parkRight = "Rechtes Parkfeld ist besetzt";
            telegramController.startTelegramBot(parkRight);
            System.out.println("Rechtes Parkfeld ist besetzt");
        } else if (message.toString().equals(isFree) && topic.equals(isRight)) {
            parkRight = "Rechtes Parkfeld ist frei";
            telegramController.startTelegramBot(parkRight);
            System.out.println("Rechtes Parkfeld ist frei");
            rightWarningMessage = false;
        }
    }

    public long getValueRight(){
        return timeParkedRight;
    }
    public long getTimeParkedLeft(){
        return timeParkedLeft;
    }

    public boolean getLeftWarning(){
        return leftWarningMessage;
    }
    public boolean getRightWarning(){
        return rightWarningMessage;
    }
    public void setLeftWarning(boolean value) {
        leftWarningMessage = value;
    }

    public void setRightWarning(boolean value) {
        rightWarningMessage = value;
    }

    @Override
    public void deliveryComplete(IMqttDeliveryToken token) {
        // TODO Auto-generated method stub

    }

}
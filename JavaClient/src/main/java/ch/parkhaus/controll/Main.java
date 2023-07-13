package ch.parkhaus.controll;

import ch.parkhaus.controll.Mqtt.MqttController;
import org.eclipse.paho.client.mqttv3.MqttException;

public class Main {

    public static void main(String[] args) {
        MqttController controller = new MqttController();
        TelegramController tgController = new TelegramController();
        controller.doDemo();

        try {
            Thread.sleep(5000); // Warte 5 Sekunden (5000 Millisekunden)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        long timeMax = 5000; // Maximale Zeitdifferenz für die Warnmeldung

        while (true) {
            long currentMillis = System.currentTimeMillis();

            long timeLeft = controller.getTimeParkedLeft();
            System.out.println("Time Left: " + timeLeft);
            long timeRight = controller.getValueRight();
            System.out.println("Time right: " + timeRight);

            boolean leftWarningSent = controller.getLeftWarning();
            boolean rightWarningSent = controller.getRightWarning();

            if (timeLeft > 0 && currentMillis - timeLeft >= timeMax && !leftWarningSent) {
                String message = "Das Auto auf dem linken Parkfeld befindet sich über dem Zeitlimit";
                tgController.startTelegramBot(message);
                // Update the warning message state in the MqttController class
                controller.setLeftWarning(true);
            }

            if (timeRight > 0 && currentMillis - timeRight >= timeMax && !rightWarningSent) {
                String message = "Das Auto auf dem rechten Parkfeld befindet sich über dem Zeitlimit";
                tgController.startTelegramBot(message);
                // Update the warning message state in the MqttController class
                controller.setRightWarning(true);
            }

            try {
                Thread.sleep(1000); // Warte 1 Sekunde (1000 Millisekunden) vor der nächsten Überprüfung
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
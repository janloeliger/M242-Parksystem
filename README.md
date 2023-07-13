# M242-Parksystem

## Quick Setup

Im Code des Core2 muss man noch die SSID, Passwort und MQTT anpassen.

Man braucht zwei M5Stack Core2:
- auf den einen Core2 muss man den C++-Code mit ``Core2`` flashen
- auf den anderen Core2 muss man den C++-Code für ``Core2Slave`` flashen

Ebenfalls braucht man einen Arduino Due:
- auf diesen muss man den ``ArduinoMonitor`` flashen.

Bei beiden M5Stack Core2 über den Port B einen Abstandssensor verbinden dazu müssen alle drei Geräte miteinander via I2C verbunden werden.
Bei dem Arduino Due muss man zwei Servo-Motore mit den Pins 10/11 verbinden.
Eine Sieben-Segment-Anzeige muss auch mit dem Arduino Due verbunden haben. Der Clock-Pin der Sieben-Segment-Anzeige muss auf Pin 7 verbunden werden und der Digital-Output Pin muss mit Pin 6 verbunden werden. 
Dazu müssen zwei Knöpfe auf Pin 8 und 9 verbunden werden. 

Um den aktuellen Zustand über die Parkplätze zu erhalten via Telegram, muss man im Java-Code in der ``MQTTController`` Klasse ebenfalls die MQTT Daten anpassen und in der ``TelegramController``-Klasse müssen die Daten des eigenen Telegram Bots erfasst werden.

Dies funktioniert so: 
1. Telegramm installieren und es einrichten
2. BotFather in der Suchleiste eingeben
3. den Chat mit BotFather öffnen
4. mit /start die Konversation mit BotFather starten.
5. Den Befehl /newbot eingeben, um einen neuen Bot zu erstellen
6. Die Anweisungen des BotFather befolgen um einen Bot zu erstellen und den Bot-Token zu erhalten.
7. Konversation mit dem erstellten Bot anfangen um den Chat-Token zu erhalten.

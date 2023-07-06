package ch.parkhaus.controll;

import com.pengrad.telegrambot.TelegramBot;
import com.pengrad.telegrambot.model.Update;
import com.pengrad.telegrambot.request.SendMessage;
import com.pengrad.telegrambot.response.SendResponse;

public class TelegramController {
    public void startTelegramBot() {
        // Ersetze "BOT_TOKEN" mit deinem eigenen Bot-Token
        TelegramBot bot = new TelegramBot("6252910635:AAHM7UnJybeZPdRLiIOYbUZzTIG8C_eS8Cc");

        // Ersetze "CHAT_ID" mit der Chat-ID deines Handys
        long chatId = 6122009233L;
        Object chatIdObj = Long.valueOf(chatId);

        // Sende die Nachricht an die angegebene Chat-ID
        SendMessage request = new SendMessage(chatIdObj, "Hello from your bot!");
        SendResponse response = bot.execute(request);

        // Prüfe den Status der Nachrichtenübermittlung
        boolean messageSent = response.isOk();
        if (messageSent) {
            System.out.println("Nachricht wurde erfolgreich gesendet.");
        } else {
            System.out.println("Fehler beim Senden der Nachricht: " + response.description());
        }
    }
}

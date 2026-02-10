#define _WIN32_WINNT 0x0601
#pragma execution_character_set("utf-8")

#include <tgbot/tgbot.h>
#include <iostream>

int main() {

    std::string token = "7925957040:AAGIjUL9lMvHc3l2-XmrFtdHRAeYAzw7e7Q";
    TgBot::Bot bot(token);
    int lastMessageId = -1;
    std::string lastCallbackId = "";

    TgBot::ReplyKeyboardMarkup::Ptr menu(new TgBot::ReplyKeyboardMarkup);
    menu->resizeKeyboard = true;

    TgBot::KeyboardButton::Ptr b1(new TgBot::KeyboardButton);
    b1->text = "❤️ Поздравление";

    TgBot::KeyboardButton::Ptr b2(new TgBot::KeyboardButton);
    b2->text = "🎁 Валентинка";

    TgBot::KeyboardButton::Ptr b3(new TgBot::KeyboardButton);
    b3->text = "🖼 Открытка";

    TgBot::KeyboardButton::Ptr b4(new TgBot::KeyboardButton);
    b4->text = "ℹ О боте";

    menu->keyboard.push_back({ b1, b2 });
    menu->keyboard.push_back({ b3, b4 });
  
    TgBot::InlineKeyboardMarkup::Ptr inlineKb(new TgBot::InlineKeyboardMarkup);

    TgBot::InlineKeyboardButton::Ptr in1(new TgBot::InlineKeyboardButton);
    in1->text = "❤️ Получить любовь";
    in1->callbackData = "love";

    TgBot::InlineKeyboardButton::Ptr in2(new TgBot::InlineKeyboardButton);
    in2->text = "💘 Ещё валентинку";
    in2->callbackData = "val2";

    TgBot::InlineKeyboardButton::Ptr in3(new TgBot::InlineKeyboardButton);
    in3->text = "🎬 Смотреть видео";
    in3->url = "https://youtube.com/shorts/s0kgimqWtzc?si=Ml6NtAx_cy-qN2Y1";

    TgBot::InlineKeyboardButton::Ptr in4(new TgBot::InlineKeyboardButton);
    in4->text = "💖 Люблю тебя";
    in4->callbackData = "love_secret";

    inlineKb->inlineKeyboard.push_back({ in1, in2 });
    inlineKb->inlineKeyboard.push_back({ in3 });
    inlineKb->inlineKeyboard.push_back({ in4 });
  
    bot.getEvents().onCommand("start", [&](TgBot::Message::Ptr message) {
       
        bot.getApi().sendAnimation(
            message->chat->id,
            "https://media.giphy.com/media/D3Rj4YGs1ufyQW3SDv/giphy.gif"
        );

        bot.getApi().sendMessage(
            message->chat->id,
            "💖 Добро пожаловать!\nВыбери кнопку ниже:",
            nullptr,
            nullptr,
            menu
        );
        });
   
    bot.getEvents().onCallbackQuery([&](TgBot::CallbackQuery::Ptr query) {

        if (query->id == lastCallbackId) return;
        lastCallbackId = query->id;

        if (query->data == "love") {
            bot.getApi().sendMessage(
                query->message->chat->id,
                "❤️ Ты самая лучшая и красивая девушка в мире!"
            );
        }

        if (query->data == "val2") {
            bot.getApi().sendAnimation(
                query->message->chat->id,
                "https://media.giphy.com/media/3oriO0OEd9QIDdllqo/giphy.gif"
            );
        }

        if (query->data == "love_secret") {
            bot.getApi().sendMessage(
                query->message->chat->id,
                "💖 Я люблю тебя больше всего на свете 💖"
            );

            bot.getApi().sendAnimation(
                query->message->chat->id,
                "https://media.giphy.com/media/v1.Y2lkPWVjZjA1ZTQ3NTduYmp4ZHY4bW4yYnI1dmQ4bWRna283cXZoN2dweHpiZWV4YW13YiZlcD12MV9naWZzX3JlbGF0ZWQmY3Q9Zw/u5N0Iq6WXDvbHTSqxz/giphy.gif"
            );
        }

        });

    bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {

        if (!message) return;

        if (message->messageId == lastMessageId) return;
        lastMessageId = message->messageId;

        if (message->text.empty()) return;

        std::string text = message->text;

        if (text[0] == '/') return;

        if (text == "❤️ Поздравление") {
            bot.getApi().sendMessage(
                message->chat->id,
                "💖 С Днём Святого Валентина Любимая!",
                nullptr,
                nullptr,
                inlineKb
            );
            return;
        }

        if (text == "🎁 Валентинка") {
            bot.getApi().sendAnimation(
                message->chat->id,
                "https://media.giphy.com/media/CZz2TBM4aTlqcxDZYp/giphy.gif"
            );
            return;
        }

        if (text == "🖼 Открытка") {
            bot.getApi().sendPhoto(
                message->chat->id,
                "https://i.pinimg.com/1200x/f2/af/54/f2af54a26abe8924dc9ccb14a883310d.jpg",
                "💌 Для Дариночки!"
            );
            return;
        }

        if (text == "ℹ О боте") {
            bot.getApi().sendAnimation(
                message->chat->id,
                "https://media.giphy.com/media/12afltvVzJIesM/giphy.gif"
            );

            bot.getApi().sendMessage(
                message->chat->id,
                "Этот бот создан для поздравления с 14 февраля 💘"
            );
            return;
        }

        });


    try {
        std::cout << "Bot started..." << std::endl;
        TgBot::TgLongPoll longPoll(bot);

        while (true) {
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

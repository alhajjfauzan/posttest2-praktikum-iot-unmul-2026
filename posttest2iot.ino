#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

const char* ssid = "Universitas Mulawarman";
const char* password = "";

#define BOT_TOKEN "8225155956:AAGmuizMKiudC_eOAhsjTSIAoc-S21isdnU"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
#define ID_A "6103206656"
#define ID_B "5750987705"
#define ID_C "1237536930"
#define GROUP_ID "-5029087510"
#define LED_A 2
#define LED_B 4
#define LED_C 5
#define LED_UTAMA 16
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define MQ2_PIN 34
int gasThreshold = 400;

void setup() {
  Serial.begin(115200);

  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_UTAMA, OUTPUT);

  dht.begin();

  WiFi.begin(ssid, password);
  client.setInsecure();

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(30000);
}
bool isAuthorized(String user_id, char led){
  if(user_id == ID_A && led == 'A') return true;
  if(user_id == ID_B && led == 'B') return true;
  if(user_id == ID_C && led == 'C') return true;
  return false;
}
void handleCommand(String text, String user_id, String chat_id, String name){
  if(name == "") name = user_id;
  if(text == "/id"){
    bot.sendMessage(chat_id, "🆔 ID kamu: " + user_id);
  }
  else if(text == "/groupid"){
    bot.sendMessage(chat_id, "📡 Chat ID: " + chat_id);
  }

  else if(text == "/ledA_on"){
    if(isAuthorized(user_id,'A')){
      digitalWrite(LED_A, HIGH);
      bot.sendMessage(chat_id, "💡 LED A ON oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya alhajj");
    }
  }

  else if(text == "/ledA_off"){
    if(isAuthorized(user_id,'A')){
      digitalWrite(LED_A, LOW);
      bot.sendMessage(chat_id, "🌙 LED A OFF oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya alhajj");
    }
  }
  else if(text == "/ledB_on"){
    if(isAuthorized(user_id,'B')){
      digitalWrite(LED_B, HIGH);
      bot.sendMessage(chat_id, "💡 LED B ON oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya cellia");
    }
  }

  else if(text == "/ledB_off"){
    if(isAuthorized(user_id,'B')){
      digitalWrite(LED_B, LOW);
      bot.sendMessage(chat_id, "🌙 LED B OFF oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya cellia");
    }
  }
  else if(text == "/ledC_on"){
    if(isAuthorized(user_id,'C')){
      digitalWrite(LED_C, HIGH);
      bot.sendMessage(chat_id, "💡 LED C ON oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya indi");
    }
  }

  else if(text == "/ledC_off"){
    if(isAuthorized(user_id,'C')){
      digitalWrite(LED_C, LOW);
      bot.sendMessage(chat_id, "🌙 LED C OFF oleh " + name);
    } else {
      bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! Ini bukan LED kamu, ini led punya indi");
    }
  }
  else if(text == "/ruangtamu_on"){
    digitalWrite(LED_UTAMA, HIGH);
    bot.sendMessage(chat_id, "🏠 Lampu ruang tamu ON oleh " + name);
  }

  else if(text == "/ruangtamu_off"){
    digitalWrite(LED_UTAMA, LOW);
    bot.sendMessage(chat_id, "🏠 Lampu ruang tamu OFF oleh " + name);
  }

  else if(text == "/cek_suhu"){
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    String msg = "🌡️ Suhu: " + String(t) + "°C\n";
    msg += "💧 Kelembapan: " + String(h) + "%";

    bot.sendMessage(chat_id, msg);
  }
  else if(text == "/cek_gas"){
    int gas = 0;
    for(int i=0; i<5; i++){
      gas += analogRead(MQ2_PIN);
      delay(50);
    }
    gas = gas / 5;
    String msg = "🧪 Gas Sensor\n";
    msg += "📊 Nilai: " + String(gas) + "\n";

    if(gas > gasThreshold){
      msg += "🚨 Status: Bahaya!";
    } else {
      msg += "🟢 Status: Aman";
    }

    bot.sendMessage(chat_id, msg);
  }
  else if(text == "/help"){
    String msg = "🤖 SMART HOME BOT\n\n";
    msg += "/ledA_on /ledA_off\n";
    msg += "/ledB_on /ledB_off\n";
    msg += "/ledC_on /ledC_off\n";
    msg += "/ruangtamu_on /ruangtamu_off\n";
    msg += "/cek_suhu\n/cek_gas\n";
    msg += "/id\n/groupid";

    bot.sendMessage(chat_id, msg);
  }
}

void loop(){
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  while(numNewMessages){
    for(int i=0; i<numNewMessages; i++){
      String text = bot.messages[i].text;
      String user_id = bot.messages[i].from_id;
      String chat_id = bot.messages[i].chat_id;
      String name = bot.messages[i].from_name;
      Serial.println("User ID: " + user_id);
      Serial.println("Chat ID: " + chat_id);
      Serial.println("Text: " + text);
      handleCommand(text, user_id, chat_id, name);
    }
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
  int gasValue = 0;

  for(int i=0; i<5; i++){
    gasValue += analogRead(MQ2_PIN);
    delay(50);
  }
  gasValue = gasValue / 5;

  if(gasValue > gasThreshold){
    String alertMsg = "🚨 PERINGATAN!\n";
    alertMsg += "Gas terdeteksi!\n";
    alertMsg += "📊 Nilai: " + String(gasValue);
    bot.sendMessage(GROUP_ID, alertMsg);
    delay(10000);
  }
}
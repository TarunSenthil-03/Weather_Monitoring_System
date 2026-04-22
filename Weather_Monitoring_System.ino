#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "vivo Y39 5G";
const char* password = "12345678";

WiFiClient client;

unsigned long myChannelNumber = 3280291;
const char * myWriteAPIKey = "TO81ESY8D4JJ73XI";

void setup() {
  WiFi.begin(ssid, password);
  dht.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  ThingSpeak.begin(client);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temperature)) {
    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  }

  delay(20000);   // Required delay for ThingSpeak
}
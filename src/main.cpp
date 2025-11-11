#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 15
#define DHTTYPE DHT22
#define LDRPIN 34
#define TRIG 12
#define ECHO 14
#define LED_OK 2
#define LED_ALERT 4
#define BUZZER 5

// Config Wi-Fi
const char *ssid = "Wokwi-GUEST";
const char *password = "";

// Config MQTT
const char *mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsg = 0;
unsigned long sentadoInicio = 0;
bool pessoaSentada = false;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

float medirDistancia()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duracao = pulseIn(ECHO, HIGH);
  float distancia = duracao * 0.034 / 2;
  return distancia;
}

void myTone(int pin)
{
  ledcAttachPin(pin, 0);       // pin, channel
  ledcWriteNote(0, NOTE_F, 4); // channel, frequency, octave
}

void myNoTone(int pin)
{
  ledcDetachPin(pin);
}

void setup()
{
  Serial.begin(115200);
  pinMode(LDRPIN, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_OK, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000)
  {
    lastMsg = now;

    float temp = dht.readTemperature();
    float umid = dht.readHumidity();
    int luz = analogRead(LDRPIN);
    float dist = medirDistancia();

    bool ambienteRuim = (temp > 28 || umid < 40 || luz < 800);
    bool pessoaAgora = (dist < 50); // pessoa sentada detectada

    // Controle do tempo sentado
    if (pessoaAgora)
    {
      if (!pessoaSentada)
      {
        pessoaSentada = true;
        sentadoInicio = now;
      }
    }
    else
    {
      pessoaSentada = false;
      sentadoInicio = 0;
    }

    bool pausaNecessaria = false;
    if (pessoaSentada && (now - sentadoInicio > 5000/*3600000*/))
    { // 1 hora
      pausaNecessaria = true;
    }

    // Sinalização visual/sonora
    if (ambienteRuim || pausaNecessaria)
    {
      digitalWrite(LED_ALERT, HIGH);
      digitalWrite(LED_OK, LOW);
      if (pausaNecessaria)
        myTone(BUZZER);
    }
    else
    {
      digitalWrite(LED_OK, HIGH);
      digitalWrite(LED_ALERT, LOW);
      myNoTone(BUZZER);
    }

    // Envia dados via MQTT
    char payload[200];
    snprintf(payload, sizeof(payload),
             "{\"temperatura\":%.2f,\"umidade\":%.2f,\"luz\":%d,\"distancia\":%.2f}",
             temp, umid, luz, dist);
    client.publish("/AllData", payload);


    Serial.println(payload);
  }
}

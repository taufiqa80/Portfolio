#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "CameraTrap";
const char* password = "CTrappwd";
const char* mqtt_server = "raspizerow.local";
const char* topic = "TrapNotif";
char ID = 'C'; // Trap ID

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int val = LOW;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  digitalWrite(D2,LOW);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() >= 5000)
    {
      digitalWrite(D2,HIGH);
      ESP.deepSleep(0);
    }
    delay(500);
    Serial.print(".");
    if (val == LOW)
    {
      digitalWrite(D2,HIGH);
      val = HIGH;
    }
    else
    {
      digitalWrite(D2,LOW);
      val = LOW;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

   if (millis() >= 5000)
    {
      digitalWrite(D2,HIGH);
      ESP.deepSleep(0);
    }
  
    while (!client.connected()) {
      if (millis() >= 5000)
      {
        digitalWrite(D2,HIGH);
        ESP.deepSleep(0);
      }
      Serial.print("Attempting MQTT connection...");
      // Attempt to connect
      if (client.connect("ESP8266Client")) {
        Serial.println("connected");
      }
    }
    
    client.loop();

    snprintf (msg, 75, "Trigger %c", ID);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic, msg);
    delay(1500);
    digitalWrite(D2,HIGH);
    ESP.deepSleep(0);
  }

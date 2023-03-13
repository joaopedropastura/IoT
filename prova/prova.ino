#include <common.h>
#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>

#include <DHT.h>
#include <LiquidCrystal.h>
#include <WiFi.h>

#define FIREBASE_HOST "https://avaliacao-iot-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "x0JSDlyziiS8IG8X50KT649stOpJ8p0VzEuF8nLw" 
DHT dht (33, DHT11);
LiquidCrystal lcd (13, 12, 14, 27, 26, 25);
const char *ssid = "Vivo-Internet-BF17";
const char *password = "78814222";
float temp;
float umid;
FirebaseData firebaseData;
FirebaseJson json;
byte customChar[] = {
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  dht.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.createChar(1, customChar);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(21, OUTPUT);


}

void turnOf()
{
  digitalWrite(18, 0);
  digitalWrite(19, 0);
  digitalWrite(32, 0);
  digitalWrite(21, 0);  
}

void loop() {
  temp = dht.readTemperature();
  umid = dht.readHumidity();
    
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.setCursor(0, 1);
  lcd.print(umid);
  lcd.print("%");
  
  delay(3000);
  digitalWrite(21, HIGH);
  json.set("/temperatura", temp);
  json.set("/umidade", umid);
  Firebase.updateNode(firebaseData, "/JoaoPedro/Sensor", json);
  digitalWrite(21, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.write(1);
  lcd.print("C");
  
  delay(3000);

  if (temp <= 25)
  {
    turnOf();
    digitalWrite(18, HIGH);
  }
  else if(temp <= 27)
  {
    turnOf();
    digitalWrite(19, HIGH);
  }
  else
  {
    turnOf();
    digitalWrite(32, HIGH);
  }

}

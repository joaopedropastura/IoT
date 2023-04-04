#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>
#include <WiFi.h>


#define FIREBASE_HOST "https://capsulas-fbdf0-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "KQsc6H51mKaBXsJt9dOLTLhu05MErDQAgj4jsy0A" 

const char *ssid = "Vivo-Internet-BF17";
const char *password = "78814222";
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  // put your setup code here, to run once:
  pinMode(19, INPUT);
  pinMode(21, OUTPUT);
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
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(19))
    digitalWrite(21, HIGH);
  delay(200);
  digitalWrite(21, LOW);

  json.set("/Nome", "cafe preto");
  json.set("/Quantidade", 10);
  Firebase.updateNode(firebaseData, "/Capsulas", json);

}

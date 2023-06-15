#include <FirebaseESP32.h>
#include <WiFi.h>


#define FIREBASE_HOST "https://porquinho-e387d-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "KQsc6H51mKaBXsJt9dOLTLhu05MErDQAgj4jsy0A" 


float amount;
const char *ssid = "Hemer";
const char *password = "zbqs9196";
FirebaseData firebaseData;
FirebaseJson json;

void setup() {
  pinMode(34, INPUT);
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  if(Firebase.getFloat(firebaseData, "Amount/networth"))
  {
  if (firebaseData.dataTypeEnum() == fb_esp_rtdb_data_type_float) {
      Serial.print(firebaseData.to<float>());
      amount = firebaseData.to<float>();
    }
    else{
      Serial.println(firebaseData.errorReason());
    }
  }
Serial.print(amount);
}
void loop() {
  Serial.println(amount);
  if(digitalRead(34))
  {
    amount += 1;
    json.set("/networth", amount);
    // Serial.println(amount);
    delay(200);
  }
   if(digitalRead(35))
  {
    amount += 0.5;
    json.set("/networth", amount);
    // Serial.println(amount);

    delay(200);
  }
  if(digitalRead(32))
  {
    amount += 0.25;
    // Serial.println(amount);
    json.set("/networth", amount);
    delay(200);
  }
    Firebase.updateNode(firebaseData, "/Amount", json);

  if(digitalRead(33))
    Serial.println("panela");
}

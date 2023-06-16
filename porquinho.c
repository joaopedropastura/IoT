#include <FirebaseESP32.h>
#include <WiFi.h>
#include <map>
#include <Servo.h>

#define FIREBASE_HOST "https://porquinho-e387d-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "KQsc6H51mKaBXsJt9dOLTLhu05MErDQAgj4jsy0A" 

FirebaseData firebaseData;
FirebaseJson json;
Servo myservo;

float amount;
const char *ssid = "Hemer";
const char *password = "zbqs9196";

std::map < int, float > coinValue = 
{
  { 25, 1 },
  { 32, 0.5 },
  { 33, 0.25 },
  { 34, 0.1 },
  { 35, 0.05 }
};
bool flag = false;
int vet[5] = {34,35,32,33,25};

void setup() {
 
  Serial.begin(9600);
  myservo.attach(26);
  pinMode(34, INPUT);
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  pinMode(25, INPUT);

  
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
      else
        Serial.println(firebaseData.errorReason());
    }
    myservo.write(147); 

  }

void AllowCoinPassage()
{
  myservo.write(60);
  delay(1000);
  myservo.write(147); 
}

float verify(int port)
{
  delay(500);
    if(digitalRead(port))
    {
      AllowCoinPassage();
      return coinValue[port];
    }
  Serial.println("Deu ruim");
  return 0;
}

void loop() {

  for (int i = 0; i < 5; i++)
  {
    if(digitalRead(vet[i]))
    {
      amount += verify(vet[i]);
      json.set("/networth", amount);
    }
  }
  Firebase.updateNode(firebaseData, "/Amount", json);
}

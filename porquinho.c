#include <LiquidCrystal_I2C.h>
#include <FirebaseESP32.h>
#include <Servo.h>
#include <WiFi.h>
#include <Wire.h>
#include <map>

#define FIREBASE_HOST "https://porquinho-e387d-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "KQsc6H51mKaBXsJt9dOLTLhu05MErDQAgj4jsy0A" 

FirebaseData firebaseData;
FirebaseJson json;
Servo myservo;

float amount;
const char *ssid = "Hemer";
const char *password = "zbqs9196";
bool flag = true;

LiquidCrystal_I2C lcd(0x27,20,4);

std::map < int, float > coinValue = 
{
  { 25, 1 },
  { 32, 0.5 },
  { 33, 0.25 },
  { 34, 0.1 },
  { 35, 0.05 }
};
int vet[5] = {34,35,32,33,25};

void setup() {
 
  Serial.begin(9600);
  myservo.attach(26);
  pinMode(34, INPUT);
  pinMode(32, INPUT);
  pinMode(35, INPUT);
  pinMode(33, INPUT);
  pinMode(25, INPUT);

  lcd.init();
  lcd.backlight();

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

void PrintMessage(float value)
{
  lcd.setCursor(0, 0);
  lcd.print("nham nham nham!");
  lcd.setCursor(0, 1);
  lcd.print("din din chegando...");
  lcd.setCursor(0, 2);
  lcd.print("R$:");
  lcd.setCursor(3, 2);
  lcd.print(value);
  delay(4000);
  lcd.clear();
}
void AllowCoinPassage()
{
  myservo.write(60);
  delay(1000);
  myservo.write(147); 
  delay(100);
  flag = true;
}

float verify(int port)
{
  delay(500);
    if(digitalRead(port) && flag)
    {
      flag = false;
      AllowCoinPassage();
      PrintMessage(coinValue[port]);
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
  lcd.setCursor(0, 4);
  lcd.print("Total: ");
  lcd.setCursor(8, 4);
  lcd.print("R$");
  lcd.setCursor(10, 4);
  lcd.print(amount);
}

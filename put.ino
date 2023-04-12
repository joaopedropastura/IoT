//#include <FirebaseESP32.h>
//#include <WiFi.h>
#include "lib.h"
//
//#define FIREBASE_HOST "https://capsulasfinal-default-rtdb.firebaseio.com/"
//#define FIREBASE_AUTH "CpYYbimhc6DmdfR9Fv91NCvhWtTiEpb6B9Q5IVHU"

//LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
//
//const char *ssid = "Vivo-Internet-BF17";
//const char *password = "78814222";

//const char *ssid = "iPhone de Ramirez";
//const char *password = "trabalhoesp32";

FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonData result;
int qtt = 100;
int indx = 0;
int seila = 0;

std::vector<CafeTipo> cafesTipos;

void setup() {
//  lcd.begin(16, 2);
  pinMode(26, INPUT);
  Serial.begin(9600);
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
  if (digitalRead(26))
  {
//    Serial.print("Olha quanta coisa: "); Serial.println(qtt);
    json.set("/Capsulas/"+ (String)indx + "/Nome", "cafe preto");
    json.set("/Capsulas/"+ (String)indx + "/Quantidade", qtt);
    qtt--;
    indx++;
    Firebase.updateNode(firebaseData, "/", json);
    delay(200);
  }
  if (Firebase.getInt(firebaseData, "/Capsulas")) {
    if (firebaseData.dataTypeEnum() == fb_esp_rtdb_data_type_integer) {
      seila = firebaseData.to<int>();
    }
//    Serial.print(seila);
//    Serial.print(Firebase.getInt(firebaseData, "/"));
  }
    String s = firebaseData.stringData();
    cafesTipos = jsonParse(s);

    
    for (int i = 0; i < cafesTipos.size(); i++)
    {
      Serial.println(cafesTipos[i].Nome);
      Serial.print(" - ");
      Serial.print(cafesTipos[i].Quantidade);
      delay(500);
    }
}

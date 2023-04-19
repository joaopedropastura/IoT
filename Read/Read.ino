#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <vector>

#define WIFI_SSID "Vivo-Internet-BF17"
#define WIFI_PASSWORD "78814222"
#define API_KEY "AIzaSyCNF0kP0IkgQWUfme7J1NNbaL2rC8MM4ps"
#define DATABASE_URL "https://capsulas-rtdb-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int coffeeIndex = 0;

typedef struct {
  String Name;
  int Amount;
} CoffeeStorage;


std::vector<CoffeeStorage> coffeeStorages;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("signUp OK");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();


    if (Firebase.RTDB.getJSON(&fbdo, "Capsulas/")) {
      Serial.println(fbdo.dataType());
      if (fbdo.dataType() == "json") {
        Serial.println(fbdo.jsonString());
      } else {
        Serial.println("FAILED: " + fbdo.errorReason());
      }
    }



    //    for (;;) {
    //
    //      String path = "Capsulas/" + (String)coffeeIndex;
    //      CoffeeStorage newData;
    //
    //      if (Firebase.RTDB.getString(&fbdo, path + "/Name")) {
    //        if (fbdo.dataType() == "string") {
    //          newData.Name = fbdo.stringData();
    //          Serial.println(fbdo.stringData().length());
    //          Serial.println(newData.Name == "");
    //          Serial.println(newData.Name == " ");
    //        } else {
    //          Serial.println("FAILED: " + fbdo.errorReason());
    //          break;
    //        }
    //      }
    //
    //      if (Firebase.RTDB.getInt(&fbdo, path + "/Amount")) {
    //        if (fbdo.dataType() == "int") {
    //          newData.Amount = fbdo.intData();
    //        } else {
    //          Serial.println("FAILED: " + fbdo.errorReason());
    //          break;
    //        }
    //      }
    //
    //      Serial.println((String)coffeeIndex + " - " + newData.Name + " - " + newData.Amount);
    //      coffeeStorages.push_back(newData);
    //      ++coffeeIndex;
    //    }
    //
    //    Serial.println("Saiu");
    //
    //    for (int i = 0; i < coffeeStorages.size(); i++)
    //    {
    //      Serial.println((String)coffeeStorages[i].Name + " - " + coffeeStorages[i].Amount);
    //    }
  }
}

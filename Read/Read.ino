#include <WiFi.h>
#include <FirebaseESP32.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <vector>

#define WIFI_SSID "gab"
#define WIFI_PASSWORD "gabriellee"
#define API_KEY "AIzaSyCNF0kP0IkgQWUfme7J1NNbaL2rC8MM4ps"
#define DATABASE_URL "https://capsulas-rtdb-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

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
  if (Firebase.ready() && signupOK) {
    if (Firebase.RTDB.getArray(&fbdo, "/Capsulas")) {
      Serial.println(fbdo.dataType());
      if (fbdo.dataType() == "array") {
        FirebaseJsonArray &arr = fbdo.to<FirebaseJsonArray>();

        FirebaseJsonData result;

        result.get<FirebaseJsonArray>(arr);

        for (size_t i = 0; i < arr.size(); i++) {
          // result now used as temporary object to get the parse results
          arr.get(result, i);

          String data = result.to<String>();
          data.replace("{", "");
          data.replace("}", "");
          data.replace("\"", "");
          data.replace("Name:", "");
          data.replace("Amount:", "");

        
          int amount = data.substring(0, data.indexOf(',')).toInt();
          String name = data.substring(data.indexOf(',') + 1);
          coffeeStorages.push_back({ name, amount });
          Serial.println(name + " - " + (String)amount);
        }
      } else {
        Serial.println("FAILED: " + fbdo.errorReason());
      }
    }
  }
}

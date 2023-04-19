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
  byte Amount;
} CoffeeStorage;


std::vector<CoffeeStorage> coffeeStorages = {
  { "Mocha", 6 },
  { "Capuccino", 0 },
  { "Café com Leite", 10 },
  { "Café Brasileiro", 3 },
  { "Café Espresso", 8 },
  { "Mochaccino", 9 },
  { "Frapuccino", 1 }
};

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
    for (int i = 0; i < coffeeStorages.size(); i++) {
      String path = "Capsulas/" + (String)i;

      if (!Firebase.RTDB.setString(&fbdo, path + "/Name", coffeeStorages[i].Name) || !Firebase.RTDB.setInt(&fbdo, path + "/Amount", coffeeStorages[i].Amount)) {
        Serial.println(i + " - ERRO: " + fbdo.errorReason());
      }
    }
  }
}

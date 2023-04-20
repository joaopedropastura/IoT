#include <WiFi.h>
#include <FirebaseESP32.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <vector>

#define WIFI_SSID "BARTO 2"
#define WIFI_PASSWORD "barto5302"
#define API_KEY "AIzaSyCNF0kP0IkgQWUfme7J1NNbaL2rC8MM4ps"
#define DATABASE_URL "https://capsulas-rtdb-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


typedef struct {
  String Name;
  byte Amount;
} CoffeeStorage

std::vector<CoffeeStorage> coffeeStorages = {
  { "Mocha", 6 },
  { "Capuccino", 0 },
  { "Café com Leite", 10 },
  { "Café Brasileiro", 3 },
  { "Café Espresso", 8 },
  { "Mochaccino", 9 },
  { "Frapuccino", 1 }
};
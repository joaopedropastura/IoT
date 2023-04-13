#include "lib.h"

FirebaseData firebaseData;
FirebaseJson json;

int status = WL_IDLE_STATUS;
int quantidade = 100;
int indx = 0;
String val = "example";

std::vector<CafeTipo> cafesTipos;

void setup() {
  // Serial init
  Serial.begin(9600);
  while (!Serial) { }

  // Pin init
  pinMode(26, INPUT);
  pinMode(21, OUTPUT);

  // WiFi init
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
  Serial.print("You're connected to the network");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop() {
  if (digitalRead(26))
  {
    json.set("/Capsulas/" + (String)indx + "/Nome", "cafe preto");
    json.set("/Capsulas/" + (String)indx + "/Quantidade", quantidade);
    quantidade--;
    indx++;
    Firebase.updateNode(firebaseData, "/", json);
    delay(300);
  }

  if (Firebase.getString(firebaseData, "/Capsulas")) {                           // On successful Read operation, function returns 1
    Serial.println(firebaseData.dataType());
    val = firebaseData.stringData();
    Serial.println(val);
    Serial.println("\n Change value at firebase console to see changes here.");
    delay(1000);
  } else {
    Serial.println(firebaseData.errorReason());
  }
  // }
  //  String json = firebaseData.stringData();
  //  cafesTipos = jsonParse(json);
  //  Serial.println(json);
  //
  //  for (int i = 0; i < cafesTipos.size(); i++)
  //  {
  //
  //    Serial.print(cafesTipos[i].Nome);
  //    Serial.print(" - ");
  //    Serial.println(cafesTipos[i].Quantidade);
  //    delay(500);
  //  }
}

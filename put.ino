#include <FirebaseESP32.h>
#include <vector>
#include <WiFi.h>

// Declaration of consts
const char FIREBASE_HOST[] = "https://capsulasfinal-default-rtdb.firebaseio.com/";
const char FIREBASE_AUTH[] = "CpYYbimhc6DmdfR9Fv91NCvhWtTiEpb6B9Q5IVHU";
const char *ssid = "Vivo-Internet-BF17";
const char *pass = "78814222";

// Declaration of vars
int status = WL_IDLE_STATUS;
int quantidade = 100;
int indx = 0, idx = 0;
int seila = 0;

// Declaration of structs
typedef struct
{
  String Nome;
  int Quantidade;
} CafeTipo;

// Declaration of arrays
std::vector<CafeTipo> cafesTipos;
std::vector<String> cafes {"Espresso", "cafe preto", "cafe caseiro", "mocha", "alpino", "pingado"};

// Declaration of funcs
std::vector<CafeTipo> jsonParse(String json);

// Declaration of objs
FirebaseData firebaseData;
FirebaseJson json;
FirebaseJsonData result;

void setup() {
  // Serial init
  Serial.begin(9600);
  while (!Serial) { }

  // Pin init
  pinMode(13, INPUT);
  pinMode(21, OUTPUT);

  // WiFi init
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Firebase init
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop() {
  if (digitalRead(13))
  {
    json.set("/Capsulas/" + (String)indx + "/Nome", cafes[idx]);
    json.set("/Capsulas/" + (String)indx + "/Quantidade", quantidade);
    quantidade--;
    indx++;
    idx > cafes.size() - 1 ? idx++ : idx = 0;
    Firebase.updateNode(firebaseData, "/", json);
    Serial.println("ta aq");
    delay(300);
  }

  String sla = firebaseData.stringData();
  Serial.println(sla);
  cafesTipos = jsonParse(sla);

  for (int i = 0; i < cafesTipos.size(); i++)
  {

    Serial.print(cafesTipos[i].Nome);
    Serial.print(" - ");
    Serial.println(cafesTipos[i].Quantidade);
    delay(500);
  }
}


std::vector<CafeTipo> jsonParse(String json)
{
  json.replace("[", "");
  json.replace("]", "");
  json.replace("{", "");
  json.replace("}", "");
  json.replace("\"", "");
  json.replace("Nome:", "");
  json.replace("Quantidade:", "");

  std::vector<CafeTipo> cafesTipos;

  for (;;) {
    int middleIndex = json.indexOf(",") + 1;
    int endIndex = json.indexOf(",", middleIndex) + 1;
    String jsonData = json.substring(0, endIndex - 1);
    json = json.substring(endIndex);

    String nomeCafe = jsonData.substring(0, middleIndex - 1);
    int quantidadeCafe = jsonData.substring(middleIndex).toInt();
    cafesTipos.push_back(CafeTipo { nomeCafe, quantidadeCafe });

    if (endIndex >= json.length())
    {
      middleIndex = json.indexOf(",") + 1;
      nomeCafe = jsonData.substring(0, middleIndex - 1);
      quantidadeCafe = jsonData.substring(middleIndex).toInt();
      cafesTipos.push_back(CafeTipo { nomeCafe, quantidadeCafe });
      break;
    }
  }

  return cafesTipos;
}

#ifndef Network_h
#define Network_h
#include <vector>
#include <FirebaseESP32.h>
#include <WiFi.h>

#define FIREBASE_HOST "https://capsulasfinal-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "CpYYbimhc6DmdfR9Fv91NCvhWtTiEpb6B9Q5IVHU"

const char *ssid = "Vivo-Internet-BF17";
const char *password = "78814222";

typedef struct {
  String Nome;
  int Quantidade;
} CafeTipo;

std::vector<CafeTipo> jsonParse(String json);

#endif

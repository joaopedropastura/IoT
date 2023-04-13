#ifndef lib_h
#define lib_h

#include <WiFi.h>
#include <vector>
#include <FirebaseESP32.h>

const char FIREBASE_HOST[] = "https://capsulasfinal-default-rtdb.firebaseio.com/";
const char FIREBASE_AUTH[] = "CpYYbimhc6DmdfR9Fv91NCvhWtTiEpb6B9Q5IVHU";

const char ssid[] = "Vivo-Internet-BF17";
const char pass[] = "78814222";

typedef struct
{
  String Nome;
  int Quantidade;
} CafeTipo;

std::vector<CafeTipo> jsonParse(String json);

#endif

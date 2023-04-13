#include "lib.h"

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

#include "lib.h"


void createList() 
{
  if (Firebase.ready() && signupOK) 
  {
    for (int i = 0; i < coffeeStorages.size(); i++) 
    {
      String path = "Capsulas/" + (String)i;
      if (!Firebase.RTDB.setString(&fbdo, path + "/Name", coffeeStorages[i].Name) || !Firebase.RTDB.setInt(&fbdo, path + "/Amount", coffeeStorages[i].Amount)) 
        Serial.println(i + " - ERRO: " + fbdo.errorReason());
    }
  }
}
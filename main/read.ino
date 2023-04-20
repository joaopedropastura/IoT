#include "lib.h"

std::vector<CoffeeStorage> readFirebase() {
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
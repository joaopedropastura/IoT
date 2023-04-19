#include <LiquidCrystal.h>
#include <vector>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t x_pin = 34;
const uint8_t y_pin = 35;
const uint8_t button_pin = 32;


String CafesNomes[]{
  "Cafe Preto",
  "Cafe com Leite",
  "Moccha",
  "Cafe de Canela",
  "Cafe Expresso",
  "Cafe Amargo"
};

int Quantidades[]{
  10,10,20,30,20,10
}



struct cafe{
  String Nome;
  int Quantidade;
};

std::vector<cafe> Cafes;


byte setaDireita[] = {
  B00000,
  B00100,
  B00110,
  B11111,
  B11111,
  B00110,
  B00100,
  B00000
};

byte setaBaixo[] = {
  B00000,
  B00000,
  B00100,
  B00100,
  B11111,
  B01110,
  B00100,
  B00000
};



void setup() {

  pinMode(33,INPUT_PULLUP);
  
  pinMode(button_pin, INPUT_PULLUP); //DEFINE A PORTA COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  Serial.begin(9600); //INICIALIZA O MONITOR SERIAL

  lcd.begin();
  lcd.clear();

  lcd.createChar(0, setaDireita);
  lcd.createChar(1, setaBaixo);
}




void mostrarCafes() {

  int len = Cafes.size();
  Serial.println(Cafes[0].Nome)
  Serial.println(len);
  
//  int indx = 0;
//  int len = sizeof(TiposCafe);
//  bool parar = false;
//
//  int setaPos = 0;
//
//
//  Serial.println(len);
//
//  
//  while(parar == false)
//  {
//    int inicioString = 0;
//    int finalString = 11;
//    
//    for (int i = 2; i < 20; i++) {
//      if (indx != len - 2) {
//        lcd.clear();
//        lcd.setCursor(0, setaPos);
//        lcd.write(byte(0));
//        lcd.setCursor(15, 1);
//        lcd.write(byte(1));
//      } else {
//        lcd.clear();
//        lcd.setCursor(0, setaPos);
//        lcd.write(byte(0));
//      }
//  
//      if (setaPos % 2 == 0) {
//        lcd.setCursor(2, 0);
//        lcd.print(TiposCafe[indx].Nome.substring(inicioString, finalString));
//        lcd.setCursor(2, 1);
//        lcd.print(TiposCafe[indx + 1].Nome.substring(0, 11));
//      } else if (setaPos % 2 != 0) {
//        lcd.setCursor(2, 0);
//        lcd.print(TiposCafe[indx].Nome.substring(0, 11));
//        lcd.setCursor(2, 1);
//        lcd.print(TiposCafe[indx + 1].Nome.substring(inicioString, finalString));
//      }
//  
//      inicioString++;
//      finalString++;
//  
//      if ((analogRead(x_pin)) == 0) {
//        if (setaPos % 2 == 0) {
//          indx = indx - 2;
//          setaPos++;
//          inicioString = 0;
//          finalString = 11;
//        } else {
//          setaPos--;
//          inicioString = 0;
//          finalString = 11;
//        }
//      } else {
//        if ((analogRead(x_pin)) == 4095) {
//          
//          if (setaPos % 2 != 0) {
//            indx = indx + 2;
//            setaPos--;
//            inicioString = 0;
//            finalString = 11;
//          } else {
//            setaPos++;
//            inicioString = 0;
//            finalString = 11;
//          }
//  
//        } else {
//          if ((analogRead(y_pin)) == 0) {} else {
//            if ((analogRead(y_pin)) == 4095) {} else {
//              if (digitalRead(button_pin) == LOW) {
//                lcd.clear();
//                lcd.setCursor(0, 1);
//                lcd.print("PRESSIONADO");
//                parar = true;
//              }
//            }
//          }
//        }
//      }
//      delay(300);
//      Serial.println(len);
//      Serial.println(indx);
//  
//    }
//  }


}


void loop() {
  String nome = "";
  int qtt = 0;

  
  for(int i = 0; i < 6; i++){
    nome = CafesNomes[i];
    qtt = Quantidades[i];
    Cafes.push_back( {nome, qtt} );
  }


  
  lcd.setCursor(0,0);
  lcd.print("Aproxime seu");
  lcd.setCursor(0,1);
  lcd.print("cartao");

  if(digitalRead(33) == LOW){
    mostrarCafes(Cafes);
    delay(300);
  }

  

}

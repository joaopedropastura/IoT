#include <LiquidCrystal.h>
#include <vector>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint8_t x_pin = 34;
const uint8_t y_pin = 35;
const uint8_t button_pin = 32;
int setaLado = 7;
bool selecionado = false;


String CafesNomes[] {
  "Cafe Preto",
  "Cafe com Leite",
  "Moccha",
  "Cafe de Canela",
  "Cafe Expresso",
  "Cafe Amargo"
};

int Quantidades[] {
  10, 10, 20, 30, 20, 10
};



struct cafe {
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

  pinMode(33, INPUT_PULLUP);

  pinMode(button_pin, INPUT_PULLUP); //DEFINE A PORTA COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
  //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
  Serial.begin(9600); //INICIALIZA O MONITOR SERIAL

  lcd.begin();
  lcd.clear();

  lcd.createChar(0, setaDireita);
  lcd.createChar(1, setaBaixo);
}


bool selecionarCafe(int qtt) {
  delay(500);
  while (true)
  {
    lcd.setCursor(0, 0);
    lcd.print("Quantidade:");
    lcd.setCursor(12, 0);
    lcd.print(qtt);

    lcd.setCursor(setaLado, 1);
    lcd.write(byte(0));
    lcd.setCursor(0, 1);
    lcd.print("Pegar:");
    lcd.setCursor(8, 1);
    lcd.print("Sim");
    lcd.setCursor(13, 1);
    lcd.print("Nao");

    if ((analogRead(y_pin) == 0) && setaLado == 7) {
      setaLado = setaLado + 5;
      lcd.clear();
    } else if ((analogRead(y_pin) == 4095) && setaLado == 12) {
      setaLado = setaLado - 5;
      lcd.clear();
    } else if (digitalRead(button_pin) == LOW && setaLado == 7) {
      selecionado = true;
      return true;
    } else if (digitalRead(button_pin) == LOW && setaLado == 12) {
      return true;
    }
  }
}







int mostrarCafes() {

  int indx = 0;
  bool parar = false;

  int setaPos = 0;

  while (parar == false)
  {
    int inicioString = 0;
    int finalString = 11;

    for (int i = 2; i < 20; i++) {

      lcd.clear();
      lcd.setCursor(0, setaPos);
      lcd.write(byte(0));
      lcd.setCursor(15, 1);
      lcd.write(byte(1));

      if (setaPos % 2 == 0) {
        lcd.setCursor(2, 0);
        lcd.print(Cafes[indx].Nome.substring(inicioString, finalString));
        lcd.setCursor(2, 1);
        lcd.print(Cafes[indx + 1].Nome.substring(0, 11));
      } else if (setaPos % 2 != 0) {
        lcd.setCursor(2, 0);
        lcd.print(Cafes[indx].Nome.substring(0, 11));
        lcd.setCursor(2, 1);
        lcd.print(Cafes[indx + 1].Nome.substring(inicioString, finalString));
      }

      inicioString++;
      finalString++;

      if ((analogRead(x_pin)) == 0) {
        if (setaPos % 2 == 0) {
          indx = indx - 2;
          setaPos++;
          inicioString = 0;
          finalString = 11;
        } else {
          setaPos--;
          inicioString = 0;
          finalString = 11;
        }
      } else {
        if ((analogRead(x_pin)) == 4095) {

          if (setaPos % 2 != 0) {
            indx = indx + 2;
            setaPos--;
            inicioString = 0;
            finalString = 11;
          } else {
            setaPos++;
            inicioString = 0;
            finalString = 11;
          }

        } else {
          if ((analogRead(y_pin)) == 0) {} else {
            if ((analogRead(y_pin)) == 4095) {} else {
              if (digitalRead(button_pin) == LOW) {
                if (setaPos == 0) {
                  lcd.clear();
                  if (selecionarCafe(Cafes[indx].Quantidade) == true && selecionado == true) {
                    lcd.clear();
                    return indx;
                  }
                } else if (setaPos == 1) {
                  lcd.clear();
                  if (selecionarCafe(Cafes[indx + 1].Quantidade) == true && selecionado == true) {
                    lcd.clear();
                    return indx + 1;
                  }
                }
              }
            }
          }
        }
      }
      delay(300);
    }
  }
  lcd.clear();
}


void loop() {
  String nome = "";
  int qtt = 0;

  for (int i = 0; i < 6; i++) {
    nome = CafesNomes[i];
    qtt = Quantidades[i];
    Cafes.push_back( {nome, qtt} );
  }


  lcd.setCursor(0, 0);
  lcd.print("Aproxime seu");
  lcd.setCursor(0, 1);
  lcd.print("cartao");

  if (digitalRead(33) == LOW) {
    Serial.println(mostrarCafes());
    delay(300);
  }



}

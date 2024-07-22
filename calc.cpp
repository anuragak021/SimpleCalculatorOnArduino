#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define keypad pin connections
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal_I2C lcd(0x27, 16, 2);

String input = ""; 
float num1 = 0; 
float num2 = 0; 
char operatorSymbol = ' ';
bool resultShown = false; 

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Calculator");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (resultShown) {
      lcd.clear();
      resultShown = false;
    }

    if (isdigit(key)  key == '.') {
      input += key;
      lcd.print(key);
    }
    else if (key == '+'  key == '-'  key == '*'  key == '/') {
      num1 = input.toFloat();
      operatorSymbol = key;
      input = "";
      lcd.setCursor(15, 0);
      lcd.print(operatorSymbol);
    }
    else if (key == '=') {
      num2 = input.toFloat();
      input = "";
      float result;
      switch (operatorSymbol) {
        case '+':
          result = num1 + num2;
          break;
        case '-':
          result = num1 - num2;
          break;
        case '*':
          result = num1 * num2;
          break;
        case '/':
          result = num1 / num2;
          break;
        default:
          lcd.setCursor(0, 1);
          lcd.print("Error");
          delay(1000);
          lcd.clear();
          break;
      }
            lcd.setCursor(0, 1);
      lcd.print("Result: ");
      lcd.print(result);
      resultShown = true;
    }
    else if (key == 'C') {
      input = "";
      num1 = 0;
      num2 = 0;
      operatorSymbol = ' ';
      resultShown = false;
      lcd.clear();
    }
  }
}

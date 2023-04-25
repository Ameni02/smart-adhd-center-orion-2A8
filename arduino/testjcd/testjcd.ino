#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char data;
String data2;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','A','3'},
  {'4','5','B','6'},
  {'7','8','C','9'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte buttonPin = 10;
bool buttonState = HIGH; // Initialise l'état du bouton à HIGH

void setup(){
  keypad.setDebounceTime(500);
  lcd.init();
  lcd.backlight();
  pinMode(buttonPin, INPUT_PULLUP); // Configure le port numérique du bouton en entrée avec résistance de Pull-Up activée
  Serial.begin(9600);
}

void loop(){
  static String code = "";
  char key = keypad.getKey();
  
  if (key != NO_KEY){
    code += key;
   
  }
  
  buttonState = digitalRead(buttonPin); // Lis l'état actuel du bouton
  
  if (buttonState == LOW){
    Serial.print(code);
    data2= Serial.readString();// Si le bouton est enfoncé
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NAME: ");
    lcd.print(data2);
    
    code = ""; // Réinitialise le code
    delay(500); // Attends 500ms pour éviter les rebonds de bouton
  }
}

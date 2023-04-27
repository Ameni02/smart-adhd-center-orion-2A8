#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);
int getFingerprintIDez();
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
#define PIN_LED1 11 //le numéro de la broche sur laquelle la lampe 2  est branchée
#define PIN_LED2 12
#define PIN_LEDFALSE 13// Le numéro de la broche sur laquelle la lampe 1 
//(par défaut intégrée dans la carte) est branchée 
#define pas  20 // incrément de l'intensité
Servo myservo;
char data;
String data2;
int fing;
int ISD_PIN =5; // ISD1820 module PE Pin
// variable contenant le caractère lu
int x; // variable contenant l'intensité de la deuxième lampe

void setup() {

  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(ISD_PIN, INPUT_PULLUP); 

  // Configure la broche 11 sur laquelle est reliée notre LED  en sortie
  pinMode(PIN_LED1,OUTPUT);
  pinMode(PIN_LEDFALSE,OUTPUT);
   myservo.attach(9);
//La LED reliée à la broche 11 est intialisé à l'état LOW
  digitalWrite(PIN_LED2,LOW);
  // Configure la broche 13 sur laquelle est reliée notre LED  en sortie
  pinMode(PIN_LED2,OUTPUT);
//La LED reliée à la broche 13 est intialisé à l'état LOW
pinMode(PIN_LED1,OUTPUT);
  analogWrite(PIN_LED1,HIGH);
    analogWrite(PIN_LEDFALSE,LOW);
  Serial.begin(9600); //Permet d'initialiser le moniteur série à 9600 bauds 
  x=0; // Intialiser l'intensité de la deuxième lampe 
 finger.begin(57600);
}

void spekear()
{
    digitalWrite(ISD_PIN, HIGH);
    delay (100);        
    digitalWrite(ISD_PIN, LOW);
    delay (2000);  
}

void loop() {

fing=getFingerprintIDez();
   //Serial.write(fing);

  //digitalWrite(PIN_LED1,HIGH);
    
if((Serial.available()>0) || (fing>0)){
       //Serial.println(fing);   
    //Si un message a été reçu  faire ceci
     
     data2= Serial.readString();
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
   
//     (data == fing ) && 
     if((data == fing ) && (finger.fingerID==9) || (finger.fingerID==41)) //si le caractère lu est égale à 1
    {    Serial.write(fing);
       Serial.write(data);
    Serial.write("yess");
      Serial.write(fing);
      digitalWrite(PIN_LED2,HIGH);
      digitalWrite(PIN_LED1,LOW); 
       myservo.write(0); 
         Serial.print(fing);
        
        spekear();
       lcd.clear();
       lcd.setCursor(4,0);
       lcd.print(data2);
      digitalWrite(PIN_LED2,HIGH);
      digitalWrite(PIN_LED1,LOW);
      // alumer la lampe 
     //envoyer le nouvel état de la lampe  
     delay(5000);
    myservo.write(90);
      digitalWrite(PIN_LED2,LOW);
      digitalWrite(PIN_LED1,HIGH);
     }  
     else if(data=! fing ) //si le caractère lu est égale à 0

     {
         Serial.write("ghalet");
     digitalWrite(PIN_LEDFALSE,HIGH);
     delay(500);
     digitalWrite(PIN_LEDFALSE,LOW);
      delay(500);
      digitalWrite(PIN_LEDFALSE,HIGH);
      delay(500);
       digitalWrite(PIN_LEDFALSE,LOW);
//       lcd.clear();
//       lcd.setCursor(4,0);
//       lcd.print("heyyyh");
//      myservo.write(0);
//        digitalWrite(PIN_LED2,LOW);
//      digitalWrite(PIN_LED1,HIGH); //éteindre la lampe
//        Serial.write('0'); //envoyer le nouvel état de la lampe
     
     }   
     // Régler l'intensité de la luminosité de la deuxième lampe branchée sur la broche 11
     else if(data=='2') //si le caractère reçu est égale à 2
     {
        if(x+pas<=255) // si l'intesité est encore inférieur à l'intensité max=255 
        x=x+pas; // incrémenter l'intesité de la lumière   
        analogWrite(PIN_LED1,x); 
        
     }  
     else if(data=='3')
     {
        if((x>pas)) // si l'intesité est encore supérieur au pas 
         x=x-pas; // décreménter l'intensité 
        else 
         x=0;
         
        analogWrite(PIN_LED1,x);
     
     } 
  }
}
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  

  //Serial.print(finger.fingerID); 
  //Serial.println(finger.confidence);

  return finger.fingerID; 
}

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define statePin 2 //Pin d'état, =1 si connexion BT
#define rxPin 3 //Pin Rx du HC05 --> Pin 3 de la Nano
#define txPin 4 //Pin Tx du HC05 --> Pin 4 de la Nano
#define keyPin 5 //Pin activation AT/data
#define hc05BR 38400 //Baudrate module BT
#define IRSensor 10
#define score 26

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

//Initilisation de la communication série avec le hc05
SoftwareSerial hc05(txPin, rxPin); //Tx | Rx pdv HC05
//Robot: 98d3,11,fcc42f
//Panier: 98D3,41,F62269

int compteur=-1, currStatus=1, prevStatus=1;

void setup() {
  pinMode(IRSensor, INPUT);
  pinMode(keyPin, OUTPUT);

  //Initialisation connexion série avec le module BT
  hc05.begin(hc05BR);

  //Initialisation de l'écran LCD 
  lcd.init(); 
  lcd.backlight();
  lcd.clear();       

  //Affichage écran d'attente connexion BT
  lcd.setCursor(0, 0); lcd.print("Waiting for");
  lcd.setCursor(0, 1); lcd.print("BT connection");

  //Attente connexion BT
  // while (digitalRead(statePin) !=1 ){}

  //Affichage message connexion BT réussie
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("BT connected");

  //Affichage nb cerises
  delay(2000);
  lcd.setCursor(0,0); lcd.print("Score cerises:");
  lcd.setCursor(0,1); lcd.print("Score total: "); lcd.setCursor(14,1); lcd.print(compteur+score);

  
}

void loop() {
  //status = 1 : no obstacle
  //status = 0 : obstacle
  //==> passage de 1 à 0 = détection de cerise
  currStatus = digitalRead(IRSensor);
  if (prevStatus==1 && currStatus==0)
  {
    compteur ++;
    //Màj nb cerises sur affichage LCD
    lcd.setCursor(14,0);  lcd.print(compteur);
  }
  prevStatus = currStatus;
}

#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define HEATER 7
#define DHTPIN 2 
#define DHTPIN1 4
#define DHTPIN2 5
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int led = 3;
const float epi= 0.5;
unsigned long timer;
bool triger =true;
bool triger2 =false;
unsigned long startTime;
void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(led, OUTPUT);
  pinMode(HEATER,OUTPUT);
  digitalWrite(HEATER,HIGH);
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  dht1.begin();
  dht2.begin();
  analogWrite(led, 128);
  startTime=millis();
}

void loop() {
  
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor 0!"));
    return;
  }

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  if (isnan(h1) || isnan(t1)) {
    Serial.println(F("Failed to read from DHT sensor 1!"));
    return;
  }

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  if (isnan(h2) || isnan(t2)) {
    Serial.println(F("Failed to read from DHT sensor 2!"));
    return;
  }
  ///control logic
  if(millis()-timer >20000){
    triger =true;
  }
  if (t>30)
  { 
    if(triger){
      triger =false;
      triger2=true;
    // increase fan speed
    analogWrite(led, 255);
    digitalWrite(HEATER,LOW);
    //turn off heater
    // initialize timeer
    timer =millis();
    }
  }else{
    if(triger){
      if(triger2){
        triger2=false;
        // reduce fan speed
        analogWrite(led, 128);
        digitalWrite(HEATER,HIGH);
      }

  }
  }
  if (millis()-startTime>6000)
  {
    if((((h2+h1)/2)-h)<=epi){
      digitalWrite(HEATER,LOW);
      analogWrite(led,0);
      lcd.clear();
      lcd.print("done!");
      //display
      while(1);
      //things are dry
    }
    //check moisture content
  }
  

  lcd.clear();
  lcd.print("temp");
  lcd.setCursor(6,0);
  lcd.print(t);
  lcd.setCursor(0,1);
  lcd.print("hum");
  lcd.setCursor(6,1);
  lcd.print(h);
  Serial.println("bottom sensor");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
 Serial.println("top sensor1");
  Serial.print(F("Humidity: "));
  Serial.print(h1);
  Serial.print(F("%  Temperature: "));
  Serial.print(t1);
  Serial.println(F("°C "));
Serial.println("top sensor2");
  Serial.print(F("Humidity: "));
  Serial.print(h2);
  Serial.print(F("%  Temperature: "));
  Serial.print(t2);
  Serial.println(F("°C "));
  

}

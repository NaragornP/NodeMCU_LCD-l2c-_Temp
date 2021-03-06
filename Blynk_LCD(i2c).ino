/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
//-------------------------------LCD
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h> //ประกาศ Library ของจอ I2C
#include <LiquidCrystal.h>
//----------------------------------
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "DHT.h"
#include <DHT_U.h>

#define DHTPIN            D7    
#define DHTTYPE           DHT22

//LiquidCrystal_I2C lcd(0x27, 16, 2);//--------------LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//NodeMCU
DHT_Unified dht(DHTPIN, DHTTYPE);
DHT dhtt(DHTPIN, DHTTYPE, 15);

char auth[] = "215767778f2b464d99b3bcde81ad1be7";

SimpleTimer timer;

void sendUptime()
{
   Blynk.virtualWrite(V5, millis() / 1000);
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V1, event.temperature);
   }
 
   
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V2, event.relative_humidity);
  }
}

void setup()
{

  Blynk.begin(auth, "Itsecckmutnb", "0824687893");
  //Wire.begin(D1, D2); // sda, scl
  dht.begin();
  lcd.begin(16,2);
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void loop()
{
  Blynk.run();
  timer.run();
  
  float t = dhtt.readTemperature();
  float h = dhtt.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Temp: |");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity:");
  lcd.print(h);
}

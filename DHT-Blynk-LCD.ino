// include the library code:
#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <DHT_U.h>

#define DHTPIN D7    
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
char auth[] = "215767778f2b464d99b3bcde81ad1be7";
SimpleTimer timer;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(D6, D5, D4, D3, D2, D1);

void sendUptime()
{
  
  Blynk.virtualWrite(V5, millis() / 1000);//D0
  sensors_event_t event;  
  Blynk.virtualWrite(V1, dht.readTemperature());
  Blynk.virtualWrite(V2, dht.readHumidity());
  
}

void setup() {
  
  Blynk.begin(auth, "Itsecckmutnb", "0824687893");//change follow wifi connect
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  dht.begin();
  timer.setInterval(5000L, sendUptime);
  
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("Humidity : ");
  lcd.print(h);

  // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.print(" C ");
  Blynk.run();
  timer.run();

}


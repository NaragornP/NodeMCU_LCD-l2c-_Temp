/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN            12    
#define DHTTYPE           DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

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
  Serial.begin(9600);
  Blynk.begin(auth, "Itsecckmutnb", "0824687893");

  dht.begin();
  
  // Setup a function to be called every second
  timer.setInterval(5000L, sendUptime);
}

void loop()
{
  Blynk.run();
  timer.run();
}

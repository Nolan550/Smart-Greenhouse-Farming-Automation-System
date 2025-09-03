#include <DHT.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define DHTPIN 2
#define DHTTYPE DHT22
#define SOIL_PIN A0
#define LDR_PIN A1


#define RELAY_PUMP 9
#define RELAY_BULB 10
#define RELAY_FAN 8


#define MOISTURE_THRESHOLD 500
#define TEMP_THRESHOLD 26
#define LIGHT_THRESHOLD 20

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PUMP, OUTPUT);
  pinMode(RELAY_BULB, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);

  digitalWrite(RELAY_PUMP, HIGH);  
  digitalWrite(RELAY_BULB, HIGH);
  digitalWrite(RELAY_FAN, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Smart Greenhouse");
  delay(2000);
  lcd.clear();
}

void loop() {

  int soil = analogRead(SOIL_PIN);
  int light = analogRead(LDR_PIN);
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (soil > MOISTURE_THRESHOLD) {
    digitalWrite(RELAY_PUMP, HIGH); 
  } else {
    digitalWrite(RELAY_PUMP, LOW); 
  }

  
  if (temp > TEMP_THRESHOLD) {
    digitalWrite(RELAY_FAN, HIGH); 
  } else {
    digitalWrite(RELAY_FAN, LOW); 
  }

  
  if (light < LIGHT_THRESHOLD) {
    digitalWrite(RELAY_BULB, HIGH); 
  } else {
    digitalWrite(RELAY_BULB, LOW); 
  }

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:"); lcd.print(temp, 1);
  lcd.print(" H:"); lcd.print(humidity, 0); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("FAN:");
  if (temp > TEMP_THRESHOLD) lcd.print("ON ");
  else lcd.print("OFF");
  delay(3000);

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil: "); lcd.print(soil);
  lcd.setCursor(0, 1);
  lcd.print("PUMP:");
  if (soil > MOISTURE_THRESHOLD) lcd.print("ON ");
  else lcd.print("OFF");
  delay(3000);

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Light: "); lcd.print(light);
  lcd.setCursor(0, 1);
  lcd.print("BULB:");
  if (light < LIGHT_THRESHOLD) lcd.print("ON ");
  else lcd.print("OFF");
  delay(3000);
}

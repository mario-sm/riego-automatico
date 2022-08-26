#include <DHT.h>
#include <LiquidCrystal.h>
// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
//Sensor analogicos de humedad de las plantas
#define LIGHT_SENSOR A0
//Sensores de humedad de las plantas : del 1 al 5
#define HUMIDITY_SENSOR_1 A1
#define HUMIDITY_SENSOR_2 A2
#define HUMIDITY_SENSOR_3 A3
#define HUMIDITY_SENSOR_4 A4
#define HUMIDITY_SENSOR_5 A5

const int hSensor1 = A0;
const int lightSensor= A1;
const float hMax =300;
const float hMin = 1023;
const float lMax = 1000;
const float lMin = 0;
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  lcd.print("AutoRiego 0.2");
  lcd.setCursor(0, 1);
  lcd.print("By Mario Suarez");

}
 
void loop() {
    // Esperamos 5 segundos entre medidas
  delay(5000);
  lcd.clear();
  int humidity = analogRead(HUMIDITY_SENSOR_1);
  int light = analogRead(LIGHT_SENSOR);
  
  float ambient_humidity = dht.readHumidity();
  float ambient_temperature = dht.readTemperature();

  float plant_humidity = CalculatePercentOfAnalogValueNotNormalized(hMax,hMin, humidity);
  float ambient_light = CalculatePercentOfAnalogValueNormalized(lMax,lMin, light);

  PrintOnLCD(ambient_temperature, ambient_humidity, ambient_light,plant_humidity);

}

float CalculatePercentOfAnalogValueNotNormalized(float max, float min, int value){
  float percent = (1-((value -max)/ (min-max)))*100;
  return percent;
}

float CalculatePercentOfAnalogValueNormalized(float max, float min, int value){
  float percent = (value / max)*100;
  return percent;
}

void PrintOnLCD(float ambient_temperature, float ambient_humidity, float ambient_light, float plant_humidity){
    lcd.print("T:");
  lcd.print(ambient_temperature);
  lcd.print("|H: ");
  lcd.print(ambient_humidity);
  lcd.print(" %\t");
  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print(ambient_light);
  lcd.print(" ");
  lcd.print("HP:");
  lcd.print(plant_humidity);
 
}

#include <DHT.h>
#include <LiquidCrystal.h>
#include <aREST.h>
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

const float hMax =300;
const float hMin = 1023;
const float lMax = 1000;
const float lMin = 0;

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
aREST rest= aREST(); 

float ambient_humidity = 0;
float ambient_temperature = 0;
float ambient_light = 0;
float plant_humidity_1 = 0;
int readData(String command);
void setup() {
  // Inicializamos comunicación serie
  Serial.begin(115200);
  // Comenzamos el sensor DHT
  dht.begin();
  lcd.begin(16, 2);
  // Escribimos el Mensaje en el LCD.
  lcd.print("AutoRiego 0.2");
  lcd.setCursor(0, 1);
  lcd.print("By Mario Suarez");

  rest.variable("ambient_temperature",&ambient_temperature);
  rest.variable("ambient_humidity",&ambient_humidity);
  rest.variable("ambient_light",&ambient_light);
  rest.variable("plant_humidity_1",&plant_humidity_1);

  rest.function("data",readData); 

  rest.set_id("1");
  rest.set_name("serial");
    
}
 
void loop() {

  rest.handle(Serial);
}

int readData(String command){
  
  lcd.clear();
  int humidity = analogRead(HUMIDITY_SENSOR_1);
  int light = analogRead(LIGHT_SENSOR);
  
  ambient_humidity = dht.readHumidity();
  ambient_temperature = dht.readTemperature();
  plant_humidity_1 = CalculatePercentOfAnalogValueNotNormalized(hMax,hMin, humidity);
  ambient_light = CalculatePercentOfAnalogValueNormalized(lMax,lMin, light);
  PrintOnLCD(ambient_temperature, ambient_humidity, ambient_light,plant_humidity_1);
  return 1;
}

float CalculatePercentOfAnalogValueNotNormalized(float max, float min, int value){
  float percent = (1-((value -max)/ (min-max)))*100;
  return percent;
}

float CalculatePercentOfAnalogValueNormalized(float max, float min, int value){
  float percent = (value / max)*100;
  return percent;
}

void PrintOnLCD(float ambient_temperature, float ambient_humidity, float ambient_light, float plant_humidity_1){
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
  lcd.print(plant_humidity_1);
 
}

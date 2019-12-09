#include <DHTesp.h>

DHTesp dht;

float humidity;
float temperature;

float humidityLowest = 101;
float humidityHighest = -1;
float temperatureLowest = 1000;
float temperatureHighest = -1000;

#define DHTpin 14 //D5 of NodeMCU is GPIO14

void setup(){
  Serial.begin(9600);
  Serial.println();
  String thisBoard= ARDUINO_BOARD;
  Serial.println(thisBoard);
  
  dht.setup(DHTpin, DHTesp::DHT11);

  pinMode(LED_BUILTIN, OUTPUT);
}
void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  digitalWrite(LED_BUILTIN, LOW); //LED On

  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  if (humidity < humidityLowest) humidityLowest = humidity;
  if (humidity > humidityHighest) humidityHighest = humidity;
  if (temperature < temperatureLowest) temperatureLowest = temperature;
  if (temperature > temperatureHighest) temperatureHighest = temperature;
  
  Serial.println("\nStatus\tHumidity\tTemperature\tHeatIndex\tHumidityInterval\tTemperatureInterval");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("%\t\t");
  Serial.print(temperature, 1);
  Serial.print("ºC\t\t");
  Serial.print(dht.computeHeatIndex(temperature, humidity, false), 1);
  Serial.print("ºC\t\t");
  Serial.print(humidityLowest, 1);
  Serial.print("% - ");
  Serial.print(humidityHighest, 1);
  Serial.print("%\t\t");
  Serial.print(temperatureLowest, 1);
  Serial.print("ºC - ");
  Serial.print(temperatureHighest, 1);
  Serial.print("ºC");
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH); //LED On

}

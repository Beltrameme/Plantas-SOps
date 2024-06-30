#include <DHT11.h> //libreria manejo sensor humedad
#include <EEPROM.h> //libreria manejo eeprom

int pinLuz = A5; //pin analogico 5 para los valores del fotoresistor
int memoriaEeprom = 0; 
DHT11 dht11(2); //indica al pin 2 como pin para el sensor DHT

void setup() {
  Serial.begin(9600);
}
byte valores[3];

void loop() {
  if (memoriaEeprom >= 252){
    memoriaEeprom = 0;
  }
  int temperatura = 0;
  int humedad = 0;
  int luzPuro = analogRead(pinLuz); //leer el valor analogico del pin 5
  float voltaje = luzPuro * (5.0/1023) * 1000;
  float resistencia = 10000 * ( voltaje / ( 5000.0 - voltaje) ); //ecuaciones sacadas de la datasheet del sensor, para conseguir el valor de la resistencia se hace un divisor resistivo entre los 5 volts que entrega el arduino y la resistencia interna del mismo
  int tempHum = dht11.readTemperatureHumidity(temperatura, humedad);
  valores[0] = temperatura;
  valores[1] = humedad;
  valores[2] = resistencia/1000;
  delay(500);
  Serial.write(valores,sizeof(valores));
  EEPROM.write(memoriaEeprom, valores); //la eeprom solo puede tener valores hasta 255, entonces bajo el valor, que esta entre 1000 y 80000
  memoriaEeprom++;

}

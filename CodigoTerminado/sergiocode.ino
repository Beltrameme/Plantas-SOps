#include <DHT11.h> //libreria manejo sensor humedad
#include <EEPROM.h> //libreria manejo eeprom

int pinLuz = A5; //pin analogico 5 para los valores del fotoresistor
int memoriaEeprom = 0; 
DHT11 dht11(2); //indica al pin 2 como pin para el sensor DHT

void setup() {
  Serial.begin(9600);
}

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
  if (tempHum == 0) {
        delay(500); //se ingresa un delay para que se pueda leer correctamente los valores del sensor
        Serial.write(temperatura); //mando la informacion por el puerto serie (usb en este caso) hacia la raspy
        EEPROM.write(memoriaEeprom, temperatura);
        memoriaEeprom++; //storeo valor en la eeprom
        delay(500);
        Serial.write(humedad);
        EEPROM.write(memoriaEeprom, humedad);
        memoriaEeprom++;
    } else {
        // mensaje de error
        Serial.println(DHT11::getErrorString(tempHum));
    }
  delay(500);
  Serial.write((int)resistencia/1000);
  EEPROM.write(memoriaEeprom, (resistencia/1000)); //la eeprom solo puede tener valores hasta 255, entonces bajo el valor, que esta entre 1000 y 80000
  memoriaEeprom++;

}

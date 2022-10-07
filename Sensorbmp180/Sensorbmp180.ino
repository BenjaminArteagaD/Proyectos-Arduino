/* 
se programa el sensor bmp180 para que lea e imprima en el monitor serial
temperatura y presión, y en base a eso imprimir igual la altitud 
*/

/*
Pines SDA y SCL Arduinos:          SDA   SCL
Uno, Redboard, Pro:                 A4    A5
Mega2560, Due:                      20    21
Leonardo:                            2     3
*/

#include <SFE_BMP180.h> // descargar librería aquí: https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/installing-the-arduino-library
#include <Wire.h>

SFE_BMP180 sensor; // creacion del objeto "sensor"

float P0 = 1013.0;//presion al nivel del mar, en mb

void setup()
   {
    Serial.begin(9600); //definicion de los baudios de la comunicacion serial
    Serial.println("REBOOT"); // reiniciar el sensor (para calibracion)
    if (sensor.begin())
    {
      Serial.println("BMP180 init success");
      Serial.println("Temperature  Pressure  Altitude");
    }
      
   else
     {
        Serial.println("BMP180 init fail\n\n");
        while(1); // Pause forever.
     }
   }
   
void loop() 
  {
    char status;  //definicion tipo de variable status
    double T,P,Alt; // definicion variables T, P y Alt


    status = sensor.startTemperature();// Empieza a leer la temperatura
    if (status != 0)
    {
      // si el sensor no está listo
      delay(status); // espera hasta que esté listo
      status = sensor.getTemperature(T);// Guarda la temperatura
      if (status != 0) 
      {
        status = sensor.startPressure(3); //Empezamos a medir la presion
        if (status != 0) // si el sensor no está listo
        {
          delay(status); // espera hasta que esté listo
          status = sensor.getPressure(P,T);// Guardamos la presion
          Alt = sensor.altitude(P,P0);
          //float dif = P-PresNivMar;
          if (status != 0)
          {
            Serial.print(T,2);  // imprime el valor de T en C
              Serial.print("        ");
            Serial.print(P,2);// imprime la presion en mb
              Serial.print("    ");

           
            Serial.println(Alt); //imprime la altitud en metros
          }
        }
        
      }
    }
    delay(300);
   
  }

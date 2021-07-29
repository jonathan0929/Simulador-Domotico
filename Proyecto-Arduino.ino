/**
* @file Proyecto-Arduino.ino
* @brief Gestion autonoma y mediante bluetooth de diversos sistemas en un hogar
*
*
* @author Jonathan Monge, Martha Espinoza, Luis Bonilla, Marcelo Redondo
* @date 28/07/2021
*/

#include "Proyecto-Arduino.h"

/**
* @brief Función setup encargada de definir el pinMode
*
*  Función setup encargada de definir el pinMode para cada uno de los pines seleccionados
*
* @param void
* @return void
*/
void setup()
{
  pinMode(sensorTemp, INPUT);
  pinMode(sensorIlum, INPUT);
  pinMode(releLuz, OUTPUT);
  pinMode(ilumAzul, OUTPUT);
  pinMode(ilumVerde, OUTPUT);
  pinMode(ilumRojo, OUTPUT);
  pinMode(iluExterior, OUTPUT);
  pinMode(sensorMov, INPUT);
  pinMode(alarmaMov, OUTPUT);
  pinMode(releVent, OUTPUT);
  Serial.begin(9600);
}

/**
* @brief Función encargada de detectar el sensor de movimiento
*
* Función que se encarga de leer la entrada digital del sensor de movimiento y activar la salida digital corespondiente a la alarma(alarmaMov)
*
* @param void
* @return void
*/

void deteccionMovimiento() {
  if (digitalRead(sensorMov) != 0) {
    digitalWrite(alarmaMov, HIGH);
  }
  else {
    digitalWrite(alarmaMov, LOW);
  }
}

/**
* @brief Función encargada de leer la entrada del sensor de temperatura y comvertirla en un valor de temperatura
*
* Función que se encarga de leer la entrada analogica correspondiente al sensor de temperatura y convertir los datos medidos a un valor de temperatura en grados Celcius  
*
* @param void
* @return variable temperatura que almacena la temperatura registrada
*/

int lecturaTemperatura() {
  int temperatura = 0;
  temperatura = -40 + 0.488155 * (analogRead(sensorTemp) - 20);

  return temperatura;
}

/**
* @brief Función que recive el valor de temperatura y con este controla el LED RGB y el releVent
*
* Función que se encarga de recibir el valor de temperatura y con este determinar el color del LED RGB así del encendido y apagado del releVent
* @param variable temperatura
* @return void
*/

void sistemaTemperatura(int temperatura) {
  
  if (temperatura < 30) {
    digitalWrite(ilumAzul, HIGH);
    digitalWrite(ilumVerde, LOW);
    digitalWrite(ilumRojo, LOW);
    digitalWrite(releVent, LOW);
  }
  if (temperatura >= 30 && temperatura < 110) {
    digitalWrite(ilumAzul, LOW);
    digitalWrite(ilumVerde, HIGH);
    digitalWrite(ilumRojo, LOW);
    digitalWrite(releVent, HIGH);
  }
  if (temperatura >= 110) {
    digitalWrite(ilumAzul, LOW);
    digitalWrite(ilumVerde, LOW);
    digitalWrite(ilumRojo, HIGH);
    digitalWrite(releVent, LOW);
  }
}

/**
* @brief Función principal
*
* Función princiapl o loop que se encarga de invocar a las demás funciones y llevara acabo la lógica del sistema de iluminación
* @param variable temperatura
* @return void
*/

void loop() {
  int estado = 0; //Lectura del puerto serie
  int lectura = 0; //lectura del sensor de temperatura
  lectura = lecturaTemperatura(); //invoca la funcion para leer temperatura y almacena el dato
  sistemaTemperatura(lectura); //
  deteccionMovimiento();
 
  if(Serial.available()>0) {  // Si está habilitado el puerto serie esta habilitado 
    estado = Serial.read();   // lectura de lo que llega por el puerto Serie
  } 
  if(estado == 'a') {  // Encendido del releLuz(Pin 13)
    digitalWrite(releLuz,HIGH);
  }
  if(estado == 'b' ) {  // Apagado del releLuz(Pin 13)
    digitalWrite(releLuz,LOW);
  }      

  if(analogRead(sensorIlum) >= 700) {  //Lectura sensor de temperatura y encendido
    digitalWrite(iluExterior, HIGH);
  }
  else if(analogRead(sensorIlum) < 700){  //Lectura sensor de temperatura y apagado
    digitalWrite(iluExterior, LOW);
  }
  if (estado == 'q') { //imprime en el monitor serie el valor de temperatura
    Serial.print(lectura);
    Serial.println("°C");
    delay(100);
    estado = 0;
  }
}

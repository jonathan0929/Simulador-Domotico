#ifndef Header_h
#define Header_h

#include "Arduino.h"

// Pines del arduino
#define sensorTemp A0
#define sensorIlum A1
#define sensorMov 4
#define releLuz 13
#define ilumAzul 12
#define ilumVerde 11
#define ilumRojo 10 
#define iluExterior 9
#define ledVent 8
#define alarmaMov 7
#define releVent 3

//Prototipos de funcion
void deteccionMovimiento();
void sistemaTemperatura(int temperatura);
int lecturaTemperatura();

#endif

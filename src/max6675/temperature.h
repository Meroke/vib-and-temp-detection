#include "max6675.h"

int thermoDO = 4;  // S0
int thermoCS = 5;  // CS
int thermoCLK = 6;  //SCK

float times = 0.1;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
float get_temperature()
{
    return thermocouple.readCelsius();
}
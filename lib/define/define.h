#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

// Controle
#define X_AXIS_PIN  34
#define Y_AXIS_PIN  35
#define SWITCH_PIN  25

// Display 
#define SDA_PIN  21
#define SCL_PIN  22

struct PacketDadosEnviados {
  uint8_t xAxisValue;
  uint8_t yAxisValue;
  bool switchPressed;
};

struct PacketTelemetria {
  int distanciaCM;
};

#endif
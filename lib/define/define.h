#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

// Mapeamento de pinos do controle
#define X_AXIS_PIN  34
#define Y_AXIS_PIN  35
#define SWITCH_PIN  25

//Pinos I2C do Display (OLED SSD1306 comum)
#define SDA_PIN  21
#define SCL_PIN  22

// Estrutura enviada para o carrinho
struct PacketDadosEnviados {
  uint8_t xAxisValue;
  uint8_t yAxisValue;
  bool switchPressed;
};

// Estrutura recebida pelo carrinho
struct PacketTelemetria {
  int distanciaCM;
};

#endif
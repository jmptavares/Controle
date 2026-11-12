#ifndef DEFINE_H
#define DEFINE_H

#include <Arduino.h>

//Pinagem do Joystick
#define X_AXIS_PIN  34
#define Y_AXIS_PIN  35
#define SWITCH_PIN  25

// Pinagem do Display
#define SDA_PIN  21 
#define SCL_PIN  22

// Comandos enviados pelo controle para o carrinho
struct PacketDadosEnviados {
  uint8_t xAxisValue; // Valor do eixo X convertido para o intervalo de controle
  uint8_t yAxisValue;  // Valor do eixo Y convertido para o intervalo de controle
  bool switchPressed; // Indica se o botão do joystick estiver pressionado
};

// Dados de telemetria recebidos do carrinho
struct PacketTelemetria {
  int distanciaCM; // Distância medida pelo carrinho
};

#endif
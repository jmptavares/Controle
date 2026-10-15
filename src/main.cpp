#include <Arduino.h>
#include "define.h"
#include "controle.h"
#include "comunicacao.h"
#include "display.h"

void setup() {
  Serial.begin(115200);

  inicializarDisplay();
  inicializarJoystick();
  inicializarComunicacaoControle();

  Serial.println("Controle iniciado.");
}

void loop() {
  // 1. Envia o joystick para o robô a cada 50ms
  static unsigned long ultimoEnvio = 0;
  if (millis() - ultimoEnvio >= 50) {
    ultimoEnvio = millis();

    PacketDadosEnviados dados = lerEstadoJoystick();
    enviarDadosRobo(dados);
  }

  // 2. Atualiza o display LCD 16x2 a cada 200ms
  static unsigned long ultimaAtualizacaoDisplay = 0;
  if (millis() - ultimaAtualizacaoDisplay >= 200) {
    ultimaAtualizacaoDisplay = millis();

    int distancia = obterUltimaDistanciaRecebida();
    atualizarDisplay(distancia, false); // Passa a distância lida para a tela
  }
}
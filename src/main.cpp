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
  static unsigned long ultimoEnvio = 0;
  if (millis() - ultimoEnvio >= 50) {
    ultimoEnvio = millis();

    PacketDadosEnviados dados = lerEstadoJoystick();
    enviarDadosRobo(dados);
  }

  static unsigned long ultimaAtualizacaoDisplay = 0;
  if (millis() - ultimaAtualizacaoDisplay >= 200) {
    ultimaAtualizacaoDisplay = millis();

    int distancia = obterUltimaDistanciaRecebida();
    atualizarDisplay(distancia, false);
  }
}
#include <Arduino.h>
#include "define.h"
#include "controle.h"
#include "comunicacao.h"
#include "display.h"

// Inicia o controle, o display e o ESP-NOW
void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial para depuração

  inicializarDisplay();
  inicializarJoystick();
  inicializarComunicacaoControle();

  Serial.println("Controle iniciado."); // Informa no monitor serial que o controle foi iniciado
}

void loop() { 
  // A cada 50 ms, envia os comandos atuais do joystick ao carrinho
  static unsigned long ultimoEnvio = 0;
  if (millis() - ultimoEnvio >= 50) {
    ultimoEnvio = millis();

    PacketDadosEnviados dados = lerEstadoJoystick(); 
    enviarDadosRobo(dados); 
  }

  // A cada 200 ms, atualiza o display com a distância recebida do carrinho
  static unsigned long ultimaAtualizacaoDisplay = 0;
  if (millis() - ultimaAtualizacaoDisplay >= 200) {
    ultimaAtualizacaoDisplay = millis();

    if (telemetriaDisponivel()) {
      int distancia = obterUltimaDistanciaRecebida();
      atualizarDisplay(distancia); // Atualiza o display com a distância recebida do carrinho
    } else {
      exibirMensagemSemSinal(); // Exibe mensagem de erro caso não haja telemetria disponível
    }
  }
}
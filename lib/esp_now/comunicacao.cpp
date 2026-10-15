#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h> // Biblioteca nativa do SDK
#include "comunicacao.h"
#include <esp_wifi.h>

static uint8_t macRobo[] = {0x1C, 0xC3, 0xAB, 0xD2, 0xD3, 0x80};

static int distanciaRecebidaRobo = 0;
static bool comunicacaoPronta = false;
static bool estadoEnvioConhecido = false;
static esp_now_send_status_t ultimoEstadoEnvio;
static unsigned long ultimoErroEnvioImpresso = 0;

// Callback para receber a telemetria do robô (v2.x)
static void aoReceberDados(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len < sizeof(PacketTelemetria)) return;

  PacketTelemetria telemetria;
  memcpy(&telemetria, incomingData, sizeof(telemetria));
  distanciaRecebidaRobo = telemetria.distanciaCM;
}

// Confirma a entrega do pacote ao nível MAC; não confirma que o programa
// receptor processou o comando.
static void aoEnviarDados(const uint8_t *mac, esp_now_send_status_t status) {
  if (!estadoEnvioConhecido || status != ultimoEstadoEnvio) {
    if (status == ESP_NOW_SEND_SUCCESS) {
      Serial.println("ESP-NOW: entrega confirmada pelo receptor.");
    } else {
      Serial.println("ESP-NOW: falha na entrega ao receptor.");
    }

    ultimoEstadoEnvio = status;
    estadoEnvioConhecido = true;
  }
}

void inicializarComunicacaoControle() {
  WiFi.mode(WIFI_STA);
   esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); //Configura o canal do WiFi para 1

  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar ESP-NOW no controle!");
    return;
  }

  if (esp_now_register_send_cb(aoEnviarDados) != ESP_OK) {
    Serial.println("Erro ao registrar callback de envio ESP-NOW!");
    return;
  }

  // Registra callback de recepção
  if (esp_now_register_recv_cb(aoReceberDados) != ESP_OK) {
    Serial.println("Erro ao registrar callback de recepcao ESP-NOW!");
    return;
  }

  // Registra o robô como peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, macRobo, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Erro ao adicionar o Robô como Peer!");
  } else {
    comunicacaoPronta = true;
    Serial.println("ESP-NOW inicializado; aguardando confirmacao do primeiro envio.");
  }
}

void enviarDadosRobo(PacketDadosEnviados dados) {
  if (!comunicacaoPronta) return;

  esp_err_t resultado = esp_now_send(macRobo, (uint8_t *)&dados, sizeof(dados));
  if (resultado != ESP_OK && millis() - ultimoErroEnvioImpresso >= 1000) {
    Serial.print("Erro ao enfileirar envio ESP-NOW. Codigo: ");
    Serial.println(static_cast<int>(resultado));
    ultimoErroEnvioImpresso = millis();
  }
}

int obterUltimaDistanciaRecebida() {
  return distanciaRecebidaRobo;
}
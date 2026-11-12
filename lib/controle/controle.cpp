#include "controle.h"

// Converte uma leitura analogica em um valor de eixo com zona morta
static int mapearComDeadband(int valor, bool inverter) { // Valor inicializado em 127 (representa o centro do joystick)
  int resultado = 127; 

  if (valor >= 2200) {
    resultado = map(valor, 2200, 4095, 127, 254); // Mapeia para o intervalo de 127 a 254
  } else if (valor <= 1800) {
    resultado = map(valor, 1800, 0, 127, 0); // Mapeia para o intervalo de 0 a 127
  } else {
    resultado = 127; // Zona morta central
  }

  return inverter ? (254 - resultado) : resultado; 
}

void inicializarJoystick() {
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Configura o botão do Joystick como entrada com resistor de pull-up
}

// Lê os eixos analógicos e o botão do joystick, retornando os comandos atuais do controle em uma estrutura PacketDadosEnviados
PacketDadosEnviados lerEstadoJoystick() { 
  PacketDadosEnviados dados;

  int xBruto = analogRead(X_AXIS_PIN); // Leitura bruta do eixo X
  dados.xAxisValue = mapearComDeadband(xBruto, false);
  int yBruto = analogRead(Y_AXIS_PIN); // Leitura bruta do eixo Y
  dados.yAxisValue = mapearComDeadband(yBruto, false); 

  // A cada 250 ms, imprime no monitor serial as leituras brutas e convertidas dos eixos
  static unsigned long ultimaImpressao = 0; 
  if (millis() - ultimaImpressao >= 250) {
    ultimaImpressao = millis();
    Serial.printf("X bruto=%d, mapeado=%u | Y bruto=%d, mapeado=%u\n",
                  xBruto, dados.xAxisValue, yBruto, dados.yAxisValue);
  }
  
  dados.switchPressed = (digitalRead(SWITCH_PIN) == LOW); // Leitura do estado do botão do joystick (pressionado = LOW, não pressionado = HIGH)

  return dados;
}
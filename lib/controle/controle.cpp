#include "controle.h"

static int mapearComDeadband(int valor, bool inverter) {
  int resultado = 127;

  if (valor >= 2200) {
    resultado = map(valor, 2200, 4095, 127, 254);
  } else if (valor <= 1800) {
    resultado = map(valor, 1800, 0, 127, 0);
  } else {
    resultado = 127; // Zona morta central
  }

  return inverter ? (254 - resultado) : resultado;
}

void inicializarJoystick() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

PacketDadosEnviados lerEstadoJoystick() {
  PacketDadosEnviados dados;

  int xBruto = analogRead(X_AXIS_PIN);
  dados.xAxisValue = mapearComDeadband(xBruto, false);
  int yBruto = analogRead(Y_AXIS_PIN);
  dados.yAxisValue = mapearComDeadband(yBruto, false);

  static unsigned long ultimaImpressao = 0;
  if (millis() - ultimaImpressao >= 250) {
    ultimaImpressao = millis();
    Serial.printf("X bruto=%d, mapeado=%u | Y bruto=%d, mapeado=%u\n",
                  xBruto, dados.xAxisValue, yBruto, dados.yAxisValue);
  }
  
  // Detecção do botão pressionado
  dados.switchPressed = (digitalRead(SWITCH_PIN) == LOW);

  return dados;
}
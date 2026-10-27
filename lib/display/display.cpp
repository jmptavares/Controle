#include "display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "define.h"

// Endereço I2C pro módulo PCF8574 (normalmente 0x27 ou 0x3F)
// 16 colunas x 2 linhas
static LiquidCrystal_I2C lcd(0x27, 16, 2);

void inicializarDisplay() {
  // Inicializa I2C nos pinos definidos no define.h
  Wire.begin(SDA_PIN, SCL_PIN);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Controle Robo");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(1000);
  lcd.clear();
}

void atualizarDisplay(int distanciaCM, bool modoProporcional) {
  lcd.setCursor(0, 0);
  lcd.print("Distância: ");
  if (modoProporcional) {
    lcd.print("Proporcional");
  } else {
    lcd.print("Simples     ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  if (distanciaCM >= 999 || distanciaCM <= 0) {
    lcd.print("--- cm   ");
  } else {
    // Imprime a distância
    lcd.print(distanciaCM);
    lcd.print(" cm    ");
  }
}

void exibirMensagemSemSinal() {
  lcd.setCursor(0, 0);
  lcd.print(" STATUS: ERRO   ");
  lcd.setCursor(0, 1);
  lcd.print(" Sem Conexao!   ");
}
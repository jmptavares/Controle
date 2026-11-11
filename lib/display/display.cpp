#include "display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "define.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2);

bool modoSimples = true; 

void inicializarDisplay() {
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

void atualizarDisplay(int distanciaCM, bool modoSimples) {
  lcd.setCursor(0, 0);
  lcd.print("Distancia: ");

  lcd.setCursor(0, 1);
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
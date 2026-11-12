#include "display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "define.h"

static LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereco I2C do display, 16 colunas e 2 linhas

// Inicializa o LCD e mostra a mensagem de início antes de limpar a tela
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

// Atualiza o LCD com a distancia indicada
void atualizarDisplay(int distanciaCM) {
  lcd.setCursor(0, 0);
  lcd.print("Distancia: ");

  lcd.setCursor(0, 1);
  if (distanciaCM >= 999 || distanciaCM <= 0) {
    lcd.print("--- cm   "); //Distancias menores ou iguais a zero e maiores ou iguais a 999 sao exibidas como indisponíveis
  } else {
    lcd.print(distanciaCM);
    lcd.print(" cm    ");
  }
}

// Mostra uma mensagem de erro de conexão no LCD caso o controle não esteja recebendo dados do carrinho
void exibirMensagemSemSinal() {
  lcd.setCursor(0, 0);
  lcd.print(" STATUS: ERRO   ");
  lcd.setCursor(0, 1);
  lcd.print(" Sem Conexao!   ");
}
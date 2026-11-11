#ifndef DISPLAY_H
#define DISPLAY_H
#include <Arduino.h>

void inicializarDisplay();
void atualizarDisplay(int distanciaCM, bool modoSimples);
void exibirMensagemSemSinal();

#endif
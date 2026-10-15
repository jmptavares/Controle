#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include <Arduino.h>
#include "define.h"

void inicializarComunicacaoControle();
void enviarDadosRobo(PacketDadosEnviados dados);
int obterUltimaDistanciaRecebida();

#endif
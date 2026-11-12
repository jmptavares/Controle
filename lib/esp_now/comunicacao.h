#ifndef COMUNICACAO_H
#define COMUNICACAO_H

#include "define.h"

void inicializarComunicacaoControle();
void enviarDadosRobo(PacketDadosEnviados dados);
int obterUltimaDistanciaRecebida();
bool telemetriaDisponivel();

#endif
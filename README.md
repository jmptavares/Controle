# Código do Controle — Projeto Trainee (PET Elétrica)

Código para o controle baseado em ESP32. Lê o joystick, envia seus comandos ao carrinho usando ESP-NOW e mostra no LCD a última distância recebida pelo carrinho.

## 1. Visão Geral e Funcionamento

O ESP32 funciona como a unidade transmissora do sistema. Os eixos do joystick são convertidos para valores entre `0` e `254`, com `127` representando o centro. O botão é lido como pressionado quando seu pino está em nível baixo.

O controle envia um pacote com os dois eixos e o estado do botão ao robô aproximadamente a cada 50 ms. Também recebe pacotes de telemetria contendo a distância em centímetros e atualiza o display aproximadamente a cada 200 ms com ela.

## 2. Arquitetura do Projeto

O código separa a parte principal dos módulos de controle, display, comunicação e definições da forma a seguir:

* **`src/main.cpp`:** Inicializa a serial e os módulos no `setup()`. No `loop()`, faz a leitura e o envio do joystick a cada 50 ms e a atualização do display a cada 200 ms.
* **`lib/define/` (`define.h`):** Declara os pinos do joystick e do display, além das estruturas `PacketDadosEnviados` (dados dos eixos e botão enviados para o carrinho) e `PacketTelemetria` (distância em centímetros recebida pelo carrinho).
* **`lib/controle/` (`controle.cpp` / `.h`):** Configura o botão do joystick com pull-up, lê os eixos analógicos e o botão, e converte as leituras dos eixos. Leituras acima de 1800 e abaixo de 2200 formam a zona morta central; a conversão usa o intervalo de 0 a 4095 e produz valores de 0 a 254.
* **`lib/esp_now/` (`comunicacao.cpp` / `.h`):** Configura o ESP32 em modo estação Wi-Fi, seleciona o canal 1 e inicializa o ESP-NOW. Quando a comunicação está pronta, envia ao MAC do carrinho os pacotes `PacketDadosEnviados` com os valores dos eixos e do botão, recebidos do módulo de controle. Também valida os pacotes de telemetria recebidos do carrinho, recebendo a última distância enviada por ele.
* **`lib/display/` (`display.cpp` / `.h`):** inicializa um LCD I2C de 16 colunas por 2 linhas, no endereço `0x27`, e mostra a distância recebida.

## 3. Fluxo de Execução

### Inicialização (`setup`)

1. Inicia a comunicação serial a 115200 baud.
2. Inicializa o barramento I2C e o display, mostra a mensagem inicial e limpa a tela.
3. Configura o pino do botão do joystick como entrada com pull-up.
4. Inicializa o Wi-Fi e o ESP-NOW, registra os callbacks e tenta adicionar o carrinho como peer.
5. Escreve uma mensagem de inicialização no monitor serial.

### Ciclo Principal (`loop`)

1. A cada 50 ms, lê os eixos e o botão do joystick e envia o pacote de comandos ao carrinho.
2. A cada 200 ms, consulta o estado da telemetria, exibe a mensagem de ausência de sinal se nenhum pacote válido foi recebido ou se não houver atualização por mais de 1 segundo. Caso contrário, mostra a última distância recebida no display.
3. A cada 250 ms aproximadamente, imprime a leitura do joystick no monitor serial com os valores brutos e convertidos dos eixos.
# Projeto: Controle de Matriz de LEDs WS2812 e LED RGB com Botões

## Descrição

Este projeto implementa o controle de uma matriz 5x5 de LEDs WS2812 e um LED RGB na placa BitDogLab, utilizando interrupções para manipulação dos botões. O sistema exibe números na matriz e permite sua alteração via botões físicos.

## Componentes Utilizados

- **Placa**: Raspberry Pi Pico (BitDogLab)
- **Matriz 5x5 de LEDs WS2812** – GPIO 7
- **LED RGB** – GPIOs 11 (verde), 12 (azul), 13 (vermelho)
- **Botão A** – GPIO 5 (incrementa o número exibido na matriz)
- **Botão B** – GPIO 6 (decrementa o número exibido na matriz)

## Funcionalidades

1. O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo.
2. O botão A incrementa o número exibido na matriz de LEDs a cada pressionamento.
3. O botão B decrementa o número exibido na matriz de LEDs a cada pressionamento.
4. A matriz WS2812 exibe números de **0 a 9** utilizando um padrão fixo (estilo digital).
5. O projeto utiliza **interrupções (IRQ)** para capturar eventos dos botões e evitar polling.
6. Implementação de **debouncing via software** para evitar leituras falsas dos botões.

## Requisitos Técnicos

- Utilização de **interrupções (IRQ)** para os botões, garantindo resposta rápida.
- Implementação de **debounce** via software para evitar leituras incorretas.
- Uso da **PIO (Programmable I/O)** para o controle eficiente dos LEDs WS2812.
- Manipulação de diferentes tipos de LEDs (RGB comum e WS2812).

## Estrutura do Código

O projeto é dividido nos seguintes arquivos:

- `main.c`: Código principal que gerencia os botões, LED RGB e matriz WS2812.
- `ws2812.c`: Controle dos LEDs WS2812, incluindo buffer de cores e atualização da matriz.
- `ws2812.pio`: Programa PIO para comunicação com a matriz WS2812.
- `interrupt.c`: Implementação de interrupções para os botões com debounce.
- `PollingBlink.c`: Código auxiliar de exemplo para controle de LEDs com polling.

## Como Compilar e Executar

1. **Configurar o ambiente de desenvolvimento**:
   - Instale o SDK do Raspberry Pi Pico.
   - Configure o `CMakeLists.txt` para incluir os arquivos do projeto.

2. **Compilar o código**:
   ```sh
   mkdir build
   cd build
   cmake ..
   make

3. **Gravar no Raspberry Pi Pico**:
    - Conecte a placa em modo de boot (BOOTSEL).
    -  Copie o arquivo .uf2 gerado para a unidade correspondente ao Pico.

4. **Executar e testar**:
    - Verifique a exibição dos números na matriz.
    - Teste os botões para incremento/decremento.
    - Observe o LED vermelho piscando corretamente.

#Vídeo de demonstração
[Simulação no BitDogLab](#)
#Autores

    Aline Machado – Implementação e testes
    Colaboradores – Comunidade BitDogLab e entusiastas de sistemas embarcados.
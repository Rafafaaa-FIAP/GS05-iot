<h1 align="center">Global Solution 05 - IOT</h1>

<hr/>

<p align="center">
  <a href="#pushpin-Introdução">Introdução</a>
  &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#bulb-Desafio">Desafio</a>
  &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#hammer_and_wrench-Tecnologias-e-Ferramentas">Tecnologias e Ferramentas</a>
  &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#floppy_disk-Solução">Solução</a>
  &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#gear-Como-Utilizar">Como Utilizar</a>
  &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#technologist-Integrantes">Integrantes</a>
</p>

<hr/>

## :pushpin: Introdução
O futuro do trabalho já começou. Avanços tecnológicos, como a robótica, a automação e a Internet das Coisas, estão transformando profissões, criando novas oportunidades e também desafios inéditos. Mudanças sociais, econômicas e ambientais estão redesenhando como vivemos, trabalhamos e aprendemos. Este projeto faz parte de uma proposta interdisciplinar e deve estar alinhado à ideia central desenvolvida pelo grupo nas demais disciplinas.

A aplicação prática com ESP32 ou Arduino representa a materialização tecnológica dessa ideia, demonstrando como o uso de inovação, sensores, atuadores e comunicação IoT (MQTT e/ou HTTP) pode contribuir para o tema 'O Futuro do Trabalho'.

## :bulb: Desafio
Desenvolver uma solução inovadora com ESP32 ou Arduino simulada no ambiente Wokwi ou presencial, que demonstre na prática como a tecnologia pode transformar o trabalho, a educação e o bem-estar humano em um futuro cada vez mais digital e automatizado.
Temas que podem ser explorados:

- Saúde e bem-estar no trabalho: monitoramento ambiental, pausas inteligentes, controle de fadiga ou ergonomia.
- Educação e requalificação profissional: sistemas de aprendizado automatizado, feedback em tempo real e gamificação de habilidades.
- Ambientes híbridos e imersivos: integração de IoT em espaços de trabalho remotos e colaborativos.
- Inclusão produtiva: soluções acessíveis para pessoas com deficiência, idosos ou comunidades de difícil acesso.
- Economia verde e sustentabilidade: automação que reduz o consumo energético e o impacto ambiental.

## :hammer_and_wrench: Tecnologias e Ferramentas
Este projeto utilizou as seguintes tecnologias e ferramentas:
* [Wokwi](https://wokwi.com/)
* [Node-RED](https://nodered.org/)
* [C++](https://pt.wikipedia.org/wiki/C%2B%2B)

## :floppy_disk: Solução
### Circuito
Criação de uma estação de trabalho inteligente que monitore o ambiente (temperatura, umidade e iluminação) e o tempo que o trabalhador passa sentado, enviando alertas automáticos e dados IoT para um dashboard via protocolo MQTT.

Essa estação visa melhorar o bem-estar, saúde e produtividade, representando como a automação e a IoT podem transformar o futuro do trabalho.

#### Componentes
- ESP32: microcontrolador principal com Wi-Fi integrado.
- Sensor DHT22: mede temperatura e umidade.
- Sensor LDR: mede luminosidade (ergonomia visual).
- Sensor Ultrassônico: detecta presença da pessoa (para medir tempo sentado).
- LED (verde/vermelho): indica boas/más condições de trabalho.
- Buzzer: emite alerta sonoro quando o trabalhador ultrapassa tempo limite sem pausa.

<img src="https://github.com/Rafafaaa-FIAP/GS05-iot/blob/main/images/circuit.png" alt="circuit" width="500" />

### Funcionamento da Lógica
- O sistema lê os dados dos sensores a cada poucos segundos.
- Se:
  - Temperatura > 28°C → ambiente quente.
  - Umidade < 40% → ar seco.
  - Luminosidade < limiar → iluminação ruim.
  - Pessoa detectada continuamente por > 1h → emitir alerta de pausa.
- O ESP32:
  - Envia todos os dados via MQTT (tópico: AllData).
  - Acende LED verde se tudo estiver bom; vermelho se alguma condição ruim.
  - Aciona buzzer quando a pausa for necessária.

### Fluxo
<img src="https://github.com/Rafafaaa-FIAP/GS05-iot/blob/main/images/flow.png" alt="circuit 5" width="500" />
<h6>Acesse o JSON para importação no Node-RED clicando <a href="https://github.com/Rafafaaa-FIAP/GS05-iot/blob/main/flows.json">aqui</a>.</h6>

### Dashboard
<img src="https://github.com/Rafafaaa-FIAP/GS05-iot/blob/main/images/dashboard.png" alt="circuit 5" width="500" />

## :gear: Como Utilizar
1. Baixar o projeto e abri-lo no VSCode;
2. Instalar a extensão PlatformIO e realizar o build do projeto;
3. Iniciar a simulação do arquivo diagram.json;
4. Instalar o Node-RED;
5. Iniciar o Node-RED no computador;
6. Instalar o pacote @flowfuse/node-red-dashboard no Node-RED;
7. Importar o [fluxo](https://github.com/Rafafaaa-FIAP/GS05-iot/blob/main/flows.json) no Node-RED no computador e fazer o deploy;
8. O dashboard ficará disponível em [http://127.0.0.1:1880/dashboard/dashboard](http://127.0.0.1:1880/dashboard/dashboard).

## :technologist: Integrantes
* RM553377 - Enzo Rodrigues
* RM553266 - Hugo Santos
* RM553521 - Rafael Cristofali

# Jogo da Velha

## Sobre

## Sumário
- [Softwares e Periféricos Utilizados](#softwares-e-periféricos-utilizados)
    - [Kit de desenvolvimento DE1 SoC](#kit-de-desenvolvimento-de1-soc)
    - [Linguagem C](#linguagem-c)
    - [Compilador GCC](#compilador-gcc)
    - [Editor de texto VSCode](#editor-de-texto-vscode)
    - [Mouse](#mouse)
    - [Push Buttons](#push-buttons)

- [Arquitetura da DE1 SoC](#arquitetura-da-de1soc)
- [Execução](#execução)
- [Lógica do Jogo](#lógica-do-jogo)
- [Cenários de Testes](#cenários-de-testes)
- [Conclusão](#conclusão)
- [Referências](#referências)

## Equipe
- Jeferson Almeida da Silva Ribeiro
- Letícia Teixeira Ribeiro dos Santos
- Vitória Tanan dos Santos

## Softwares e Periféricos Utilizados

### Kit de desenvolvimento DE1-SoC

<p align="justify">
A placa de desenvolvimento DE1-SoC é uma plataforma baseada no chip Altera Cyclone V SoC, que integra um processador ARM Cortex-A9 dual-core com uma FPGA da família Cyclone V. A DE1-SoC possui uma ampla variedade de periféricos e interfaces, incluindo:
</p>

- Interfaces de entrada/saída;
- Conexões de áudio de vídeo;
- Interface USB;
- Conexões Ethernet;
- LEDS, chaves e botões, entre outros.

<p align="center">
    <img src="https://github.com/leticiaribeiro7/jogo-da-velha/blob/main/Imagens/placa.jpg" alt="Placa DE1-SoC" width="500">
    <br>
    Figura 1. Esta é a placa de desenvolvimento DE1-SoC.
</p>

<p align="justify">
Os periféricos utilizados na construção do projeto com a DE1-SoC incluíram entradas USB e botões (Figura 2). A placa possui 2 portas USB 2.0 tipo A, cada uma equipada com um controlador SMSC USB3300 e um controlador de hub de 2 portas. O dispositivo USB3300, alojado em um pacote QFN de 32 pinos, é conectado ao controlador de hub SMSC USB2512B e suporta a interface UTMI+ Low Pin Interface (ULPI), permitindo a comunicação com o controlador USB 2.0 no HPS.
</p>
<p align="justify">
A placa DE1-Soc possui 4 botões para interação denominados, KEY0, KEY1, KEY2 e KEY3. Ao pressionar um botão específico, o seu estado é registrado em um registrador de dados, onde o bit correspondente é ativado para 1, caso contrário, é definido como 0.
</p>

<p align="center">
    <img src="https://github.com/leticiaribeiro7/jogo-da-velha/blob/main/Imagens/perifericos_placa.png" alt="Periféricos Utilizados" width="600">
    <br>
    Figura 2. Periféricos da DE1-SoC utilizados.
</p>

### Mouse
<p align="justify">
Foi utilizado um mouse como dispositivo periférico que serve de entrada para o jogador selecionar a posição no tabuleiro do jogo e realizar a jogada. Para tal, o mouse é conectado na [DE1-SoC](#kit-de-desenvolvimento-de1-soc) através de uma de suas entradas USB.  (add foto da placa com mouse)
</p>

### Push Buttons
Os push buttons, também conhecidos como botões de pressão, são dispositivos de entrada que permitem aos usuários interagir com sistemas eletrônicos ou dispositivos por meio de pressão física. Sua escolha se justifica pela capacidade de fornecer uma interface física intuitiva, facilitando a interação dos usuários com dispositivos eletrônicos. Isso permite operações simples e diretas, melhorando a experiência do usuário.

No projeto em questão, os botões foram utilizados para iniciar e encerrar um jogo. O botão KEY0 é responsável por iniciar o jogo quando pressionado, enquanto o botão KEY1 encerra o jogo quando pressionado.

Para manipular e captar os dados dos botões, foi utilizado o driver KEY disponível na DE1-SoC-UP, a distribuição Linux da placa. Isso proporciona uma maneira eficaz de integrar a funcionalidade dos botões ao sistema, garantindo uma interação fluida e eficiente.

### Linguagem C

<p align="justify">
A linguagem C é uma linguagem de programação de alto nível que foi criada nos anos 70 com o propósito inicial de desenvolver sistemas operacionais. Nos dias atuais, ela permanece bastante popular, sendo amplamente utilizada em sistemas embarcados, no Kernel do Linux, aleḿ de também ter servido de influência para criação de outras linguagens como C#, C++ e Java. No projeto, essa linguagem foi utilizada para desenvolver o código fonte em conjunto com o compilador GCC para execução do programa.
</p>

### Compilador GCC
GCC é sigla para GNU Compiler Collection

### Editor de texto VSCode
<p align="justify">
O Visual Studio Code é um editor de texto bastante popular que tem suporte para Windows, Linux e MacOS. Neste projeto, o VSCode foi utilizado para fins de edição do código em linguagem C, usufruindo do realce de sintaxe que o programa propociona.
</p>

## Arquitetura da DE1-SoC


## Execução

Para executar o jogo, basta clonar este repositório e na pasta raiz do projeto os seguintes comandos:

```bash
make all
sudo ./jogo.exe
```

## Funcionamento do Jogo

Para possibilitar o funcionamento do jogo utilizando o mouse, foi utilizado o arquivo **/dev/input/mice** disponível em distribuições Linux. Esse arquivo trata-se de um driver que detecta os dados do mouse, como cliques dos botões e movimentação. Portanto, ao abrir este arquivo em modo leitura no código fonte foi possível criar uma lógica de verificação das coordenadas X e Y do mouse e limitá-las ao tamanho desejado.
Além disso, para início e finalização do jogo foi utilizado dois botões da placa de desenvolvimento, o KEY0 para início e o KEY1 para finalizar. Para implementar essa funcionalidade, foi utilizado o driver KEY disponível na DE1-SoC-UP, a distribuição Linux da placa. Este driver proporciona comunicação com os push buttons, possuindo função de leitura dos estados dos botões para identificar qual está pressionado no momento. A importação no código fonte é feita através dessa linha:
```bash
"include <intelfpgaup/KEY>"
```

Em relação à mudança das coordenadas, o movimento funciona da seguinte forma:

#### Coordenada X
- Movimento para a esquerda: O valor de X diminui
- Movimento para a direita: O valor de X aumenta

#### Coordenada Y
- Movimento para cima: O valor de Y diminui
- Movimento para baixo: O valor de Y aumenta

#### Casas do tabuleiro
As jogadas propriamente ditas são executadas através de uma lógica de "casas", o tabuleiro é subdividido em 9 espaços em que os jogadores podem escolher (caso o outro jogador não tenha jogado naquele espaço) e finalizar a jogada com um clique do mouse no botão esquerdo. A todo tempo durante a execução, é mostrado em qual casa o jogador se encontra, e vai mudando conforme o mouse é movimentado.
Cada casa possui 50 unidades de tamanho, o valor foi decidido de acordo à sensibilidade envolvida na mudança de uma casa para outra.

## Cenários de Testes
- vitoria
- empate
- iniciar jogo
- sair do jogo


## Conclusão

## Referências




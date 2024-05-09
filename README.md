# Jogo da Velha

## Sobre

## Sumário
- [Softwares e Periféricos Utilizados](#softwares-e-periféricos-utilizados)
    - [Kit de desenvolvimento DE1 SoC](#kit-de-desenvolvimento-de1-soc)
    - [Linguagem C](#linguagem-c)
    - [Compilador GCC](#compilador-gcc)
    - [Editor de texto VSCode](#editor-de-texto-vscode)
    - [Mouse](#mouse)
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
    <img src="https://github.com/leticiaribeiro7/jogo-da-velha/blob/main/Imagens/placa.jpg" alt="Placa DE1-SoC" width="400">
    <br>
    Figura 1. Esta é a placa de desenvolvimento DE1-SoC.
</p>


### Linguagem C
--
### Compilador GCC
--
### Editor de texto VSCode

O Visual Studio Code é um editor de texto bastante popular que tem suporte para Windows, Linux e MacOS. Neste projeto, o VSCode foi utilizado para fins de edição do código em linguagem C, usufruindo do realce de sintaxe que o programa propociona.

### Mouse

Foi utilizado um mouse como dispositivo periférico que serve de entrada para o jogador selecionar a posição no tabuleiro do jogo e realizar a jogada. Para tal, o mouse é conectado na [DE1-SoC](#kit-de-desenvolvimento-de1-soc) através de uma de suas entradas USB.  (add foto da placa com mouse)


## Arquitetura da De1SoC



## Execução

Para executar o jogo, basta clonar este repositório e na pasta raiz do projeto os seguintes comandos:

```bash
make all
sudo ./jogo.exe
```

## Funcionamento do Jogo

Para possibilitar o funcionamento do jogo utilizando o mouse, foi utilizado o arquivo **/dev/input/mice** disponível em distribuições Linux. Esse arquivo trata-se de um driver que detecta os dados do mouse, como cliques dos botões e movimentação. Portanto, ao abrir este arquivo em modo leitura no código fonte foi possível criar uma lógica de verificação das coordenadas X e Y do mouse e limitando-as ao tamanho desejado.

#### Coordenada X
- Movimento para a esquerda: O valor de X diminui
- Movimento para a direita: O valor de X aumenta

#### Coordenada Y
- Movimento para cima: O valor de Y diminui
- Movimento para baixo: O valor de Y aumenta

#### Casas do tabuleiro
 --


## Cenários de Testes
- vitoria
- empate
- iniciar jogo
- sair do jogo


## Conclusão

## Referências

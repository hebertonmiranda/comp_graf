#### Nome: Heberton Miranda Rodrigues da Silva  	
#### R.A.: 21023713
#### Professor: Harlen Costa Batagelo

# Computação Gráfica – Atividade 1

## Enunciado
Esta tarefa consiste em desenvolver uma aplicação que use a plataforma ABCg e explore a interface gráfica da biblioteca Dear ImGui. O objetivo é mostrar a capacidade de usar o ambiente de desenvolvimento da disciplina para produzir uma aplicação original (jogo, simulador, utilitário, etc).

## Descrição do jogo
Foi desenvolvido em C++ e utilizando a API do OpenGL o `Simon Game`, que é um jogo clássico onde há 4 botões com 4 cores (vermelho, verde, azul e amarelo) e a cada rodada uma cor acende, formando uma sequência de cores a ser memorizada.

## Instruções do jogo
 1. Clique no botão `Start!` para começar a jogar;
 2. Em `Current level` você verá quantas cores você deverá acertar na rodada. A cada nova rodada mais uma cor é adicionada à sequência;
 3. Em `Current turn`, verá quantas cores da sequência você já marcou;
 4. Ao final do turno, clique em `Check!` para verificar se você acertou a sequência ou não!

# Descrição técnica
Para a elaboração da atividade foi utilizado a linguagem C++ juntamente com as bibliotecas da própria linguagem e as bibliotecas `ABCg` e `ImGui` (https://github.com/ocornut/imgui). Para a renderização gráfica foi utilizada a API `OpenGL` (https://www.opengl.org/). Foram utilizadas as seguintes técnicas:

 - `main.cpp`– Foi criada uma janela usando a API `OpenGL`, fixando altura e comprimento e removendo os *widgets* que mostram *FPS* e botão de tela cheia;

 - `openglwindow.hpp`– A classe da janela utiliza a biblioteca `ABCg` onde são inicializados o `OpenGL`, a janela em si e os *widgets* da janela. O fundo da janela foi colorido de preto;

 - `openglwindow.cpp`– Foram utilizadas as *features* da biblioteca `ABCg` para inicializar a janela e os *widgets*. Para os *widgets* foi utilizado o `ImGui` para:

	 - Configurar as *flags* da janela, redimensionar a janela, exibir os textos fixados, criar as colunas e separadores para os botões coloridos (que também foram criados usando`ImGui`), além das *flags* dos botões e os botões comuns (não coloridos);
	- As ações dos botões também foram feitas com funções do `ImGui`.
	
Para toda a dinâmica do jogo foram criadas variáveis estáticas, vetores, estruturas condicionais e de repetição em C++. Para o tamanho dos botões foi necessário especificar os tamanhos com um *`ImVec2`*.

Para as cores dos botões coloridos, foram criados 4 vetores com 2 *`ImVec4`* cada armazenando os valores das cores mais escuras (botão não apertado) e das cores mais claras (botão apertado), dando a ideia de acendimento de luz, interagindo melhor com o jogador.

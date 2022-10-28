#### Nome: Heberton Miranda Rodrigues da Silva  	
#### R.A.: 21023713
#### Professor: Harlen Costa Batagelo

# Computação Gráfica – Atividade 2

## Enunciado
Esta tarefa consiste em desenvolver uma aplicação que mostre gráficos 2D com primitivas do OpenGL e permita a interação com o teclado ou mouse. A aplicação deve necessariamente usar a biblioteca ABCg e renderizar gráficos com o pipeline do OpenGL usando shaders.

## Descrição do jogo
Foi desenvolvido em C++ e utilizando a API do OpenGL o `Brick Breaker Game`, que é um jogo clássico onde há vários blocos na parte superior e é necessário quebrá-los com uma bolinha, sem deixar a bolinha cair!

Jogo on-line disponível [aqui](https://hebertonmiranda.github.io/comp_graf/Atividade_2/public/)!

## Instruções do jogo
O jogo inicia automaticamente e você deve utilizar as teclas $\leftarrow$ e $\rightarrow$ para movimentar a *prancha* de forma a não deixar que a bolinha caia e para rebatê-la, para que ela quebre todos os blocos.

# Descrição técnica
Para a elaboração da atividade foi utilizada a linguagem C++ juntamente com as bibliotecas da própria linguagem, o framework `ABCg` (https://github.com/hbatagelo/abcg) e a biblioteca `ImGui` (https://github.com/ocornut/imgui). Para a renderização gráfica foi utilizada a API `OpenGL` (https://www.opengl.org/). Foram utilizadas as seguintes técnicas:

 - `main.cpp`– Foi criada uma janela usando a API `OpenGL`, fixando altura e comprimento, além de remover as opções de mostrar FPS e botão de tela cheia;

 - `ball.hpp`– Classe com os métodos e atributos utilizados para renderizar a bolinha no jogo;

 - `ball.cpp`– 

 - `brick.hpp`– Classe com os métodos e atributos utilizados para renderizar os blocos do jogo que serão quebrados;

 - `brick.cpp`– 

 - `gamedata.hpp`– Classe com a definição da estrutura do jogo, os estados do jogo e as teclas de entrada;

 - `paddle.hpp`– Classe com os métodos e atributos utilizados para renderizar a *prancha* no jogo;

 - `paddle.cpp`– 
  
 - `window.hpp`– Classe com os métodos e atributos utilizados para renderizar a janela do jogo;

 - `window.cpp`– 
	
 - `assets\Inconsolata-Medium.ttf`– Fonte utilizada para anunciar a vitória no jogo (*\*You Win!\**) ou a derrota (*Game Over!*);

 - `assets\objects.frag`– 

 - `assets\objects.vert`– 
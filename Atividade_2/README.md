#### Nome: Heberton Miranda Rodrigues da Silva  	
#### R.A.: 21023713
#### Professor: Harlen Costa Batagelo

# Computação Gráfica – Atividade 2

## Enunciado
Esta tarefa consiste em desenvolver uma aplicação que mostre gráficos 2D com primitivas do OpenGL e permita a interação com o teclado ou mouse. A aplicação deve necessariamente usar a biblioteca ABCg e renderizar gráficos com o pipeline do OpenGL usando shaders.

## Descrição do jogo
Foi desenvolvido em C++ e utilizando a API do OpenGL o `Brick Breaker Game`, que é um jogo clássico onde há vários blocos na parte superior e é necessário quebrá-los com uma bolinha, sem deixar a bolinha cair!

Jogo on-line disponível <a href="https://hebertonmiranda.github.io/comp_graf/Atividade_2/public/" target="_blank" rel="noopener noreferrer">aqui</a>!

## Instruções do jogo
O jogo inicia automaticamente e você deve utilizar as teclas $\leftarrow$ e $\rightarrow$ para movimentar a *prancha* de forma a não deixar que a bolinha caia e para rebatê-la, para que ela quebre todos os blocos.

# Descrição técnica
Para a elaboração da atividade foi utilizada a linguagem C++ juntamente com as bibliotecas da própria linguagem, o framework `ABCg` (https://github.com/hbatagelo/abcg) e a biblioteca `ImGui` (https://github.com/ocornut/imgui). Para a renderização gráfica foi utilizada a API `OpenGL` (https://www.opengl.org/). Foram utilizadas as seguintes técnicas:

 - `main.cpp`– Foi criada uma janela usando a API `OpenGL`, fixando altura e comprimento, além de remover as opções de mostrar FPS e botão de tela cheia;

 - `ball.hpp`– Classe com os métodos e atributos utilizados para renderizar a bolinha no jogo;

 - `ball.cpp`– Ao criar a bolinha, é estabelecido randomicamente se ela irá para a esquerda ou para a direita no primeiro movimento e são criados os VAO's e VBO's para o armazenamento dos atributos da bolinha, como a posição dela ao longo do jogo. A renderização da bolinha é feita no formato `GL_TRIANGLE_FAN`. No método `update` foram criadas funções para as direções da bolinha, para que ela percorra a tela e para as mudanças de direção quando ela bate nas laterais, "teto" e também nos blocos.

 - `brick.hpp`– Classe com os métodos e atributos utilizados para renderizar os blocos do jogo que serão quebrados;

 - `brick.cpp`– São criados 54 blocos em 6 colunas com 9 blocos cada igualmente espaçados para melhorar a dinâmica do jogo. São criados os VAO's, VBO's e EBO's para o armazenamento dos atributos dos blocos, onde os blocos são retangulares e constituídos de 2 triângulos gerados no formato `GL_TRIANGLE_STRIP`. Os blocos foram normalizados e coloridos a cada linha.

 - `gamedata.hpp`– Classe com a definição da estrutura do jogo, os estados do jogo e as teclas de entrada;

 - `paddle.hpp`– Classe com os métodos e atributos utilizados para renderizar a *prancha* no jogo;

 - `paddle.cpp`– Construção similar ao `brick.cpp`, onde basicamente a *prancha* é um bloco porém um pouco maior e fixo na parte inferior da tela. Também não é colorido como os blocos (possui cor branca) e em `update` possui a configuração de movimento conforme os inputs das teclas $\leftarrow$ e $\rightarrow$.
  
 - `window.hpp`– Classe com os métodos e atributos utilizados para renderizar a janela do jogo;

 - `window.cpp`– Configurado os inputs das teclas $\leftarrow$ e $\rightarrow$ do teclado, criado o objeto para chamar os shaders da bolinha, dos blocos e da *prancha* e definido o fundo cinza da tela. Em seguida, são definidas as regras do jogo:
   - O jogo é perdido se a bolinha estiver abaixo da *prancha*;
   - Se não sobrarem mais blocos, então o jogo foi vencido;
   - Se a bolinha possui coordenadas "dentro" de um bloco, então calcula-se a distância da bolinha para as bordas do bloco para estabelecer de qual lado a bolinha bateu no bloco, para alterar sua direção. Em seguida, o bloco é removido da tela.
	
 - `assets\Inconsolata-Medium.ttf`– Fonte utilizada para anunciar a vitória no jogo (*\*You Win!\**) ou a derrota (*Game Over!*);

 - `assets\objects.frag`– *Fragment shader*, é o objeto que possui as propriedades da bolinha, dos blocos e da *prancha*, programa como os pixels são exibidos na tela, onde a cor de entrada é a mesma cor da saída.

 - `assets\objects.vert`– *Vertex shader*, é o objeto que possui as propriedades de vértices da bolinha, dos blocos e da *prancha*.
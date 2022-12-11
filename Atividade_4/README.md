#### Nome: Heberton Miranda Rodrigues da Silva  	
#### R.A.: 21023713
#### Professor: Harlen Costa Batagelo

# Computação Gráfica – Atividade 4

## Enunciado
A tarefa consiste em desenvolver uma aplicação que mostre gráficos 3D com primitivas do OpenGL (como na atividade 3), mas que utilize shaders de iluminação e texturização. Além disso, a aplicação deve ser interativa: o usuário deve ser capaz de interagir com os gráficos e animações através do mouse e/ou teclado (pode ser através da ImGui). Assim como nas tarefas anteriores, a aplicação deve necessariamente usar a biblioteca ABCg.

## Descrição da aplicação
Foi desenvolvido em C++ e utilizando a API do OpenGL o `Earth Visualization`, que é um visualizador 3D do planeta Terra. Ele possui dois modelos de texturas para visualizar a Terra: de dia e de noite.

O visualizador está disponível <a href="https://hebertonmiranda.github.io/comp_graf/Atividade_4/public/" target="_blank" rel="noopener noreferrer">aqui</a>!

## Controles da aplicação
Basta utilizar os movimentos do *mouse* para clicar com o botão direito e arrastar para rotacionar o planeta. O clique com o botão esquerdo altera o ângulo de iluminação, que inicialmente é como uma luz vista de cima. Há um slider onde é possível alterar a quantidade de triângulos renderizados no objeto do planeta Terra.

No mais, há o *widget* para ver a quantidade de *frames* por segundo e um botão para deixar a aplicação em tela cheia, melhorando a imersão proporcionada pela aplicação.

# Descrição técnica
Para a elaboração da atividade foi utilizada a linguagem C++ juntamente com as bibliotecas da própria linguagem, o framework `ABCg` (https://github.com/hbatagelo/abcg) e a biblioteca `ImGui` (https://github.com/ocornut/imgui). Para a renderização gráfica foi utilizada a API `OpenGL` (https://www.opengl.org/). Foram utilizadas as seguintes técnicas:

 - `main.cpp`– Foi criada uma janela usando a API `OpenGL`, fixando altura e comprimento em 1280x720px, além de manter as opções de mostrar FPS e botão de tela cheia;

 - `model.hpp`– Classe com os métodos e atributos utilizados para renderizar o objeto principal da visualização, que é o planeta Terra.

 - `model.cpp`– São criados os VAO's, VBO's e EBO's para o armazenamento dos atributos do planeta Terra. Os atributos para fazer a renderização como vértices e texturas, são obtidos através de arquivos `OBJ` e `mtl`. O planeta também possui suas coordenadas normalizadas e é colocado para ser exibido no centro da visualização.

 - `trackball.hpp`– Classe com os métodos e atributos das funções de utilização do *mouse*;

 - `trackball.cpp`– Configurações dos movimentos do *mouse* com relação ao clique com os botões esquerdo e direito, além do *scroll*.
  
 - `window.hpp`– Classe com os métodos e atributos utilizados para renderizar os objetos na tela. Aqui, foram estabelecidas uma função para sempre criar 500 estrelas de fundo na tela além da chamada de um construtor para cada modelo (Terra e estrelas);

 - `window.cpp`– Foram feitas as configurações gerais da janela:
   - Foram configuradas as ações dos eventos de *mouse*. Durante a criação, foi estabelecido o fundo preto e ativação do *face culling* para otimizar a renderização dos triângulos, não renderizando triângulos que não estão visíveis (como as estrelas atrás da Terra);
    - São instanciados 2 objetos, sendo um para a Terra e outro para as estrelas;
    - Também é configurada uma câmera *LookAt* para limitar o espaço 3D a ser visualizado;
    - As estrelas são criadas em posições randômicas, normalizadas, rotacionadas e transladadas. Além de que quando elas atingirem a coordenada mais próxima da câmera, elas são retornadas para o fundo da visualização.
    - A tela inteira é configurada para projetar os objetos em perspectiva, tanto a Terra quanto as estrelas.
    - Por fim, a interface contém apenas um slider com os triângulos renderizados na Terra para se observar as camadas da Terra sendo preenchidas (no projeto final essa visualização ficará mais clara com o uso de texturas).
	
 - `assets\Earth_2K.mtl`– Arquivo contendo as coordenadas de texturização da Terra. Por enquanto o arquivo foi carregado nos assets para não gerar erros no console, ainda que não esteja sendo propriamente utilizado nesta entrega;

 - `assets\Earth_2K.obj`– Arquivo contendo os vértices e faces mapeadas da Terra.
  
 - `assets\maps\Bump_2K.png` – Textura que representa o mapa de normais do planeta, para tornar a visão do planeta mais realista com um efeito luminoso que melhora a aparência da superfície.

 - `assets\maps\Diffuse_2K.png` – Textura que representa o mapa do planeta Terra sendo completamente iluminado pelo Sol.

 - `assets\maps\Night_lights_2K.png` – Textura que representa o mapa do planeta Terra numa visualização noturna.

 - `assets\shaders\day.frag` – *Fragment shader*, onde designa a cor de cada triângulo desenhado dos objetos. Por padrão os triângulos serão brancos, já que o *face culling* está sempre ativado.

 - `assets\shaders\day.vert`– *Vertex shader*, é o objeto que possui as propriedades dos vértices dos triângulos.

 - `assets\shaders\night.frag` – *Fragment shader*, onde designa a cor de cada triângulo desenhado dos objetos. Por padrão os triângulos serão brancos, já que o *face culling* está sempre ativado.

 - `assets\shaders\night.vert`– *Vertex shader*, é o objeto que possui as propriedades dos vértices dos triângulos.
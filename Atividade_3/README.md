#### Nome: Heberton Miranda Rodrigues da Silva  	
#### R.A.: 21023713
#### Professor: Harlen Costa Batagelo

# Computação Gráfica – Atividade 3

## Enunciado
Esta tarefa consiste em desenvolver uma aplicação que mostre gráficos 3D com primitivas do OpenGL e use transformações geométricas para produzir algum tipo de animação (isto é, a geometria não pode ser estática). Assim como na atividade anterior, a aplicação deve necessariamente usar a biblioteca ABCg e renderizar gráficos com o pipeline do OpenGL usando shaders. Use como referência os projetos loadmodel, lookat, starfield e viewer abordados nas notas de aula. Esta atividade pode ser um protótipo da aplicação que será apresentada na atividade final, mas também pode ser um projeto independente.

## Descrição da aplicação
Foi desenvolvido em C++ e utilizando a API do OpenGL o `Earth Visualization`, que será um visualizador 3D do planeta Terra. Por enquanto, esta atividade representa um protótipo da atividade final, que conterá a texturização do planeta, dando mais característica ao visualizador.

O visualizador está disponível <a href="https://hebertonmiranda.github.io/comp_graf/Atividade_3/public/" target="_blank" rel="noopener noreferrer">aqui</a>!

## Controles da aplicação
Basta utilizar os movimentos do *mouse* para clicar e arrastar para rotacionar o planeta. Há um slider onde é possível alterar a quantidade de triângulos renderizados no objeto do planeta Terra. Esse slider será interessante para ver as camadas da Terra desenhadas gradualmente.

No mais, há o *widget* para ver a quantidade de *frames* por segundo e um botão para deixar a aplicação em tela cheia.

# Descrição técnica
Para a elaboração da atividade foi utilizada a linguagem C++ juntamente com as bibliotecas da própria linguagem, o framework `ABCg` (https://github.com/hbatagelo/abcg) e a biblioteca `ImGui` (https://github.com/ocornut/imgui). Para a renderização gráfica foi utilizada a API `OpenGL` (https://www.opengl.org/). Foram utilizadas as seguintes técnicas:

 - `main.cpp`– Foi criada uma janela usando a API `OpenGL`, fixando altura e comprimento, além de manter as opções de mostrar FPS e botão de tela cheia;
    > Obs.: Para uma melhor visualização web, a resolução na web foi alterada para 1280x720 px.

 - `background.hpp`– Classe com os métodos e atributos utilizados para renderizar o fundo da aplicação, que são as estrelas;

 - `background.cpp`– São criados os VAO's, VBO's e EBO's para o armazenamento dos atributos das estrelas. Os atributos de uma estrela para fazer a renderização são obtidos através de um objeto `OBJ`. Cada estrela é centralizada na origem e possui as coordenadas normalizadas para se enquadrarem na visualização.

 - `earth.hpp`– Classe com os métodos e atributos utilizados para renderizar o objeto principal da visualização, que será o planeta Terra.

 - `earth.cpp`– A estratégia é similar a `background.cpp`, onde são criados os VAO's, VBO's e EBO's para o armazenamento dos atributos dos blocos, onde os atributos do planeta para fazer a renderização são obtidos através de um objeto `OBJ`. O planeta também possui suas coordenadas normalizadas e é colocado para ser exibido no centro da visualização.

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
	
 - `assets\Earth_2k.mtl`– Arquivo contendo as coordenadas de texturização da Terra. Por enquanto o arquivo foi carregado nos assets para não gerar erros no console, ainda que não esteja sendo propriamente utilizado nesta entrega;

 - `assets\Earth_2k.obj`– Arquivo contendo os vértices e faces mapeadas da Terra.
  
 - `assets\box.obj` – Arquivo contendo os vértices e faces mapeadas das estrelas que compõem o fundo da visualização.

 - `assets\depth.frag` – *Fragment shader*, onde designa a cor de cada triângulo desenhado dos objetos. Por padrão os triângulos serão brancos, já que o *face culling* está sempre ativado.

 - `assets\depth.vert`– *Vertex shader*, é o objeto que possui as propriedades dos vértices dos triângulos.
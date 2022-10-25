#include "rectangle.hpp"

void Rectangle::create(GLuint program, int quantity) {
  destroy();

  // Initialize pseudorandom number generator and distributions
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  m_program = program;

  // Get location of uniforms in the program
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  // Create rectangles
  m_rectangles.clear();
  m_rectangles.resize(quantity);

  int indiceX = 0, indiceY = 0;

  for (auto &asteroid : m_rectangles) {
    if (indiceX < 6) {
      indiceX++;
      asteroid = createAsteroid(indiceX, indiceY);
    } else {
      indiceY++;
      indiceX = 1;
      asteroid = createAsteroid(indiceX, indiceY);
    }
  }
}

void Rectangle::paint() {
  abcg::glUseProgram(m_program);

  for (auto const &rectangles : m_rectangles) {

    abcg::glBindVertexArray(rectangles.m_VAO);

    abcg::glUniform1f(m_scaleLoc, m_scale);
    abcg::glUniform1f(m_rotationLoc, m_rotation);
    abcg::glUniform2fv(m_translationLoc, 1, &rectangles.m_translation.x);
    abcg::glUniform4fv(m_colorLoc, 1, &rectangles.m_color.r);
    abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    abcg::glBindVertexArray(0);
  }
  abcg::glUseProgram(0);
}

void Rectangle::destroy() {
  for (auto rectangles : m_rectangles) {
    abcg::glDeleteBuffers(1, &rectangles.m_VBO);
    abcg::glDeleteVertexArrays(1, &rectangles.m_VAO);
  }
}

Rectangle::Rectangles Rectangle::createAsteroid(int indiceX, int indiceY) {
  Rectangles rectangle;

  rectangle.m_translation.x =
      indiceX == 1 ? -0.75f : -1 + ((indiceX)*0.30f) - 0.05f;
  rectangle.m_translation.y =
      indiceY + 1 == 1 ? 0.97f : 1 - ((indiceY + 1) * 0.03f);

  std::array<glm::vec2, 4> positions{
      // Paddle body
      glm::vec2{-15.0f, 0.0f},
      glm::vec2{-15.0f, 0.3f},
      glm::vec2{+15.0f, 0.0f},
      glm::vec2{+15.0f, 0.3f},
  };

  // Normalize
  for (auto &position : positions) {
    position /= glm::vec2{10.0f, 1.0f};
  }

  std::array const indices{0, 1, 2, 3, 0, 2, 1, 3};
  if ((indiceX + indiceY) % 2 == 0) {
    glm::vec4 color{0, 0, 0, 1};
    rectangle.m_color = color;
  } else {
    glm::vec4 color{0.5, 0.5, 0.5, 1};
    rectangle.m_color = color;
  }

  // Generate VBO
  abcg::glGenBuffers(1, &rectangle.m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, rectangle.m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &rectangle.m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle.m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &rectangle.m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(rectangle.m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, rectangle.m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle.m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);

  return rectangle;
}
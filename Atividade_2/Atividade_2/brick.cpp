#include "brick.hpp"

void Brick::create(GLuint program, int quantity) {
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

  // Create bricks
  m_bricks.clear();
  m_bricks.resize(quantity);

  int column = 0, row = 0;

  for (auto &brick : m_bricks) {
    if (column < 6) {
      column++;
    } else {
      row++;
      column = 1;
    }
    brick = createBricks(column, row);
  }
}

void Brick::paint() {
  abcg::glUseProgram(m_program);

  for (auto const &bricks : m_bricks) {

    abcg::glBindVertexArray(bricks.m_VAO);

    abcg::glUniform1f(m_scaleLoc, m_scale);
    abcg::glUniform1f(m_rotationLoc, m_rotation);
    abcg::glUniform2fv(m_translationLoc, 1, &bricks.m_translation.x);
    abcg::glUniform4fv(m_colorLoc, 1, &bricks.m_color.r);
    abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    abcg::glBindVertexArray(0);
  }
  abcg::glUseProgram(0);
}

void Brick::destroy() {
  for (auto bricks : m_bricks) {
    abcg::glDeleteBuffers(1, &bricks.m_VBO);
    abcg::glDeleteVertexArrays(1, &bricks.m_VAO);
  }
}

Brick::Bricks Brick::createBricks(int column, int row) {
  Bricks brick;

  // position of the bricks
  if (column == 1) {
    brick.m_translation.x = -0.75f;
  } else {
    brick.m_translation.x = -1 + ((column)*0.30f) - 0.05f;
  }

  if (row + 1 == 1) {
    brick.m_translation.y = 0.97f;
  } else {
    brick.m_translation.y = 1 - ((row + 1) * 0.03f);
  }

  std::array<glm::vec2, 4> positions{
      // size of the bricks
      glm::vec2{-8.0f, 0.0f},
      glm::vec2{-8.0f, 0.2f},
      glm::vec2{+8.0f, 0.0f},
      glm::vec2{+8.0f, 0.2f},
  };

  // Normalize
  for (auto &position : positions) {
    position /= glm::vec2{10.0f, 1.0f};
  }

  // color of the bricks
  std::array const index{0, 1, 2, 3, 0, 2, 1, 3};

  if (row % 9 == 0) {
    brick.m_color = {1.00, 0.00, 0.00, 1};
  } else if (row % 9 == 1) {
    brick.m_color = {0.88, 0.25, 0.13, 1};
  } else if (row % 9 == 2) {
    brick.m_color = {0.75, 0.50, 0.25, 1};
  } else if (row % 9 == 3) {
    brick.m_color = {0.63, 0.75, 0.38, 1};
  } else if (row % 9 == 4) {
    brick.m_color = {0.50, 1.00, 0.50, 1};
  } else if (row % 9 == 5) {
    brick.m_color = {0.38, 0.75, 0.63, 1};
  } else if (row % 9 == 6) {
    brick.m_color = {0.25, 0.50, 0.75, 1};
  } else if (row % 9 == 7) {
    brick.m_color = {0.13, 0.25, 0.88, 1};
  } else {
    brick.m_color = {0.00, 0.00, 1.00, 1};
  }

  // Generate VBO
  abcg::glGenBuffers(1, &brick.m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, brick.m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &brick.m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, brick.m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &brick.m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(brick.m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, brick.m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, brick.m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);

  return brick;
}
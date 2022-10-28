#include "paddle.hpp"

#include <iostream>

void Paddle::create(GLuint program) {
  destroy();

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_rotationLoc = abcg::glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");

  m_rotation = 0.0f;
  m_translation = glm::vec2(0, -0.9);

  std::array<glm::vec2, 4> positions{
      // Paddle size
      glm::vec2{-12.0f, 0.0f},
      glm::vec2{-12.0f, 0.2f},
      glm::vec2{+12.0f, 0.0f},
      glm::vec2{+12.0f, 0.2f},
  };

  // Normalize
  for (auto &position : positions) {
    position /= glm::vec2{10.0f, 1.0f};
  }

  std::array index{0, 1, 2, 3, 0, 2, 1, 3};
  // Generate VBO
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate EBO
  abcg::glGenBuffers(1, &m_EBO);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  abcg::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index.data(),
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Paddle::paint(const GameData &gameData) {
  if (gameData.m_state != State::Playing)
    return;

  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);

  abcg::glUniform1f(m_scaleLoc, m_scale);
  abcg::glUniform1f(m_rotationLoc, m_rotation);
  abcg::glUniform2fv(m_translationLoc, 1, &m_translation.x);

  abcg::glUniform4fv(m_colorLoc, 1, &m_color.r);
  abcg::glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Paddle::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteBuffers(1, &m_EBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Paddle::update(const GameData &gameData) {

  if (m_paddleTimer.elapsed() > 10.0 / 1000.0) {

    m_paddleTimer.restart();

    // move the paddle to the left when the left arrow is pressed
    if (gameData.m_input[static_cast<size_t>(Input::Left)]) {
      if (m_translation.x - 0.02f >= -1.0f)
        m_translation.x -= 0.02f;
      if (m_translation.x - 0.12f < -1.0f)
        m_translation.x = -0.88f;
    }

    // move the paddle to the right when the right arrow is pressed
    if (gameData.m_input[static_cast<size_t>(Input::Right)]) {
      if (m_translation.x + 0.02f <= +1.0f)
        m_translation.x += 0.02f;
      if (m_translation.x + 0.12f > 1.0f)
        m_translation.x = 0.88f;
    }
  }
}
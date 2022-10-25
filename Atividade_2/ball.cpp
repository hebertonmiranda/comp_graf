#include "ball.hpp"

//#include <cppitertools/itertools.hpp>
#include <iostream>
#include <random>

// using namespace std;

void Ball::create(GLuint program) {
  destroy();
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  std::uniform_int_distribution<int> intDistribution(0, 1);
  intDistribution(m_randomEngine) == 1 ? m_esquerda = true : m_direita = true;
  m_baixo = true;
  m_defense = false;

  m_program = program;
  m_colorLoc = abcg::glGetUniformLocation(m_program, "color");
  m_scaleLoc = abcg::glGetUniformLocation(m_program, "scale");
  m_translationLoc = abcg::glGetUniformLocation(m_program, "translation");
  m_translation = glm::vec2(0, 0.7f);

  auto const sides{10};

  std::vector<glm::vec2> positions(0);
  positions.emplace_back(0, 0);
  auto const step{M_PI * 2 / sides};
  for (auto const angle : iter::range(0.0, M_PI * 2, step)) {
    positions.emplace_back(std::cos(angle), std::sin(angle));
  }
  positions.push_back(positions.at(1));

  // Generate VBO of positions
  abcg::glGenBuffers(1, &m_VBO);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

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

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Ball::paint() {
  abcg::glUseProgram(m_program);

  abcg::glBindVertexArray(m_VAO);
  abcg::glUniform4f(m_colorLoc, 1, 1, 1, 0);
  abcg::glUniform1f(m_rotationLoc, 0);
  abcg::glUniform1f(m_scaleLoc, m_scale);

  abcg::glUniform2f(m_translationLoc, m_translation.x, m_translation.y);
  abcg::glDrawArrays(GL_TRIANGLE_FAN, 0, 12);

  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Ball::destroy() {
  abcg::glDeleteBuffers(1, &m_VBO);
  abcg::glDeleteVertexArrays(1, &m_VAO);
  m_esquerda = false, m_direita = false, m_cima = false;
}

bool Ball::verifyPosition(Paddle &paddle) {
  return m_defense = paddle.m_translation.x - 0.12 <= m_translation.x &&
                     paddle.m_translation.x + 0.12 >= m_translation.x;
}

void Ball::update(Paddle &paddle, const GameData &gameData) {
  if (gameData.m_state == State::Playing &&
      m_ballTimer.elapsed() > 10.0 / 1000.0) {
    m_ballTimer.restart();

    if (m_translation.x >= 0.99f) {
      m_esquerda = true;
      m_direita = false;
    }
    if (m_translation.x <= -0.99f) {
      m_esquerda = false;
      m_direita = true;
    }
    if (m_translation.y >= 0.99f) {
      m_baixo = true;
      m_cima = false;
    }
    if (m_defense) {
      m_baixo = false;
      m_cima = true;
      m_defense = false;
    }

    if (m_esquerda) {
      if (m_translation.x < -0.0f) {
        m_translation.x - 0.01f < -0.99f ? m_translation.x = -0.99f
                                         : m_translation.x -= 0.01f;
      } else {
        m_translation.x -= 0.01;
      }

    } else if (m_direita) {
      if (m_translation.x < -0.0f) {
        m_translation.x += 0.01;
      } else {
        m_translation.x + 0.01f < 0.99f ? m_translation.x += 0.01f
                                        : m_translation.x = 0.99f;
      }
    }
    if (m_baixo) {
      if (m_translation.y < -0.0f) {
        m_translation.y - 0.01f > -0.87f
            ? m_translation.y -= 0.01
            : (verifyPosition(paddle) ? m_translation.y = -0.87f
                                      : m_translation.y -= 0.01);
      } else {
        m_translation.y -= 0.01;
      }
    } else if (m_cima) {
      if (m_translation.y < -0.0f) {
        m_translation.y += 0.01f;
      } else {
        m_translation.y + 0.01f < 0.99f ? m_translation.y += 0.01f
                                        : m_translation.y = 0.99f;
      }
    }
  }
}
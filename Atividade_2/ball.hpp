#ifndef BALL_HPP
#define BALL_HPP

#include <random>

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"
#include "paddle.hpp"
class OpenGLWindow;

class Ball {
public:
  void create(GLuint program);
  void paint();
  void destroy();
  bool verifyPosition(Paddle &paddle);
  void update(Paddle &paddle, const GameData &gameData);

  bool m_defense;
  bool m_esquerda, m_direita, m_cima, m_baixo;
  float m_scale{0.01f};
  abcg::Timer m_ballTimer;
  std::default_random_engine m_randomEngine;
  glm::vec2 m_translation{glm::vec2(0)};

private:
  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_colorLoc{};
  GLint m_rotationLoc{};
  GLint m_translationLoc{};
  GLint m_scaleLoc{};

  GLuint m_VAO{};
  GLuint m_VBO{};
};

#endif
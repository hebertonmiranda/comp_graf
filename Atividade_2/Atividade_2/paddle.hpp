#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "abcgOpenGL.hpp"
#include "brick.hpp"
#include "gamedata.hpp"

class Brick;
class Ball;
class OpenGLWindow;

class Paddle {
public:
  void create(GLuint program);
  void paint(const GameData &gameData);
  void destroy();
  void update(const GameData &gameData);

  glm::vec2 m_translation{glm::vec2(0)};

private:
  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};
  GLint m_rotationLoc{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  glm::vec4 m_color{1};
  float m_rotation{};
  float m_scale{0.1f};

  abcg::Timer m_paddleTimer;
};

#endif
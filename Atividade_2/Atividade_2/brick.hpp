#ifndef BRICK_HPP
#define BRICK_HPP

#include <list>
#include <random>

#include "abcgOpenGL.hpp"
#include "gamedata.hpp"

class OpenGLWindow;

class Brick {
public:
  void create(GLuint program, int quantity);
  void paint();
  void destroy();

  struct Bricks {
    GLuint m_VAO{};
    GLuint m_VBO{};
    GLuint m_EBO{};

    glm::vec4 m_color{1};
    bool m_dead{false};
    glm::vec2 m_translation{glm::vec2(0)};
  };

  float m_scale = 0.1f;
  float m_rotation = 0.0f;

  std::list<Bricks> m_bricks;

  std::default_random_engine m_randomEngine;

  Brick::Bricks createBricks(int, int);

private:
  GLuint m_program{};
  GLint m_colorLoc{};
  GLint m_rotationLoc{};
  GLint m_translationLoc{};
  GLint m_scaleLoc{};
};

#endif
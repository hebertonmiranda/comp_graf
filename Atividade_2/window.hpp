#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <random>

#include "abcgOpenGL.hpp"
#include "ball.hpp"
#include "gamedata.hpp"
#include "paddle.hpp"
#include "rectangle.hpp"

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onUpdate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  glm::ivec2 m_viewportSize{};

  GLuint m_starsProgram{};
  GLuint m_objectsProgram{};

  GameData m_gameData;

  Rectangle m_rectangle;
  Ball m_ball;
  Paddle m_paddle;

  abcg::Timer m_restartWaitTimer;

  ImFont *m_font{};

  std::default_random_engine m_randomEngine;

  void restart();
  void checkCollisions();
  void checkWinCondition();
  void checkLossCondition();

  std::array<float, 4> m_clearColor{0.8f, 0.5f, 0.0f, 1.0f};
};

#endif
#include "window.hpp"

void Window::onEvent(SDL_Event const &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_gameData.m_input.set(static_cast<size_t>(Input::Start));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.set(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.set(static_cast<size_t>(Input::Right));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_gameData.m_input.reset(static_cast<size_t>(Input::Start));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_gameData.m_input.reset(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_gameData.m_input.reset(static_cast<size_t>(Input::Right));
  }
}

void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  // Load a new font
  auto const filename{assetsPath + "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 60.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError("Cannot load font file");
  }
  // Create program to render the other objects
  m_objectsProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "objects.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "objects.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  // Create program to render the stars
  m_starsProgram =
      abcg::createOpenGLProgram({{.source = assetsPath + "stars.vert",
                                  .stage = abcg::ShaderStage::Vertex},
                                 {.source = assetsPath + "stars.frag",
                                  .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0.5f, 0.5f, 0.5f, 0.5f);

#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
#endif

  // Start pseudo-random number generator
  m_randomEngine.seed(
      std::chrono::steady_clock::now().time_since_epoch().count());

  restart();
}

void Window::restart() {
  m_gameData.m_state = State::Playing;

  m_paddle.create(m_objectsProgram);
  m_brick.create(m_objectsProgram, 54);
  m_ball.create(m_objectsProgram);
}

void Window::onUpdate() {
  // Wait 5 seconds before restarting
  if (m_gameData.m_state != State::Playing &&
      m_restartWaitTimer.elapsed() > 5) {
    restart();
    return;
  }

  m_paddle.update(m_gameData);
  m_ball.update(m_paddle, m_gameData);

  if (m_gameData.m_state == State::Playing) {
    checkCollisions();
    checkWinCondition();
    checkLossCondition();
  }
}

void Window::onPaint() {
  abcg::glClear(GL_COLOR_BUFFER_BIT);
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  m_paddle.paint(m_gameData);
  m_brick.paint();
  m_ball.paint();
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    auto const size{ImVec2(300, 85)};
    auto const position{ImVec2((m_viewportSize.x - size.x) / 2.0f,
                               (m_viewportSize.y - size.y) / 2.0f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags const flags{ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoTitleBar |
                                 ImGuiWindowFlags_NoInputs};
    ImGui::Begin(" ", nullptr, flags);
    ImGui::PushFont(m_font);

    if (m_gameData.m_state == State::GameOver) {
      ImGui::Text("Game Over!");
    } else if (m_gameData.m_state == State::Win) {
      ImGui::Text("*You Win!*");
    }

    ImGui::PopFont();
    ImGui::End();
  }
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_starsProgram);
  abcg::glDeleteProgram(m_objectsProgram);

  m_brick.destroy();
  m_ball.destroy();
  m_paddle.destroy();
}

void Window::checkCollisions() {
  for (auto &brick : m_brick.m_bricks) {
    // if (brick.m_translation.x - 0.12 <= m_ball.m_translation.x &&
    //     brick.m_translation.x + 0.12 >= m_ball.m_translation.x &&
    //     brick.m_translation.y + 0.02f >= m_ball.m_translation.y &&
    //     brick.m_translation.y - 0.02f <= m_ball.m_translation.y) {
    //   brick.m_dead = true;
    // }
    // check if the ball hit some side of the brick
    if (brick.m_translation.x - 0.08f <= m_ball.m_translation.x &&
        brick.m_translation.x + 0.08f >= m_ball.m_translation.x &&
        brick.m_translation.y + 0.02f >= m_ball.m_translation.y &&
        brick.m_translation.y - 0.02f <= m_ball.m_translation.y) {

      // check if the ball hit up or down the brick
      if (brick.m_translation.x - 0.08f <= m_ball.m_translation.x &&
          brick.m_translation.x + 0.08f >= m_ball.m_translation.x &&
          brick.m_translation.y + 0.02f >= m_ball.m_translation.y) {

        m_ball.m_brick_down = true;

      } else if (brick.m_translation.x - 0.08f <= m_ball.m_translation.x &&
                 brick.m_translation.x + 0.08f >= m_ball.m_translation.x &&
                 brick.m_translation.y - 0.02f <= m_ball.m_translation.y) {

        m_ball.m_brick_up = true;

      } else if (brick.m_translation.x + 0.08f >= m_ball.m_translation.x &&
                 brick.m_translation.y + 0.02f >= m_ball.m_translation.y &&
                 brick.m_translation.y - 0.02f <= m_ball.m_translation.y) {

        m_ball.m_brick_left = true;

      } else {

        m_ball.m_brick_right = true;
      }
      brick.m_dead = true;
    }
  }
  m_brick.m_bricks.remove_if([](auto const &a) { return a.m_dead; });
}

void Window::checkWinCondition() {
  if (m_brick.m_bricks.empty()) {
    m_gameData.m_state = State::Win;
    m_restartWaitTimer.restart();
  }
}

void Window::checkLossCondition() {
  if (m_ball.m_translation.y <= m_paddle.m_translation.y) {
    m_gameData.m_state = State::GameOver;
    m_restartWaitTimer.restart();
  }
}

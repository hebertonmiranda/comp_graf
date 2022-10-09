#include "window.hpp"

void Window::onCreate() {}

void Window::onPaint() {
  // Set the clear color
  abcg::glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2],
                     m_clearColor[3]);
  // Clear the color buffer
  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaint();
  // Our own ImGui widgets go below
  {
    // Window begin
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::SetNextWindowSize(ImVec2(666, 326));
    ImGui::Begin("Simon Game!", nullptr, window_flags);

    // Auxiliar variables
    static int checked = 0;
    static int game_turn = 0;
    static int player_turn = 0;
    static int index = 3;
    static int started = 0;

    // Auxiliar arrays for the game
    static std::array<int, 4> color_button{0, 0, 0, 0};
    static std::array<int, 10> game{0, 2, 3, 1, 0, 3, 2, 1, 3, 0};
    static std::array<int, 10> answer{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    static std::array<std::string, 5> attempt{
        "Correct Answer!", "Wrong Answer! Hit start and try again!",
        "Congratulations! Thanks for playing!", "Hit start and play!",
        "Hit check to check your answer!"};

    // Static text above the buttons
    ImGui::Text("  Current level: %d\t  Current turn: %d\t  %s", game_turn,
                player_turn, attempt[index].c_str());
    ImGui::Separator();

    // Create the columns
    ImGui::Columns(4, nullptr, true);

    // Buttons' flags and color properties
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha |
                                ImGuiColorEditFlags_NoPicker |
                                ImGuiColorEditFlags_NoTooltip;
    static std::array<ImVec4, 2> green_vec{ImVec4{0.0f, 0.5f, 0.0f, 1.0f},
                                           ImVec4{0.0f, 1.0f, 0.0f, 1.0f}};
    static std::array<ImVec4, 2> red_vec{ImVec4{0.5f, 0.0f, 0.0f, 1.0f},
                                         ImVec4{1.0f, 0.0f, 0.0f, 1.0f}};
    static std::array<ImVec4, 2> yellow_vec{ImVec4{0.5f, 0.5f, 0.0f, 1.0f},
                                            ImVec4{1.0f, 1.0f, 0.0f, 1.0f}};
    static std::array<ImVec4, 2> blue_vec{ImVec4{0.0f, 0.0f, 0.5f, 1.0f},
                                          ImVec4{0.0f, 0.0f, 1.0f, 1.0f}};

    // Green button and it's conditions
    ImGui::ColorButton("green", green_vec[color_button[0]], flags,
                       ImVec2(150, 150));
    if (ImGui::IsItemClicked()) {
      color_button[0] = 1;
      color_button[1] = 0;
      color_button[2] = 0;
      color_button[3] = 0;
      if (started == 1 && checked == 0) {
        answer[player_turn] = 0;
        player_turn++;
        if (player_turn == game_turn) {
          checked = 1;
        }
      }
    }
    ImGui::NextColumn();

    // Red button and it's conditions
    ImGui::ColorButton("red", red_vec[color_button[1]], flags,
                       ImVec2(150, 150));
    if (ImGui::IsItemClicked()) {
      color_button[0] = 0;
      color_button[1] = 1;
      color_button[2] = 0;
      color_button[3] = 0;
      if (started == 1 && checked == 0) {
        answer[player_turn] = 1;
        player_turn++;
        if (player_turn == game_turn) {
          checked = 1;
        }
      }
    }
    ImGui::NextColumn();

    // Yellow button and it's conditions
    ImGui::ColorButton("yellow", yellow_vec[color_button[2]], flags,
                       ImVec2(150, 150));
    if (ImGui::IsItemClicked()) {
      color_button[0] = 0;
      color_button[1] = 0;
      color_button[2] = 1;
      color_button[3] = 0;
      if (started == 1 && checked == 0) {
        answer[player_turn] = 2;
        player_turn++;
        if (player_turn == game_turn) {
          checked = 1;
        }
      }
    }
    ImGui::NextColumn();

    // Blue button and it's conditions
    ImGui::ColorButton("blue", blue_vec[color_button[3]], flags,
                       ImVec2(150, 150));
    if (ImGui::IsItemClicked()) {
      color_button[0] = 0;
      color_button[1] = 0;
      color_button[2] = 0;
      color_button[3] = 1;
      if (started == 1 && checked == 0) {
        answer[player_turn] = 3;
        player_turn++;
        if (player_turn == game_turn) {
          checked = 1;
        }
      }
    }
    // ImGui::EndColumns();
    ImGui::Separator();

    // Start button and it's conditions
    ImGui::Button("Start!");
    if (ImGui::IsItemClicked()) {
      color_button[0] = 0;
      color_button[1] = 0;
      color_button[2] = 0;
      color_button[3] = 0;
      game_turn = 1;
      started = 1;
      player_turn = 0;
      index = 4;

      // Run the sequence of buttons to be pressed by the player
      for (int i = 0; i < game_turn; i++) {
        if (game[i] == 0) {
          color_button[0] = 1;
          color_button[1] = 0;
          color_button[2] = 0;
          color_button[3] = 0;
        }
        if (game[i] == 1) {
          color_button[0] = 0;
          color_button[1] = 1;
          color_button[2] = 0;
          color_button[3] = 0;
        }
        if (game[i] == 2) {
          color_button[0] = 0;
          color_button[1] = 0;
          color_button[2] = 1;
          color_button[3] = 0;
        }
        if (game[i] == 3) {
          color_button[0] = 0;
          color_button[1] = 0;
          color_button[2] = 0;
          color_button[3] = 1;
        }
      }
    }

    // Check button and it's conditions
    ImGui::Button("Check!");
    if (ImGui::IsItemClicked()) {
      if (started == 1 && checked == 1) {
        int flag = 0;
        checked = 0;

        // Check if the current answer is correct
        for (int i = 0; i < game_turn; i++) {
          if (game[i] == answer[i]) {
            index = 0;
          } else {
            index = 1;
            answer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            game_turn = 0;
            player_turn = 0;
            flag = 1;
            started = 0;
            break;
          }
        }

        // If all the answers were correct then the game will pick the next
        // color
        if (flag == 0) {
          player_turn = 0;
          game_turn++;
          for (int i = 0; i < game_turn; i++) {
            if (game[i] == 0) {
              color_button[0] = 1;
              color_button[1] = 0;
              color_button[2] = 0;
              color_button[3] = 0;
            }
            if (game[i] == 1) {
              color_button[0] = 0;
              color_button[1] = 1;
              color_button[2] = 0;
              color_button[3] = 0;
            }
            if (game[i] == 2) {
              color_button[0] = 0;
              color_button[1] = 0;
              color_button[2] = 1;
              color_button[3] = 0;
            }
            if (game[i] == 3) {
              color_button[0] = 0;
              color_button[1] = 0;
              color_button[2] = 0;
              color_button[3] = 1;
            }
          }
          if (game_turn == 11) {
            index = 2;
            game_turn = 0;
            player_turn = 0;
            started = 0;
          }
        }
      }
    }
    // Window end
    ImGui::End();
  }
}
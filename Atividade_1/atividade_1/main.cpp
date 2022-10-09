#include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    window.setWindowSettings({.width = 790,  // 452
                              .height = 426, // 515
                              //.showMaximizeButton = false,
                              .showFPS = false,
                              .showFullscreenButton = false,
                              .title = "Simon Game!"});

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}
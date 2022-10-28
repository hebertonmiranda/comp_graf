#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include <bitset>

enum class Input { Left, Right };
enum class State { GameOver, Playing, Win };

struct GameData {
  State m_state{State::Playing};
  std::bitset<2> m_input; // [left, right]
};

#endif
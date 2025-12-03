#include <iostream>
#include <string>

#include "game.h"
#include "player.h"

int main() {
  std::string player_name;
  std::cout << "Hi! Please enter your name: ";
  std::getline(std::cin, player_name);
  Player player(player_name);

  std::string zoo_name;
  std::cout << "Give your zoo a name: ";
  std::getline(std::cin, zoo_name);
  Game game(player, zoo_name);

  game.start();

  return 0;
}

#include <iostream>
#include <string>

#include "game.h"
#include "player.h"

int main() {
  std::string player_name;
  do {
    std::cout << "> Hi! Please enter your name: ";
    std::getline(std::cin, player_name);

    if (player_name.empty()) {
      std::cout << "  Name cannot be empty. Please try again.\n";
    }
  } while (player_name.empty());

  Player player(player_name);
  std::string zoo_name;
  do {
    std::cout << "> Give your zoo a name: ";
    std::getline(std::cin, zoo_name);
    if (zoo_name.empty()) {
      std::cout << "  Zoo name cannot be empty. Please try again.\n";
    }
  } while (zoo_name.empty());

  Game game(player, zoo_name);
  game.start();

  return 0;
}

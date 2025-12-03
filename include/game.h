#ifndef GAME_H
#define GAME_H

#include <string>

#include "player.h"
#include "zoo.h"

class Game {
 public:
  Game(const Player& player, std::string zoo_name);
  void start();

 private:
  Player player_;
  Zoo zoo_;
  bool running_;

  void setupStarterZoo();

  // menus
  void displayMainMenu();
  void manageAnimals();
  void manageExhibits();
  void manageFinances();

  void clearInput();
  int getPlayerInput(int min, int max);

  // animal actions
  Animal* chooseAnimal();
  void displayAllAnimals();
  void displayAnimalsNeedingAttention();
  void renameAnimal();
  void purchaseAnimal();
  void sellAnimal();
  void feedAnimal();
  void playWithAnimal();
  void exerciseAnimal();
  void treatAnimal();
  void addAnimalToExhibit();
  void removeAnimalFromExhibit();
  void moveAnimalToExhibit();

  // exhibit actions
  Exhibit* chooseExhibit();
  void displayAllExhibits();
  void displayExhibitsNeedingCleaning();
  void purchaseExhibit();
  void sellExhibit();
  void cleanExhibit();

  // finance actions
  void checkBalance();

  void endDay();
  void exitGame();
};

#endif  // GAME_H

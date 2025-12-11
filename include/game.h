#ifndef GAME_H
#define GAME_H

#include <string>

#include "mission.h"
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

  int action_points_;
  int max_action_points_;
  std::vector<std::string> actions_;

  // mission system
  std::vector<Mission> missions_;
  void setupDailyMissions(int day);
  void checkMissions(bool end_of_day);
  void displayMissions();
  void completeMission(size_t mission_index);
  bool canAdvanceDay();
  bool checkMissionsImpossible();

  // menus
  void displayMainMenu();
  void manageAnimals();
  void manageExhibits();
  void manageZoo();

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
  void renameExhibit();
  void purchaseExhibit();
  void sellExhibit();
  void cleanExhibit();

  // zoo actions
  void checkBalance();
  void viewZooRating();

  // action tracking
  bool useActionPoint(const std::string action_description);
  void resetActionPoints();
  int getActionPoints() const;
  int getMaxActionPoints() const;
  void updateMaxActionPoints();

  void endDay();
  void exitGame();
  void displayHelp();

  void handleGameCompletion();
};

#endif  // GAME_H

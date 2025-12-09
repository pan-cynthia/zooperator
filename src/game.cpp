#include "game.h"

#include <iostream>
#include <limits>
#include <random>
#include <utility>

#include "bear.h"
#include "elephant.h"
#include "lion.h"
#include "monkey.h"
#include "penguin.h"
#include "rabbit.h"
#include "tortoise.h"

Game::Game(const Player& player, std::string zoo_name)
    : player_(player),
      zoo_(zoo_name, 1500.0),
      running_(true),
      action_points_(6),
      max_action_points_(6) {}

void Game::start() {
  std::cout << "\nWelcome to Zooperator " << player_.getName() << "!\n";
  std::cout << "You'll be working as the zookeeper for: " << zoo_.getName() << ".\n\n";
  std::cout << "Goals\n";
  std::cout << " - Keep the zoo running for 7 days.\n";
  std::cout << " - Keep all animals happy and healthy.\n";
  std::cout << " - Maintain a zoo rating above 3.0 stars.\n\n";

  setupStarterZoo();

  std::cout << "\nDAY " << zoo_.getDay() << "\n";

  while (running_) {
    displayMainMenu();
    int choice = getPlayerInput(1, 6);

    switch (choice) {
      case 1:
        manageAnimals();
        break;
      case 2:
        manageExhibits();
        break;
      case 3:
        manageZoo();
        break;
      case 4:
        endDay();
        break;
      case 5:
        exitGame();
        break;
      case 6:
        displayHelp();
        break;
    }
  }
}

void Game::setupStarterZoo() {
  std::cout << "Setting up your starter zoo...\n";
  std::cout << " - We've added 1 rabbit and a grassland exhibit to get you started!\n";

  std::cout << " - ";
  zoo_.purchaseExhibit(std::make_unique<Exhibit>("Bunny Burrow", "Grassland", 3, 300.0, 15.0));
  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit_ptr = rabbit.get();

  std::cout << " - ";
  zoo_.purchaseAnimal(std::move(rabbit));
  std::cout << " - ";
  zoo_.addAnimalToExhibit(rabbit_ptr, zoo_.getExhibit(0));

  std::cout << "\nZoo setup complete!\n";
}

void Game::clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Game::getPlayerInput(int min, int max) {
  int choice;
  while (true) {
    std::cout << "Select an option (" << min << "-" << max << "): ";
    if (std::cin >> choice && choice >= min && choice <= max) {
      clearInput();
      return choice;
    }
    std::cout << "Invalid input. Please try again.\n";
    clearInput();
  }
}

void Game::displayMainMenu() {
  std::cout << "\nMAIN MENU | Balance: $" << zoo_.getBalance() << " | Actions: " << action_points_
            << "/" << max_action_points_ << "\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "1. Manage Animals\n";
  std::cout << "2. Manage Exhibits\n";
  std::cout << "3. Manage Zoo\n";
  std::cout << "4. End Day\n";
  std::cout << "5. Exit Game\n";
  std::cout << "6. Help\n";
  std::cout << "-----------------------------------------\n\n";
}

void Game::manageAnimals() {
  while (true) {
    std::cout << "\nANIMAL MANAGEMENT | Actions: " << action_points_ << "/" << max_action_points_
              << "\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Display All Animals\n";
    std::cout << "2. Display Animals Needing Attention\n";
    std::cout << "3. Rename Animal\n";
    std::cout << "4. Purchase Animal\n";
    std::cout << "5. Sell Animal\n";
    std::cout << "6. Feed Animal (1 AP)\n";
    std::cout << "7. Play With Animal (1 AP)\n";
    std::cout << "8. Exercise Animal (1 AP)\n";
    std::cout << "9. Treat Animal (1 AP)\n";
    std::cout << "10. Add Animal to Exhibit\n";
    std::cout << "11. Remove Animal from Exhibit\n";
    std::cout << "12. Move Animal to Exhibit\n";
    std::cout << "13. Back to Main Menu\n";
    std::cout << "-----------------------------------------\n\n";

    int choice = getPlayerInput(1, 13);
    switch (choice) {
      case 1:
        displayAllAnimals();
        break;
      case 2:
        displayAnimalsNeedingAttention();
        break;
      case 3:
        renameAnimal();
        break;
      case 4:
        purchaseAnimal();
        break;
      case 5:
        sellAnimal();
        break;
      case 6:
        feedAnimal();
        break;
      case 7:
        playWithAnimal();
        break;
      case 8:
        exerciseAnimal();
        break;
      case 9:
        treatAnimal();
        break;
      case 10:
        addAnimalToExhibit();
        break;
      case 11:
        removeAnimalFromExhibit();
        break;
      case 12:
        moveAnimalToExhibit();
        break;
      case 13:
        return;
    }
  }
}

Animal* Game::chooseAnimal() {
  std::vector<Animal*> animals = zoo_.getAllAnimals();
  if (animals.empty()) {
    std::cout << "No animals in zoo.\n";
    return nullptr;
  }
  std::cout << "\nChoose an animal:\n";
  std::cout << "-----------------------------------------\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    std::cout << (i + 1) << ". " << animals[i]->getName() << " the " << animals[i]->getSpecies()
              << "\n";
  }
  std::cout << (animals.size() + 1) << ". Cancel\n";
  std::cout << "-----------------------------------------\n\n";

  int choice = getPlayerInput(1, static_cast<int>(animals.size() + 1));
  if (choice == static_cast<int>(animals.size() + 1)) {
    return nullptr;
  }
  return animals[choice - 1];
}

void Game::displayAllAnimals() {
  std::vector<Animal*> animals = zoo_.getAllAnimals();
  if (animals.empty()) {
    std::cout << "No animals in zoo yet.\n";
    return;
  }

  std::cout << "\nALL ANIMALS\n";
  std::cout << "-----------------------------------------\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    Animal* animal = animals[i];
    std::cout << (i + 1) << ". " << animal->getName() << " the " << animal->getSpecies() << "\n";
    std::cout << "   Age:        " << animal->getAge() << "\n";
    std::cout << "   Health:     " << animal->getHealthLevel() << "\n";
    std::cout << "   Hunger:     " << animal->getHungerLevel() << "\n";
    std::cout << "   Happiness:  " << animal->getHappinessLevel() << "\n";
    std::cout << "   Energy:     " << animal->getEnergyLevel() << "\n";
    Exhibit* exhibit = zoo_.findAnimalLocation(animal);
    std::cout << "   Location:   " << (exhibit ? exhibit->getName() : "None") << "\n";

    if (i < animals.size() - 1) {
      std::cout << "-----------------------------------------\n";
    }
  }
  std::cout << "-----------------------------------------\n";
}

void Game::displayAnimalsNeedingAttention() {
  std::vector<Animal*> animals = zoo_.getAnimalsNeedingAttention();
  if (animals.empty()) {
    std::cout << "\nNo animals need attention right now!\n";
    return;
  }

  std::cout << "\nANIMALS NEEDING ATTENTION\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    Animal* animal = animals[i];
    std::cout << "-----------------------------------------\n";
    std::cout << (i + 1) << ". " << animal->getName() << " the " << animal->getSpecies() << "\n";
    std::cout << "   Health:    " << animal->getHealthLevel() << "\n";
    std::cout << "   Hunger:    " << animal->getHungerLevel() << "\n";
    std::cout << "   Happiness: " << animal->getHappinessLevel() << "\n";
    std::cout << "   Energy:    " << animal->getEnergyLevel() << "\n";
  }
}

void Game::renameAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  std::string old_name = animal->getName();
  std::cout << "Enter new name: ";
  std::string name;
  std::getline(std::cin, name);

  std::cout << "Rename " << old_name << " the " << animal->getSpecies() << " to " << name << " the "
            << animal->getSpecies() << "? (1 - Yes, 2 - No)\n";

  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    animal->setName(name);
    std::cout << "Renamed " << old_name << " the " << animal->getSpecies() << " to " << name
              << " the " << animal->getSpecies() << "!\n";
  }
}

void Game::purchaseAnimal() {
  std::cout << "\nPURCHASE ANIMAL | Balance: $" << zoo_.getBalance() << "\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "1. Rabbit - $150\n";
  std::cout << "2. Tortoise - $250\n";
  std::cout << "3. Penguin - $400\n";
  std::cout << "4. Monkey - $600\n";
  std::cout << "5. Bear - $1500\n";
  std::cout << "6. Lion - $1500\n";
  std::cout << "7. Elephant - $3000\n";
  std::cout << "8. Cancel\n";
  std::cout << "-----------------------------------------\n\n";

  int choice = getPlayerInput(1, 8);
  if (choice == 8) {
    return;
  }

  std::cout << "Name your animal: ";
  std::string name;
  std::getline(std::cin, name);

  // random number generator
  std::random_device seed;
  std::mt19937 gen(seed());

  std::unique_ptr<Animal> animal;
  int age;

  switch (choice) {
    case 1: {
      std::uniform_int_distribution<> distr(1, 8);
      age = distr(gen);
      animal = std::make_unique<Rabbit>(name, age);
      break;
    }
    case 2: {
      std::uniform_int_distribution<> distr(10, 50);
      age = distr(gen);
      animal = std::make_unique<Tortoise>(name, age);
      break;
    }
    case 3: {
      std::uniform_int_distribution<> distr(5, 20);
      age = distr(gen);
      animal = std::make_unique<Penguin>(name, age);
      break;
    }
    case 4: {
      std::uniform_int_distribution<> distr(3, 15);
      age = distr(gen);
      animal = std::make_unique<Monkey>(name, age);
      break;
    }
    case 5: {
      std::uniform_int_distribution<> distr(3, 25);
      age = distr(gen);
      animal = std::make_unique<Bear>(name, age);
      break;
    }
    case 6: {
      std::uniform_int_distribution<> distr(4, 20);
      age = distr(gen);
      animal = std::make_unique<Lion>(name, age);
      break;
    }
    case 7: {
      std::uniform_int_distribution<> distr(10, 60);
      age = distr(gen);
      animal = std::make_unique<Elephant>(name, age);
      break;
    }
  }

  std::cout << "Purchase " << animal->getName() << " the " << animal->getSpecies() << " for $"
            << animal->getPurchaseCost() << "? (1 - Yes, 2 - No)\n";
  std::cout << "Daily Cost: $" << (animal->getFeedingCost() + animal->getMaintenanceCost())
            << " (Feeding: $" << animal->getFeedingCost() << ", Maintenance: $"
            << animal->getMaintenanceCost() << ")\n";

  choice = getPlayerInput(1, 2);

  if (choice == 1) {
    if (zoo_.purchaseAnimal(std::move(animal))) {
      updateMaxActionPoints();
      std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
    }
  }
}

void Game::sellAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  std::cout << "Sell " << animal->getName() << " the " << animal->getSpecies() << " for $"
            << (animal->getPurchaseCost() / 2.0) << "? (1 - Yes, 2 - No)\n";
  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    if (zoo_.sellAnimal(animal)) {
      updateMaxActionPoints();
      std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
    }
  }
}

void Game::feedAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  if (!useActionPoint("Fed " + animal->getName())) {
    return;
  }

  if (player_.feedAnimal(zoo_, animal)) {
    std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
  }
}

void Game::playWithAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  if (!useActionPoint("Played with " + animal->getName())) {
    return;
  }

  player_.playWithAnimal(animal);
}

void Game::exerciseAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  if (!useActionPoint("Exercised " + animal->getName())) {
    return;
  }

  player_.exerciseAnimal(animal);
}

void Game::treatAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  if (!useActionPoint("Treated " + animal->getName())) {
    return;
  }

  if (player_.treatAnimal(zoo_, animal)) {
    std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
  }
}

void Game::addAnimalToExhibit() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  zoo_.addAnimalToExhibit(animal, exhibit);
}

void Game::removeAnimalFromExhibit() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  Exhibit* exhibit = zoo_.findAnimalLocation(animal);
  if (!exhibit) {
    std::cout << animal->getName() << " is not in any exhibit!\n";
    return;
  }

  zoo_.removeAnimalFromExhibit(animal, exhibit);
}

void Game::moveAnimalToExhibit() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  zoo_.moveAnimalToExhibit(animal, exhibit);
}

void Game::manageExhibits() {
  while (true) {
    std::cout << "\nEXHIBIT MANAGEMENT | Actions: " << action_points_ << "/" << max_action_points_
              << "\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Display All Exhibits\n";
    std::cout << "2. Display Exhibits Needing Cleaning\n";
    std::cout << "3. Purchase Exhibit\n";
    std::cout << "4. Sell Exhibit\n";
    std::cout << "5. Clean Exhibit (1 AP)\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "-----------------------------------------\n\n";

    int choice = getPlayerInput(1, 6);
    switch (choice) {
      case 1:
        displayAllExhibits();
        break;
      case 2:
        displayExhibitsNeedingCleaning();
        break;
      case 3:
        purchaseExhibit();
        break;
      case 4:
        sellExhibit();
        break;
      case 5:
        cleanExhibit();
        break;
      case 6:
        return;
    }
  }
}

Exhibit* Game::chooseExhibit() {
  std::vector<Exhibit*> exhibits = zoo_.getAllExhibits();
  if (exhibits.empty()) {
    std::cout << "No exhibits in zoo.\n";
    return nullptr;
  }

  std::cout << "\nChoose an exhibit:\n";
  std::cout << "-----------------------------------------\n";
  for (size_t i = 0; i < exhibits.size(); ++i) {
    std::cout << (i + 1) << ". " << exhibits[i]->getName() << "\n";
  }

  std::cout << (exhibits.size() + 1) << ". Cancel\n";
  std::cout << "-----------------------------------------\n";

  int choice = getPlayerInput(1, static_cast<int>(exhibits.size() + 1));
  if (choice == static_cast<int>(exhibits.size() + 1)) {
    return nullptr;
  }

  return exhibits[choice - 1];
}

void Game::displayAllExhibits() {
  std::vector<Exhibit*> exhibits = zoo_.getAllExhibits();
  if (exhibits.empty()) {
    std::cout << "No exhibits in zoo yet.\n";
    return;
  }

  std::cout << "\nEXHIBITS\n";
  std::cout << "-----------------------------------------\n";
  for (size_t i = 0; i < exhibits.size(); ++i) {
    Exhibit* exhibit = exhibits[i];
    std::cout << (i + 1) << ". " << exhibit->getName() << " (" << exhibit->getType() << ")\n";
    std::cout << "   Capacity:     " << exhibit->getMaxCapacity() << "\n";
    std::cout << "   Cleanliness:  " << exhibit->getCleanliness() << "\n";
    if (i < exhibits.size() - 1) {
      std::cout << "--------------------------------------------\n";
    }
  }
  std::cout << "-----------------------------------------\n";
}

void Game::displayExhibitsNeedingCleaning() {
  std::vector<Exhibit*> exhibits = zoo_.getExhibitsNeedingCleaning();
  if (exhibits.empty()) {
    std::cout << "\nNo exhibits need cleaning right now!\n";
    return;
  }

  for (size_t i = 0; i < exhibits.size(); ++i) {
    std::cout << (i + 1) << ". " << exhibits[i]->getName() << "\n";
  }
}

void Game::purchaseExhibit() {
  std::cout << "\nPURCHASE EXHIBIT | Balance: $" << zoo_.getBalance() << "\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "1. Grassland (2-3 capacity) - $300\n";
  std::cout << "2. Forest (3-4 capacity) - $800\n";
  std::cout << "3. Jungle (4-6 capacity) - $1000\n";
  std::cout << "4. Savannna (3-5 capacity) - $1200\n";
  std::cout << "5. Arctic (4-5 capacity) - $1500\n";
  std::cout << "6. Cancel\n";
  std::cout << "-----------------------------------------\n\n";

  int choice = getPlayerInput(1, 6);
  if (choice == 6) {
    return;
  }

  std::cout << "Name the exhibit: ";
  std::string name;
  std::getline(std::cin, name);

  // random number generator
  std::random_device seed;
  std::mt19937 gen(seed());

  int capacity;
  std::unique_ptr<Exhibit> exhibit;
  switch (choice) {
    case 1: {
      std::uniform_int_distribution<> distr(2, 3);
      capacity = distr(gen);
      exhibit = std::make_unique<Exhibit>(name, "Grassland", capacity, 300.0, 15.0);
      break;
    }
    case 2: {
      std::uniform_int_distribution<> distr(3, 4);
      capacity = distr(gen);
      exhibit = std::make_unique<Exhibit>(name, "Forest", capacity, 800.0, 35.0);
      break;
    }
    case 3: {
      std::uniform_int_distribution<> distr(4, 6);
      capacity = distr(gen);
      exhibit = std::make_unique<Exhibit>(name, "Jungle", capacity, 1000.0, 45.0);
      break;
    }
    case 4: {
      std::uniform_int_distribution<> distr(3, 5);
      capacity = distr(gen);
      exhibit = std::make_unique<Exhibit>(name, "Savanna", capacity, 1200.0, 50.0);
      break;
    }
    case 5: {
      std::uniform_int_distribution<> distr(4, 5);
      capacity = distr(gen);
      exhibit = std::make_unique<Exhibit>(name, "Arctic", capacity, 1500.0, 60.0);
      break;
    }
  }

  std::cout << "Purchase " << exhibit->getName() << " for $" << exhibit->getPurchaseCost()
            << "? (1 - Yes, 2 - No)\n";

  choice = getPlayerInput(1, 6);

  if (choice == 1) {
    if (zoo_.purchaseExhibit(std::move(exhibit))) {
      updateMaxActionPoints();
      std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
    }
  }
}

void Game::sellExhibit() {
  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  std::cout << "Sell " << exhibit->getName() << " for $" << (exhibit->getPurchaseCost() / 2.0)
            << "? (1 - Yes, 2 - No)\n";
  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    if (zoo_.sellExhibit(exhibit)) {
      updateMaxActionPoints();
      std::cout << "New Balance: $" << zoo_.getBalance() << "\n";
    }
  }
}

void Game::cleanExhibit() {
  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  // check if exhibit needs cleaning first
  if (exhibit->getCleanliness() > 70) {
    std::cout << "\nExhibit does not need to be cleaned yet!\n";
    return;
  }

  if (!useActionPoint("Clean " + exhibit->getName())) {
    return;
  }

  player_.cleanExhibit(exhibit);
}

void Game::manageZoo() {
  while (true) {
    std::cout << "\nZOO MANAGEMENT\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "1. Check Balance\n";
    std::cout << "2. View Zoo Rating\n";
    std::cout << "3. Back to Main Menu\n";
    std::cout << "-----------------------------------------\n\n";

    int choice = getPlayerInput(1, 3);

    switch (choice) {
      case 1:
        checkBalance();
        break;
      case 2:
        viewZooRating();
        break;
      case 3:
        return;
    }
  }
}

void Game::checkBalance() {
  std::cout << "\nCurrent Balance: $" << zoo_.getBalance() << "\n";
}

void Game::viewZooRating() {
  double rating = zoo_.calculateZooRating();
  std::cout << "\nZoo Rating: " << rating << "/5.0 ";
  std::cout << zoo_.getRatingMessage(rating) << "\n";
  zoo_.viewZooRatingBreakdown();
}

bool Game::useActionPoint(const std::string action_description) {
  if (action_points_ <= 0) {
    std::cout << "No more action points remaining today!\n";
    std::cout << "End the day to reset your actions.\n";
    return false;
  }

  action_points_--;
  actions_.push_back(action_description);
  return true;
}

void Game::resetActionPoints() {
  action_points_ = max_action_points_;
  actions_.clear();
}

int Game::getActionPoints() const {
  return action_points_;
}

int Game::getMaxActionPoints() const {
  return max_action_points_;
}

void Game::updateMaxActionPoints() {
  // base 6 points, +1 per animal, +1 per 2 exhibits
  max_action_points_ = 6 + zoo_.getAnimalCount() + (zoo_.getExhibitCount() / 2);

  // cap at 20 points
  if (max_action_points_ > 20) {
    max_action_points_ = 20;
  }
}

void Game::endDay() {
  std::cout << "\nEND OF DAY " << zoo_.getDay() << "\n";
  std::cout << "-----------------------------------------\n";

  // action summary
  if (actions_.empty()) {
    std::cout << "No actions performed today.\n";
  } else {
    std::cout << "Actions Performed (" << (max_action_points_ - action_points_) << "/"
              << max_action_points_ << "):\n";
    for (size_t i = 0; i < actions_.size(); ++i) {
      std::cout << "  " << (i + 1) << ". " << actions_[i] << "\n";
    }
  }

  resetActionPoints();

  zoo_.advanceDay();

  if (zoo_.getBalance() <= 0) {
    std::cout << "\nGAME OVER: You went bankrupt!\n";
    running_ = false;
    return;
  }

  if (zoo_.getAnimalCount() == 0) {
    std::cout << "\nGAME OVER: No animals left!\n";
    running_ = false;
    return;
  }

  if (zoo_.getBalance() < 500) {
    std::cout << "\nLow funds! Your zoo is at risk of bankruptcy!\n";
  }

  if (zoo_.getDay() >= 8) {
    std::cout << "\nGAME COMPLETE!\n";
    std::cout << "Final balance:      $" << zoo_.getBalance() << "\n";
    std::cout << "Final animal count: " << zoo_.getAnimalCount() << "\n";

    // calculate overall score
    int score = 0;

    // financial health
    if (zoo_.getBalance() >= 2000) {
      score += 3;
    } else if (zoo_.getBalance() >= 1500) {
      score += 2;
    } else if (zoo_.getBalance() >= 1000) {
      score += 1;
    }

    // zoo rating
    double rating = zoo_.calculateZooRating();
    if (rating >= 4.5) {
      score += 3;
    } else if (rating >= 4.0) {
      score += 2;
    } else if (rating >= 3.5) {
      score += 1;
    }

    // animal diversity
    int animal_count = zoo_.getAnimalCount();
    if (animal_count >= 6) {
      score += 2;
    } else if (animal_count >= 4) {
      score += 1;
    }

    // animal welfare
    auto needy_animals = zoo_.getAnimalsNeedingAttention();
    if (needy_animals.empty()) {
      score += 2;
    } else if (needy_animals.size() < animal_count * 0.5) {
      score += 1;
    }

    // victory messages
    if (score >= 9) {
      std::cout << "Perfect! You're a master zookeeper!\n";
    } else if (score >= 7) {
      std::cout << "Excellent! Your zoo is thriving!\n";
    } else if (score >= 5) {
      std::cout << "Good! You successfully managed the zoo!\n";
    } else if (score >= 3) {
      std::cout << "You barely made it to day 7!\n";
    } else {
      std::cout << "Poor. Your zoo is in terrible condition. The animals deserve better.\n";
    }
    running_ = false;
    return;
  }

  std::cout << "\nDAY " << zoo_.getDay() << "\n";
}

void Game::exitGame() {
  std::cout << "Exit game? (1 - Yes, 2 - No)\n";
  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    std::cout << "\nExiting game...\n";
    std::cout << "Thanks for playing Zooperator " << player_.getName() << "!\n";
    running_ = false;
  }
}

void Game::displayHelp() {
  std::cout << "\nHOW TO PLAY\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "Goals:\n";
  std::cout << " - Keep the zoo running for 7 days.\n";
  std::cout << " - Keep all animals happy and healthy.\n";
  std::cout << " - Maintain a zoo rating above 3.0 stars.\n\n";
  std::cout << "Actions (limited per day):\n";
  std::cout << "  - Feed: Reduces hunger\n";
  std::cout << "  - Play: Increases happiness\n";
  std::cout << "  - Exercise: Increases health\n";
  std::cout << "  - Treat: Heals sick animals (costs $50)\n";
  std::cout << "  - Clean: Keeps exhibits attractive\n\n";
  std::cout << "Warnings:\n";
  std::cout << "  - Hungry animals lose health and can die\n";
  std::cout << "  - Unhappy animals reduce your zoo rating\n";
  std::cout << "  - A low zoo rating = fewer visitors and less revenue\n";
  std::cout << "  - Dirty exhibits will drive visitors away\n\n";
  std::cout << "Tips:\n";
  std::cout << "  - Check animals that need attention daily\n";
  std::cout << "  - Balance spending vs saving\n";
  std::cout << "  - Don't expand too fast\n";
  std::cout << "-----------------------------------------\n\n";
}
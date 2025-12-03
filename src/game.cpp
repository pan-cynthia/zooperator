#include "game.h"

#include <iostream>
#include <limits>
#include <utility>

#include "bear.h"
#include "penguin.h"
#include "rabbit.h"

Game::Game(const Player& player, std::string zoo_name)
    : player_(player), zoo_(zoo_name, 10000.00), running_(true) {}

void Game::start() {
  std::cout << "\n==============================================================\n";
  std::cout << "Welcome to Zooperator " << player_.getName() << "!\n";
  std::cout << "You'll be working as the zookeeper for: " << zoo_.getName() << ".\n";
  std::cout << "Your goal is to keep all the animals fed, happy, and healthy.\n";
  std::cout << "You'll run the zoo for 7 days.\n\n";

  setupStarterZoo();

  while (running_) {
    displayMainMenu();
    int choice = getPlayerInput(1, 5);

    switch (choice) {
      case 1:
        manageAnimals();
        break;
      case 2:
        manageExhibits();
        break;
      case 3:
        manageFinances();
        break;
      case 4:
        endDay();
        break;
      case 5:
        exitGame();
        break;
    }
  }
}

void Game::setupStarterZoo() {
  std::cout << "Setting up your starter zoo...\n";
  std::cout << "We've added a rabbit exhibit and 1 rabbit to get you started!\n\n";

  zoo_.purchaseExhibit(std::make_unique<Exhibit>("Bunny Burrow", "Grassland", 4, 500.0, 10.0));
  auto rabbit = std::make_unique<Rabbit>("Miffy", 7);
  Animal* rabbit_ptr = rabbit.get();

  zoo_.purchaseAnimal(std::move(rabbit));
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
  std::cout << "\n============== MAIN MENU ==============\n";
  std::cout << "1. Manage Animals\n";
  std::cout << "2. Manage Exhibits\n";
  std::cout << "3. Manage Finances\n";
  std::cout << "4. End Day\n";
  std::cout << "5. Exit Game\n";
  std::cout << "=======================================\n";
}

void Game::manageAnimals() {
  while (true) {
    std::cout << "\n========== ANIMAL MANAGEMENT ==========\n";
    std::cout << "1. Display All Animals\n";
    std::cout << "2. Display Animals Needing Attention\n";
    std::cout << "3. Purchase Animal\n";
    std::cout << "4. Sell Animal\n";
    std::cout << "5. Feed Animal\n";
    std::cout << "6. Play With Animal\n";
    std::cout << "7. Exercise Animal\n";
    std::cout << "8. Treat Animal\n";
    std::cout << "9. Add Animal to Exhibit\n";
    std::cout << "10. Remove Animal from Exhibit\n";
    std::cout << "11. Move Animal to Exhibit\n";
    std::cout << "12. Back to Main Menu\n";
    std::cout << "=======================================\n";

    int choice = getPlayerInput(1, 12);
    switch (choice) {
      case 1:
        displayAllAnimals();
        break;
      case 2:
        displayAnimalsNeedingAttention();
        break;
      case 3:
        purchaseAnimal();
        break;
      case 4:
        sellAnimal();
        break;
      case 5:
        feedAnimal();
        break;
      case 6:
        playWithAnimal();
        break;
      case 7:
        exerciseAnimal();
        break;
      case 8:
        treatAnimal();
        break;
      case 9:
        addAnimalToExhibit();
        break;
      case 10:
        removeAnimalFromExhibit();
        break;
      case 11:
        moveAnimalToExhibit();
        break;
      case 12:
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
  std::cout << "------------------\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    std::cout << (i + 1) << ". " << animals[i]->getName() << " the " << animals[i]->getSpecies()
              << "\n";
  }
  std::cout << (animals.size() + 1) << ". Cancel\n";

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

  std::cout << "\n================ ALL ANIMALS ================\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    Animal* animal = animals[i];
    std::cout << (i + 1) << ". " << animal->getName() << " the " << animal->getSpecies() << "\n";
    std::cout << "   Health:     " << animal->getHealthLevel() << "\n";
    std::cout << "   Hunger:     " << animal->getHungerLevel() << "\n";
    std::cout << "   Happiness:  " << animal->getHappinessLevel() << "\n";
    std::cout << "   Energy:     " << animal->getEnergyLevel() << "\n";
    Exhibit* exhibit = zoo_.findAnimalLocation(animal);
    std::cout << "   Location:   " << (exhibit ? exhibit->getName() : "None") << "\n";

    if (i < animals.size() - 1) {
      std::cout << "----------------------------------------------\n";
    }
  }
  std::cout << "==============================================\n";
}

void Game::displayAnimalsNeedingAttention() {
  std::vector<Animal*> animals = zoo_.getAnimalsNeedingAttention();
  if (animals.empty()) {
    std::cout << "No animals need attention right now!\n";
    return;
  }

  std::cout << "\n====== ANIMALS NEEDING ATTENTION ======\n";
  for (size_t i = 0; i < animals.size(); ++i) {
    Animal* animal = animals[i];
    std::cout << "----------------------------------------------------------\n";
    std::cout << (i + 1) << ". " << animal->getName() << " the " << animal->getSpecies() << "\n";
    std::cout << "   Health:    " << animal->getHealthLevel() << "\n";
    std::cout << "   Hunger:    " << animal->getHungerLevel() << "\n";
    std::cout << "   Happiness:    " << animal->getHappinessLevel() << "\n";
    std::cout << "   Energy:    " << animal->getEnergyLevel() << "\n";
  }
}

void Game::purchaseAnimal() {
  std::cout << "\n========== PURCHASE ANIMAL ==========\n";
  std::cout << "1. Rabbit - $150\n";
  std::cout << "2. Penguin - $500\n";
  std::cout << "3. Bear - $2000\n";
  std::cout << "4. Cancel\n";
  std::cout << "=====================================\n";

  int choice = getPlayerInput(1, 4);
  if (choice == 4) {
    return;
  }

  std::cout << "Name your animal: ";
  std::string name;
  std::getline(std::cin, name);

  std::unique_ptr<Animal> animal;
  switch (choice) {
    case 1:
      animal = std::make_unique<Rabbit>(name, 2);
      break;
    case 2:
      animal = std::make_unique<Penguin>(name, 3);
      break;
    case 3:
      animal = std::make_unique<Bear>(name, 5);
      break;
  }

  std::cout << "Purchase " << animal->getName() << " the " << animal->getSpecies() << " for $"
            << animal->getPurchaseCost() << "? (1 - Yes, 2 - No): ";

  choice = getPlayerInput(1, 2);

  if (choice == 1) {
    zoo_.purchaseAnimal(std::move(animal));
  }
}

void Game::sellAnimal() {
  // int animalIndex = chooseAnimalIndex();
  // Animal* animal = zoo_.getAnimal(animalIndex);
  std::cout << "\n========== SELL ANIMAL ==========\n";
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }

  std::cout << "Sell " << animal->getName() << " the " << animal->getSpecies() << " for $"
            << (animal->getPurchaseCost() / 2.0) << "? (1 - Yes, 2 - No): ";
  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    zoo_.sellAnimal(animal);
  }
}

void Game::feedAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }
  player_.feedAnimal(zoo_, animal);
}

void Game::playWithAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }
  player_.playWithAnimal(animal);
}

void Game::exerciseAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }
  player_.exerciseAnimal(animal);
}

void Game::treatAnimal() {
  Animal* animal = chooseAnimal();
  if (!animal) {
    return;
  }
  player_.treatAnimal(zoo_, animal);
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
    std::cout << "\n========== EXHIBIT MANAGEMENT ==========\n";
    std::cout << "1. Display All Exhibits\n";
    std::cout << "2. Display Exhibits Needing Cleaning\n";
    std::cout << "3. Purchase Exhibit\n";
    std::cout << "4. Sell Exhibit\n";
    std::cout << "5. Clean Exhibit\n";
    std::cout << "6. Back to Main Menu\n";
    std::cout << "=====================================\n";

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

  std::cout << "Choose an exhibit:\n";
  std::cout << "------------------\n";
  for (size_t i = 0; i < exhibits.size(); ++i) {
    std::cout << (i + 1) << ". " << exhibits[i]->getName() << "\n";
  }

  std::cout << (exhibits.size() + 1) << ". Cancel\n";

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

  std::cout << "\n================= EXHIBITS =================\n";
  for (size_t i = 0; i < exhibits.size(); ++i) {
    Exhibit* exhibit = exhibits[i];
    std::cout << (i + 1) << ". " << exhibit->getName() << " (" << exhibit->getType() << ")\n";
    std::cout << "   Capacity:     " << exhibit->getMaxCapacity() << "\n";
    std::cout << "   Cleanliness:  " << exhibit->getCleanliness() << "\n";
    if (i < exhibits.size() - 1) {
      std::cout << "--------------------------------------------\n";
    }
  }
  std::cout << "=============================================\n";
}

void Game::displayExhibitsNeedingCleaning() {
  std::vector<Exhibit*> exhibits = zoo_.getExhibitsNeedingCleaning();
  if (exhibits.empty()) {
    std::cout << "No exhibits need cleaning right now!\n";
    return;
  }

  for (size_t i = 0; i < exhibits.size(); ++i) {
    std::cout << (i + 1) << ". " << exhibits[i]->getName() << "\n";
  }
}

void Game::purchaseExhibit() {
  std::cout << "\n========== PURCHASE EXHIBIT ==========\n";
  std::cout << "1. Grassland (2 Capacity) - $500\n";
  std::cout << "2. Forest (3 Capacity) - $1500\n";
  std::cout << "3. Arctic (5 Capacity)- $2500\n";
  std::cout << "4. Cancel\n";
  std::cout << "=======================================\n";

  int choice = getPlayerInput(1, 4);
  if (choice == 4) {
    return;
  }

  std::cout << "Name the exhibit: ";
  std::string name;
  std::getline(std::cin, name);

  std::unique_ptr<Exhibit> exhibit;
  switch (choice) {
    case 1:
      exhibit = std::make_unique<Exhibit>(name, "Grassland", 2, 500.0, 10.0);
      break;
    case 2:
      exhibit = std::make_unique<Exhibit>(name, "Forest", 3, 1500.0, 30.0);
      break;
    case 3:
      exhibit = std::make_unique<Exhibit>(name, "Arctic", 5, 2500.0, 50.0);
      break;
  }

  std::cout << "Purchase " << exhibit->getName() << " for $" << exhibit->getPurchaseCost()
            << "? (1 - Yes, 2 - No): ";

  choice = getPlayerInput(1, 2);

  if (choice == 1) {
    zoo_.purchaseExhibit(std::move(exhibit));
  }
}

void Game::sellExhibit() {
  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  std::cout << "Sell " << exhibit->getName() << " for $" << (exhibit->getPurchaseCost() / 2.0)
            << "? (1 - Yes, 2 - No): ";
  int choice = getPlayerInput(1, 2);

  if (choice == 1) {
    zoo_.sellExhibit(exhibit);
  }
}

void Game::cleanExhibit() {
  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }
  // check if exhibit needs cleaning first
  if (exhibit->getCleanliness() > 70) {
    std::cout << "Exhibit does not need to be cleaned yet!\n";
    return;
  }

  player_.cleanExhibit(exhibit);
}

void Game::manageFinances() {
  while (true) {
    std::cout << "\n========== FINANCIAL MANAGEMENT ==========\n";
    std::cout << "1. Check Balance\n";
    std::cout << "2. Back to Main Menu\n";
    std::cout << "==========================================\n";

    int choice = getPlayerInput(1, 2);

    switch (choice) {
      case 1:
        checkBalance();
        break;
      case 2:
        return;
    }
  }
}

void Game::checkBalance() {
  std::cout << "\nCurrent Balance: $" << zoo_.getBalance() << "\n";
}

void Game::endDay() {
  std::cout << "\n---------- End of Day " << zoo_.getDay() << " ----------\n";

  zoo_.advanceDay();

  if (zoo_.getBalance() <= 0) {
    std::cout << "\n*********** GAME OVER ***********\n";
    std::cout << "Game over. You went bankrupt!\n";
    running_ = false;
    return;
  }

  if (zoo_.getAnimalCount() == 0) {
    std::cout << "\n*********** GAME OVER ***********\n";
    std::cout << "Game over: No animals left\n";
    running_ = false;
    return;
  }

  if (zoo_.getDay() >= 7) {
    std::cout << "Congratulations! You survived 7 days!\n";
    std::cout << "Final balance: $" << zoo_.getBalance() << "\n";
    std::cout << "Final animal count: " << zoo_.getAnimalCount() << "\n";
    running_ = false;
    return;
  }
}

void Game::exitGame() {
  std::cout << "Exiting game...\n";
  std::cout << "Thanks for playing Zooperator " << player_.getName() << "!\n";
  running_ = false;
}

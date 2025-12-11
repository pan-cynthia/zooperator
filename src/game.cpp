#include "game.h"

#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <utility>

#include "animal.h"
#include "bear.h"
#include "elephant.h"
#include "lion.h"
#include "monkey.h"
#include "penguin.h"
#include "rabbit.h"
#include "tortoise.h"

Game::Game(const Player& player, std::string zoo_name)
    : player_(player),
      zoo_(zoo_name, 2000.0),
      running_(true),
      action_points_(3),
      max_action_points_(3) {
  setupDailyMissions(1);
}

void Game::setupDailyMissions(int day) {
  missions_.clear();

  switch (day) {
    case 1:
      missions_.push_back(Mission(true, "Purchase 1 animal", MissionType::OWN_X_ANIMALS, 1));
      missions_.push_back(Mission(true, "Purchase 1 exhibit", MissionType::OWN_X_EXHIBITS, 1));
      missions_.push_back(
          Mission(true, "Add animal to an exhibit", MissionType::ADD_ANIMAL_TO_EXHIBIT));
      missions_.push_back(Mission(false, "End the day with a balance of at least $250",
                                  MissionType::BALANCE_AT_LEAST, 0, 250.0, 100.0, true));
      missions_.push_back(Mission(false, "Zoo rating above 4.5", MissionType::ZOO_RATING_ABOVE, 0,
                                  4.5, 100.0, true));
      break;

    case 2:
      missions_.push_back(Mission(true, "Have at least 2 animals", MissionType::OWN_X_ANIMALS, 2));
      missions_.push_back(
          Mission(true, "Own at least 2 different species", MissionType::OWN_X_SPECIES, 2));
      missions_.push_back(Mission(false, "Achieve zoo rating above 3.0",
                                  MissionType::ZOO_RATING_ABOVE, 0, 3.0, 200.0, true));
      break;

    case 3:
      missions_.push_back(Mission(true, "No animals need attention",
                                  MissionType::NO_ANIMALS_NEED_ATTENTION, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(true, "Achieve zoo rating above 3.5",
                                  MissionType::ZOO_RATING_ABOVE, 0, 3.5, 0.0, true));
      missions_.push_back(Mission(false, "All animals in preferred habitats",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 200.0, true));
      missions_.push_back(
          Mission(false, "Have at least 3 animals", MissionType::OWN_X_ANIMALS, 3, 0.0, 300.0));
      break;

    case 4:
      missions_.push_back(Mission(true, "Have at least 3 animals", MissionType::OWN_X_ANIMALS, 3));
      missions_.push_back(
          Mission(true, "Have at least 3 different species", MissionType::OWN_X_SPECIES, 3));
      missions_.push_back(Mission(false, "Achieve a zoo rating above 4.0",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 400.0, true));
      missions_.push_back(Mission(false, "All exhibits at 80+ cleanliness",
                                  MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, 80, 0.0, 250.0,
                                  true));
      break;

    case 5:
      missions_.push_back(Mission(true, "Have at least 4 animals", MissionType::OWN_X_ANIMALS, 4));
      missions_.push_back(Mission(true, "No animals need attention",
                                  MissionType::NO_ANIMALS_NEED_ATTENTION, 0, 0.0, 0.0, true));
      missions_.push_back(
          Mission(true, "Balance above $800", MissionType::BALANCE_AT_LEAST, 0, 800.0, 0.0, true));
      missions_.push_back(
          Mission(false, "Have at least 2 exhibits", MissionType::OWN_X_EXHIBITS, 2, 0.0, 400.0));
      break;

    case 6:
      missions_.push_back(
          Mission(true, "Have at least 2 exhibits", MissionType::OWN_X_EXHIBITS, 2));
      missions_.push_back(Mission(true, "No homeless animals", MissionType::NO_HOMELESS_ANIMALS));
      missions_.push_back(Mission(true, "Achieve zoo rating above 3.5",
                                  MissionType::ZOO_RATING_ABOVE, 0, 3.5, 0.0, true));
      missions_.push_back(
          Mission(false, "Have at least 5 animals", MissionType::OWN_X_ANIMALS, 5, 0.0, 400.0));
      missions_.push_back(Mission(false, "Have at least 4 different species",
                                  MissionType::OWN_X_SPECIES, 4, 0.0, 350.0));
      break;

    case 7:
      missions_.push_back(Mission(true, "Have at least 5 animals", MissionType::OWN_X_ANIMALS, 5));
      missions_.push_back(
          Mission(true, "No sick animals", MissionType::NO_SICK_ANIMALS, 0, 0.0, 0.0, true));
      missions_.push_back(Mission(true, "Achieve zoo rating above 4.0",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 0.0, true));
      missions_.push_back(Mission(false, "All animals are in preferred habitats",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 600.0));
      missions_.push_back(
          Mission(false, "Have at least 3 exhibits", MissionType::OWN_X_EXHIBITS, 3, 0.0, 500.0));
      break;

    case 8:
      missions_.push_back(Mission(true, "Have at least 6 animals", MissionType::OWN_X_ANIMALS, 6));
      missions_.push_back(
          Mission(true, "Have at least 4 different species", MissionType::OWN_X_SPECIES, 4));
      missions_.push_back(Mission(true, "Achieve zoo rating above 4.0",
                                  MissionType::ZOO_RATING_ABOVE, 0, 4.0, 0.0, true));
      missions_.push_back(Mission(false, "Own a bear, lion, or elephant",
                                  MissionType::OWN_SPECIAL_ANIMAL, 0, 0.0, 600.0));
      missions_.push_back(Mission(false, "Balance above $1500", MissionType::BALANCE_AT_LEAST, 0,
                                  1500.0, 500.0, true));
      break;

    case 9:
      missions_.push_back(Mission(true, "Have at least 7 animals", MissionType::OWN_X_ANIMALS, 7));
      missions_.push_back(
          Mission(true, "No animals need attention", MissionType::NO_ANIMALS_NEED_ATTENTION));
      missions_.push_back(
          Mission(true, "Zoo rating above 4.0", MissionType::ZOO_RATING_ABOVE, 0, 4.0, 0.0, true));
      missions_.push_back(Mission(false, "Have at least 5 different species",
                                  MissionType::OWN_X_SPECIES, 5, 0.0, 700.0));
      missions_.push_back(Mission(false, "All exhibits at 80+ cleanliness",
                                  MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X, 80, 0.0, 400.0,
                                  true));
      break;

    case 10:
      missions_.push_back(Mission(true, "No homeless animals", MissionType::NO_HOMELESS_ANIMALS));
      missions_.push_back(
          Mission(true, "Zoo rating above 4.0", MissionType::ZOO_RATING_ABOVE, 0, 4.0, 0.0, true));
      missions_.push_back(Mission(false, "All animals are in preferred habitats",
                                  MissionType::PREFERRED_HABITATS, 0, 0.0, 800.0));
      missions_.push_back(
          Mission(false, "Have at least 8 animals", MissionType::OWN_X_ANIMALS, 8, 0.0, 600.0));
      missions_.push_back(
          Mission(false, "Own an elephant", MissionType::OWN_ELEPHANT, 0, 0.0, 500.0));
      missions_.push_back(Mission(false, "Own at least 6 different species",
                                  MissionType::OWN_X_SPECIES, 0, 0.0, 1000.0));
      missions_.push_back(Mission(false, "Balance above $2500", MissionType::BALANCE_AT_LEAST, 0,
                                  2500.0, 500.0, true));
      break;
  }
}

void Game::checkMissions(bool end_of_day) {
  for (size_t i = 0; i < missions_.size(); ++i) {
    Mission& mission = missions_[i];
    if (mission.completed) {
      continue;
    }

    // don't check end of day missions unless end of day
    if (mission.end_of_day && !end_of_day) {
      continue;
    }

    bool completed = false;

    switch (mission.type) {
      case MissionType::ADD_ANIMAL_TO_EXHIBIT:
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (zoo_.findAnimalLocation(animal)) {
            completed = true;
            break;
          }
        }
        break;

      case MissionType::OWN_X_ANIMALS:
        completed = zoo_.getAnimalCount() >= static_cast<size_t>(mission.int_param);
        break;

      case MissionType::OWN_X_SPECIES: {
        std::set<std::string> species;
        for (const Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        completed = species.size() >= static_cast<size_t>(mission.int_param);
        break;
      }

      case MissionType::OWN_X_EXHIBITS:
        completed = zoo_.getExhibitCount() >= static_cast<size_t>(mission.int_param);
        break;

      case MissionType::NO_ANIMALS_NEED_ATTENTION:
        completed = zoo_.getAnimalsNeedingAttention().empty();
        break;

      case MissionType::NO_SICK_ANIMALS:
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getHealthLevel() < 50) {
            completed = false;
            break;
          }
        }
        completed = true;
        break;

      case MissionType::NO_HOMELESS_ANIMALS:
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (zoo_.findAnimalLocation(animal) == nullptr) {
            completed = false;
            break;
          }
        }
        completed = true;
        break;

      case MissionType::PREFERRED_HABITATS:
        for (Animal* animal : zoo_.getAllAnimals()) {
          Exhibit* exhibit = zoo_.findAnimalLocation(animal);
          if (!exhibit || exhibit->getType() != animal->getPreferredHabitat()) {
            completed = false;
            break;
          }
        }
        completed = true;
        break;

      case MissionType::EXHIBITS_CLEANLINESS_AT_LEAST_X:
        for (Exhibit* exhibit : zoo_.getAllExhibits()) {
          if (exhibit->getCleanliness() < mission.int_param) {
            completed = false;
            break;
          }
        }
        completed = true;
        break;

      case MissionType::BALANCE_AT_LEAST:
        completed = zoo_.getBalance() >= mission.float_param;
        break;

      case MissionType::ZOO_RATING_ABOVE:
        completed = zoo_.calculateZooRating() >= mission.float_param;
        break;

      case MissionType::OWN_ELEPHANT:
        for (const Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Elephant") {
            completed = true;
            break;
          }
        }
        break;

      case MissionType::OWN_SPECIAL_ANIMAL: {
        bool owns_bear = false;
        bool owns_lion = false;
        bool owns_elephant = false;
        for (const Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getSpecies() == "Bear") {
            owns_bear = true;
          } else if (animal->getSpecies() == "Lion") {
            owns_lion = true;
          } else if (animal->getSpecies() == "Elephant") {
            owns_elephant = true;
          }
        }
        completed = owns_bear || owns_lion || owns_elephant;
        break;
      }
    }
    if (completed) {
      completeMission(i);
    }
  }
}

void Game::completeMission(size_t mission_index) {
  Mission& mission = missions_[mission_index];
  mission.completed = true;

  std::cout << "\nMission Complete: " << mission.description << "\n";

  if (mission.reward_amount > 0) {
    zoo_.addMoney(mission.reward_amount);
    std::cout << "Reward: $" << mission.reward_amount << "\n";
  }
}

void Game::displayMissions() {
  std::cout << "\nDAY " << zoo_.getDay() << " MISSIONS\n";
  std::cout << "-----------------------------------------\n";

  std::cout << "Required:\n";
  for (const Mission& mission : missions_) {
    if (mission.required) {
      std::cout << " - " << mission.description << (mission.completed ? " ⎷" : " X") << "\n";
    }
  }

  bool has_optional = false;

  for (const Mission& mission : missions_) {
    if (!mission.required) {
      has_optional = true;
      break;
    }
  }
  if (has_optional) {
    std::cout << "\nOptional:\n";
    for (const Mission& mission : missions_) {
      if (!mission.required) {
        std::cout << " - " << mission.description << (mission.completed ? " ⎷" : " X") << "\n";
      }
    }
  }
  std::cout << "-----------------------------------------\n";
}

bool Game::canAdvanceDay() {
  for (const Mission& mission : missions_) {
    if (mission.required && !mission.completed) {
      return false;
    }
  }
  return true;
}

bool Game::checkMissionsImpossible() {
  for (const Mission& mission : missions_) {
    if (!mission.required || mission.completed) {
      continue;
    }

    switch (mission.type) {
      case MissionType::ADD_ANIMAL_TO_EXHIBIT: {
        // need at least one animal and one exhibit
        if (zoo_.getAnimalCount() == 0 || zoo_.getExhibitCount() == 0) {
          double balance_needed = 0.0;
          if (zoo_.getAnimalCount() == 0) {
            balance_needed += 150.0;
          }
          if (zoo_.getExhibitCount() == 0) {
            balance_needed += 300.0;
          }
          if (zoo_.getBalance() < balance_needed) {
            return true;
          }
        }
        break;
      }

      case MissionType::OWN_X_ANIMALS: {
        std::set<std::string> species;
        for (Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        int animals_needed = mission.int_param - species.size();
        if (zoo_.getBalance() < (animals_needed * 150.0)) {
          return true;
        }
        break;
      }

      case MissionType::OWN_X_SPECIES: {
        std::set<std::string> species;
        for (Animal* animal : zoo_.getAllAnimals()) {
          species.insert(animal->getSpecies());
        }
        int species_needed = mission.int_param - species.size();
        if (zoo_.getBalance() < (species_needed * 150.0)) {
          return true;
        }
        break;
      }

      case MissionType::OWN_X_EXHIBITS: {
        int exhibits_needed = mission.int_param - zoo_.getExhibitCount();
        if (zoo_.getBalance() < (exhibits_needed * 300.0)) {
          return true;
        }
        break;
      }

      case MissionType::NO_ANIMALS_NEED_ATTENTION: {
        int needy_animals = 0;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->needsAttention()) {
            needy_animals++;
          }
        }
        // estimated treatment cost: treatment ($50) + feeding ($5-50)
        double treatment_cost = needy_animals * 100.0;
        if (zoo_.getBalance() < treatment_cost && action_points_ == 0) {
          return true;
        }
        break;
      }

      case MissionType::NO_SICK_ANIMALS: {
        int sick_animals = 0;
        for (Animal* animal : zoo_.getAllAnimals()) {
          if (animal->getHealthLevel() < 50) {
            sick_animals++;
          }
        }
        // estimated treatment cost: treatment ($50) + feeding ($5-50)
        double treatment_cost = sick_animals * 100.0;
        if (zoo_.getBalance() < treatment_cost && action_points_ == 0) {
          return true;
        }
        break;
      }

      default:
        break;
    }
  }
  return false;
}

void Game::start() {
  std::cout << "\nWelcome to Zooperator " << player_.getName() << "!\n";
  std::cout << "You'll be working as the zookeeper for: " << zoo_.getName() << ".\n\n";
  std::cout << "Goals\n";
  std::cout << " - Keep the zoo running for 10 days.\n";
  std::cout << " - Complete all the required missions each day.\n";
  std::cout << " - Keep all animals happy and healthy.\n";
  std::cout << " - Maintain a zoo rating above 3.0 stars.\n";

  std::cout << "\nDAY " << zoo_.getDay() << "\n";

  while (running_) {
    displayMainMenu();
    int choice = getPlayerInput(0, 6);

    switch (choice) {
      case 0:
        displayHelp();
        break;
      case 1:
        displayMissions();
        break;
      case 2:
        manageAnimals();
        break;
      case 3:
        manageExhibits();
        break;
      case 4:
        manageZoo();
        break;
      case 5:
        endDay();
        break;
      case 6:
        exitGame();
        break;
    }
  }
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
  std::cout << "0. Help\n";
  std::cout << "1. View Missions\n";
  std::cout << "2. Manage Animals\n";
  std::cout << "3. Manage Exhibits\n";
  std::cout << "4. Manage Zoo\n";
  std::cout << "5. End Day\n";
  std::cout << "6. Exit Game\n";
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
    if (exhibit) {
      if (exhibit->getType() == animal->getPreferredHabitat()) {
        std::cout << "   Location:   " << exhibit->getName() << " (Perfect Match!)\n";
      } else {
        std::cout << "   Location:   " << exhibit->getName() << " (Wrong Habitat!)\n";
      }
    } else {
      std::cout << "   Location:   Homeless\n";
    }

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
  std::cout << "1. Rabbit   - $150   [Grassland]\n";
  std::cout << "2. Tortoise - $250   [Grassland]\n";
  std::cout << "3. Penguin  - $400   [Arctic]\n";
  std::cout << "4. Monkey   - $600   [Jungle]\n";
  std::cout << "5. Bear     - $1000  [Forest]\n";
  std::cout << "6. Lion     - $1200  [Savanna]\n";
  std::cout << "7. Elephant - $1500  [Savanna]\n";
  std::cout << "8. Cancel\n";
  std::cout << "-----------------------------------------\n\n";

  int choice = getPlayerInput(1, 8);
  if (choice == 8) {
    return;
  }

  std::cout << "\nName your animal: ";
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
  std::cout << " - Daily Cost: $" << (animal->getFeedingCost() + animal->getMaintenanceCost())
            << " (Feeding: $" << animal->getFeedingCost() << ", Maintenance: $"
            << animal->getMaintenanceCost() << ")\n";
  std::cout << " - Preferred Habitat: " << animal->getPreferredHabitat() << "\n";
  choice = getPlayerInput(1, 2);

  if (choice == 1) {
    if (zoo_.purchaseAnimal(std::move(animal))) {
      updateMaxActionPoints();
      std::cout << "New Balance: $" << zoo_.getBalance() << "\n";

      std::vector<Animal*> animals = zoo_.getAllAnimals();
      Animal* new_animal = animals.back();

      std::cout << "\nAssign " << new_animal->getName()
                << " to an exhibit now? (1 - Now, 2 - Later)\n";
      std::cout << "(Animals without exhibits lose health/happiness daily!)\n";

      int assign = getPlayerInput(1, 2);
      if (assign == 1) {
        Exhibit* exhibit = chooseExhibit();
        if (exhibit) {
          zoo_.addAnimalToExhibit(new_animal, exhibit);
        }
      }
      checkMissions(false);
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
  checkMissions(false);
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
    std::cout << "3. Rename Exhibit\n";
    std::cout << "4. Purchase Exhibit\n";
    std::cout << "5. Sell Exhibit\n";
    std::cout << "6. Clean Exhibit (1 AP)\n";
    std::cout << "7. Back to Main Menu\n";
    std::cout << "-----------------------------------------\n\n";

    int choice = getPlayerInput(1, 7);
    switch (choice) {
      case 1:
        displayAllExhibits();
        break;
      case 2:
        displayExhibitsNeedingCleaning();
        break;
      case 3:
        renameExhibit();
        break;
      case 4:
        purchaseExhibit();
        break;
      case 5:
        sellExhibit();
        break;
      case 6:
        cleanExhibit();
        break;
      case 7:
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
    std::cout << "   Capacity:     " << exhibit->getCapacityUsed() << "/"
              << exhibit->getMaxCapacity() << "\n";
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

void Game::renameExhibit() {
  Exhibit* exhibit = chooseExhibit();
  if (!exhibit) {
    return;
  }

  std::string old_name = exhibit->getName();
  std::cout << "Enter new name: ";
  std::string name;
  std::getline(std::cin, name);

  std::cout << "Rename Exhibit " << old_name << " to Exhibit " << name << "? (1 - Yes, 2 - No)\n";
  int choice = getPlayerInput(1, 2);
  if (choice == 1) {
    exhibit->setName(name);
    std::cout << "Renamed Exhibit " << old_name << " to Exhibit " << name << ".\n";
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

      checkMissions(false);
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
  checkMissions(false);
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
  // base 3 points, +1 per animal, +1 per 2 exhibits
  max_action_points_ = 3 + zoo_.getAnimalCount() + (zoo_.getExhibitCount() / 2);

  // cap at 20 points
  if (max_action_points_ > 20) {
    max_action_points_ = 20;
  }
}

void Game::endDay() {
  zoo_.calculateEndOfDayStats();

  checkMissions(true);
  displayMissions();

  if (checkMissionsImpossible()) {
    std::cout << "\nGAME OVER: You failed a required mission!\n";
    running_ = false;
    return;
  }

  if (!canAdvanceDay()) {
    std::cout << "\nCannot advance to next day!\n";
    std::cout << "Complete all required missions first.\n";
    return;
  }

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

  if (zoo_.getDay() <= 10) {
    setupDailyMissions(zoo_.getDay());
  }

  if (zoo_.getDay() >= 11) {
    handleGameCompletion();
    return;
  }

  zoo_.displayEndOfDaySummary();

  std::cout << "\nDAY " << zoo_.getDay() << "\n";

  checkMissions(false);
}

void Game::handleGameCompletion() {
  double rating = zoo_.calculateZooRating();

  std::cout << "\nGAME COMPLETE!\n";
  std::cout << "-----------------------------------------\n";
  std::cout << "Final balance: $" << zoo_.getBalance() << "\n";
  std::cout << "Animals: " << zoo_.getAnimalCount() << "\n";
  std::cout << "Zoo rating: " << rating << "/5.0\n";
  std::cout << "-----------------------------------------\n\n";

  std::cout << "PERFOMANCE REVIEW\n";
  std::cout << "-----------------------------------------\n";

  // calculate overall score
  int score = 0;

  // financial health
  if (zoo_.getBalance() >= 2000) {
    std::cout << "Excellent finances! (+3 points)\n";
    score += 3;
  } else if (zoo_.getBalance() >= 1500) {
    std::cout << "Strong finances! (+2 points)\n";
    score += 2;
  } else if (zoo_.getBalance() >= 1000) {
    std::cout << "Financially stable! (+1 point)\n";
    score += 1;
  } else {
    std::cout << "Poor finances. (+0 points)\n";
  }

  if (rating >= 4.5) {
    std::cout << "Outstanding zoo! (+3 points)\n";
    score += 3;
  } else if (rating >= 4.0) {
    std::cout << "Excellent zoo! (+2 points)\n";
    score += 2;
  } else if (rating >= 3.5) {
    std::cout << "Good zoo! (+1 point)\n";
    score += 1;
  } else if (rating >= 3.0) {
    std::cout << "Acceptable zoo. (+0 points)\n";
  } else {
    std::cout << "Poor rating. (+0 points)\n";
  }

  // animal diversity
  int animal_count = zoo_.getAnimalCount();
  if (animal_count >= 6) {
    std::cout << "Diverse zoo! (+2 points)\n";
    score += 2;
  } else if (animal_count >= 4) {
    std::cout << "Good collection! (+1 point)\n";
    score += 1;
  } else {
    std::cout << "Small collection! (+0 points)\n";
  }

  // animal welfare
  auto needy_animals = zoo_.getAnimalsNeedingAttention();
  if (needy_animals.empty()) {
    std::cout << "All animals are healthy! (+2 points)\n";
    score += 2;
  } else if (needy_animals.size() < animal_count * 0.5) {
    std::cout << "Most animals are healthy! (+1 point)\n";
    score += 1;
  } else {
    std::cout << "Many animals are being neglected! (+0 points)\n";
  }

  std::cout << "FINAL SCORE: " << score << "/10\n\n";

  // victory messages
  if (score >= 9) {
    std::cout << "Perfect Ending!\n";
    std::cout << "You're a master zookeeper!\n";
  } else if (score >= 7) {
    std::cout << "Excellent Ending!\n";
    std::cout << "Your zoo is thriving!\n";
  } else if (score >= 5) {
    std::cout << "Good Ending!\n";
    std::cout << "You successfully managed the zoo!\n";
  } else if (score >= 3) {
    std::cout << "Survival Ending!\n";
    std::cout << "You made it but barely!\n";
  } else {
    std::cout << "Poor Ending!\n";
    std::cout << "Your zoo is in terrible condition. The animals deserve better.\n";
  }
  running_ = false;
  return;
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
  std::cout << " - Keep the zoo running for 7 days\n";
  std::cout << " - Keep all animals happy and healthy\n";
  std::cout << " - Aim for a zoo rating above 4 stars\n";
  std::cout << " - Maintain a balance of $2000+\n\n";

  std::cout << "Actions (Limited Per Day):\n";
  std::cout << " - Each action costs 1 action point (1 AP)\n";
  std::cout << " - Some actions also cost money\n";
  std::cout << " - Feed ($): Reduces hunger\n";
  std::cout << " - Play: Increases happiness\n";
  std::cout << " - Exercise: Increases health\n";
  std::cout << " - Treat ($50): Heals sick animals\n";
  std::cout << " - Clean: Keeps exhibits attractive\n\n";

  std::cout << "Warnings:\n";
  std::cout << "  - Neglected animals will die\n";
  std::cout << "  - Unhappy animals reduce your zoo rating\n";
  std::cout << "  - Homeless animals lose happiness/health daily\n";
  std::cout << "  - Low rating = less visitors = less revenue\n";
  std::cout << "  - Dirty exhibits drive visitors away\n\n";

  std::cout << "Habitats:\n";
  std::cout << "  - Animals prefer certain exhibit types\n";
  std::cout << "     - Correct habitat: +3 happiness/day\n";
  std::cout << "     - Wrong habitat: -2 happiness/day\n";
  std::cout << "     - No exhibit: -15 happiness/day, -5 health/day\n\n";

  std::cout << "Habitat Guide:\n";
  std::cout << " Grassland - Rabbit                    \n";
  std::cout << " Forest    - Bear                      \n";
  std::cout << " Arctic    - Penguin                   \n";
  std::cout << " Jungle    - Monkey                    \n";
  std::cout << " Savanna   - Elephant, Lion            \n\n";

  std::cout << "Tips:\n";
  std::cout << "  - Check 'Animals Needing Attention' daily\n";
  std::cout << "  - Balance spending vs saving\n";
  std::cout << "  - Don't expand too fast\n";
  std::cout << "-----------------------------------------\n\n";
}

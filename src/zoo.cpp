#include "zoo.h"

#include <algorithm>
#include <iostream>

Zoo::Zoo(std::string name, double starting_balance)
    : name_(std::move(name)), day_(1), balance_(starting_balance) {}

// getters
const std::string& Zoo::getName() const {
  return name_;
}

int Zoo::getDay() const {
  return day_;
}

double Zoo::getBalance() const {
  return balance_;
}

// animal management
bool Zoo::purchaseAnimal(std::unique_ptr<Animal> animal) {
  double cost = animal->getPurchaseCost();
  if (balance_ < cost) {
    std::cout << "Insufficient funds, cannot purchase animal.\n";
    return false;
  }

  std::cout << "Purchased " << animal->getName() << " the " << animal->getSpecies() << " for $"
            << cost << ".\n";
  balance_ -= cost;
  animals_.push_back(std::move(animal));
  return true;
}

bool Zoo::sellAnimal(Animal* animal) {
  if (!animal) {
    return false;
  }

  auto it =
      std::find_if(animals_.begin(), animals_.end(),
                   [animal](const std::unique_ptr<Animal>& ptr) { return ptr.get() == animal; });
  if (it == animals_.end()) {
    std::cout << "Animal not found in zoo!\n";
    return false;
  }

  // remove animal from exhibit before selling
  Exhibit* exhibit = findAnimalLocation(animal);
  if (exhibit) {
    exhibit->removeAnimal(animal);
  }

  double sell_price = (*it)->getPurchaseCost() / 2.0;

  std::cout << "Sold " << (*it)->getName() << " the " << (*it)->getSpecies() << " for $"
            << sell_price << "!\n";
  balance_ += sell_price;

  animals_.erase(it);
  return true;
}

Animal* Zoo::getAnimal(size_t index) {
  if (index >= animals_.size()) {
    return nullptr;
  }
  return animals_[index].get();
}

std::vector<Animal*> Zoo::getAllAnimals() {
  std::vector<Animal*> animals;
  for (const auto& ptr : animals_) {
    animals.push_back(ptr.get());
  }
  return animals;
}

std::vector<Animal*> Zoo::getAnimalsNeedingAttention() {
  std::vector<Animal*> animals;
  for (const auto& ptr : animals_) {
    if (ptr->needsAttention()) {
      animals.push_back(ptr.get());
    }
  }
  return animals;
}

size_t Zoo::getAnimalCount() const {
  return animals_.size();
}

// exhibit management
bool Zoo::purchaseExhibit(std::unique_ptr<Exhibit> exhibit) {
  double cost = exhibit->getPurchaseCost();
  if (balance_ < cost) {
    std::cout << "Insufficient funds, cannot purchase exhibit.\n";
    return false;
  }

  std::cout << "Purchased Exhibit " << exhibit->getName() << " for $" << cost << ".\n";
  balance_ -= cost;
  exhibits_.push_back(std::move(exhibit));
  return true;
}

bool Zoo::sellExhibit(Exhibit* exhibit) {
  if (!exhibit) {
    return false;
  }

  auto it =
      std::find_if(exhibits_.begin(), exhibits_.end(),
                   [exhibit](const std::unique_ptr<Exhibit>& ptr) { return ptr.get() == exhibit; });
  if (it == exhibits_.end()) {
    std::cout << "Exhibit not found in zoo.\n";
    return false;
  }

  (*it)->removeAllAnimalsFromExhibit();

  double sell_price = (*it)->getPurchaseCost() / 2.0;
  std::cout << "Sold " << (*it)->getName() << " for $" << sell_price << "!\n";
  balance_ += sell_price;

  exhibits_.erase(it);
  return true;
}

Exhibit* Zoo::getExhibit(size_t index) {
  if (index >= exhibits_.size()) {
    return nullptr;
  }
  return exhibits_[index].get();
}

std::vector<Exhibit*> Zoo::getAllExhibits() {
  std::vector<Exhibit*> exhibits;
  for (const auto& ptr : exhibits_) {
    exhibits.push_back(ptr.get());
  }
  return exhibits;
}

std::vector<Exhibit*> Zoo::getExhibitsNeedingCleaning() {
  std::vector<Exhibit*> exhibits;
  for (const auto& ptr : exhibits_) {
    if (ptr->needsCleaning()) {
      exhibits.push_back(ptr.get());
    }
  }
  return exhibits;
}

size_t Zoo::getExhibitCount() const {
  return exhibits_.size();
}

Exhibit* Zoo::findAnimalLocation(Animal* animal) {
  if (!animal) {
    return nullptr;
  }

  for (const auto& ptr : exhibits_) {
    if (ptr->containsAnimal(animal)) {
      return ptr.get();
    }
  }
  return nullptr;
}

bool Zoo::addAnimalToExhibit(Animal* animal, Exhibit* exhibit) {
  if (!animal || !exhibit) {
    return false;
  }

  auto it =
      std::find_if(animals_.begin(), animals_.end(),
                   [animal](const std::unique_ptr<Animal>& ptr) { return ptr.get() == animal; });
  if (it == animals_.end()) {
    std::cout << "Animal not found in zoo.\n";
    return false;
  }

  if (exhibit->containsAnimal(animal)) {
    std::cout << "Animal is already in this exhibit.\n";
    return false;
  }

  // remove animal from current exhibit if needed
  Exhibit* current_exhibit = findAnimalLocation(animal);
  if (current_exhibit) {
    current_exhibit->removeAnimal(animal);
  }

  if (!exhibit->addAnimal(animal)) {
    std::cout << "Failed to add animal to exhibit.\n";
    return false;
  }

  return true;
}

bool Zoo::removeAnimalFromExhibit(Animal* animal, Exhibit* exhibit) {
  if (!animal || !exhibit) {
    return false;
  }

  // check if animal exists in exhibit first
  if (!exhibit->containsAnimal(animal)) {
    return false;
  }

  return exhibit->removeAnimal(animal);
}

bool Zoo::moveAnimalToExhibit(Animal* animal, Exhibit* exhibit) {
  if (!animal || !exhibit) {
    return false;
  }

  // remove animal from its current exhibit
  Exhibit* old_exhibit = findAnimalLocation(animal);
  if (!old_exhibit) {
    std::cout
        << "Animal not found in any exhibit! Need to add animal to an exhibit before moving!\n";
    return false;
  }

  // check if animal is already in the exhibit
  if (old_exhibit == exhibit) {
    std::cout << animal->getName() << " is already in Exhibit " << exhibit->getName() << ".\n";
    return false;
  }

  // see if animal can be added to new exhibit
  if (!exhibit->canAddAnimal()) {
    std::cout << "Exhibit is full!\n";
    return false;
  }

  // remove animal from old exhibit
  if (!old_exhibit->removeAnimal(animal)) {
    std::cout << "Failed to remove animal from its current exhibit!\n";
    return false;
  }

  // add animal to new exhibit
  if (!exhibit->addAnimal(animal)) {
    std::cout << "Failed to add animal to new exhibit!\n";
    // add animal back to old exhibit
    old_exhibit->addAnimal(animal);
    return false;
  }

  std::cout << "Moved " << animal->getName() << " to " << exhibit->getName() << ".\n";
  return true;
}

void Zoo::removeDeadAnimals() {
  std::vector<std::string> dead_animals;
  for (const auto& animal : animals_) {
    if (!animal->isAlive()) {
      dead_animals.push_back(animal->getName() + " the " + animal->getSpecies());

      // remove animal from exhibit if in one
      Exhibit* exhibit = findAnimalLocation(animal.get());
      if (exhibit) {
        exhibit->removeAnimal(animal.get());
      }
    }
  }

  animals_.erase(
      std::remove_if(animals_.begin(), animals_.end(),
                     [](const std::unique_ptr<Animal>& animal) { return !animal->isAlive(); }),
      animals_.end());

  for (const auto& name : dead_animals) {
    std::cout << name << " has died and has been removed from the zoo.\n";
  }
}

bool Zoo::spendMoney(double amount) {
  if (balance_ < amount) {
    return false;
  }

  balance_ -= amount;
  return true;
}

void Zoo::updateAnimalStats() {
  for (const auto& animal : animals_) {
    animal->updateStatsEndOfDay();
  }
}

int Zoo::calculateVisitorCount() const {
  int base_visitors = static_cast<int>(animals_.size()) * 10;

  double rating_multiplier = 1.0 + (calculateZooRating() / 5.0);
  int visitors = static_cast<int>(base_visitors * rating_multiplier);

  int happiness_bonus = 0;
  for (const auto& animal : animals_) {
    if (animal->getHappinessLevel() > 70) {
      happiness_bonus += static_cast<int>((animal->getHappinessLevel() / 10.0) * 20);
    }
  }
  return visitors + happiness_bonus;
}

double Zoo::calculateDailyRevenue(int visitor_count) const {
  constexpr double TICKET_PRICE = 15.0;
  return visitor_count * TICKET_PRICE;
}

double Zoo::calculateDailyExpenses() const {
  double total = 0.0;

  // animal maintenance costs
  for (const auto& animal : animals_) {
    total += animal->getMaintenanceCost();
  }

  // exhibit maintenance costs
  for (const auto& exhibit : exhibits_) {
    total += exhibit->getMaintenanceCost();
  }

  return total;
}

double Zoo::calculateZooRating() const {
  if (animals_.empty()) {
    return 0.0;
  }

  double total_happiness = 0.0;
  double total_health = 0.0;
  for (const auto& animal : animals_) {
    total_happiness += animal->getHappinessLevel();
    total_health += animal->getHealthLevel();
  }

  double avg_happiness = total_happiness / getAnimalCount();
  double happiness_score = (avg_happiness / 100.0) * 2.0;
  double avg_health = total_health / getAnimalCount();
  double health_score = (avg_health / 100.0) * 1.5;

  double cleanliness_score = 0.5;
  if (getExhibitCount() > 0) {
    double total_cleanliness = 0.0;
    for (const auto& exhibit : exhibits_) {
      total_cleanliness += exhibit->getCleanliness();
    }
    double avg_cleanliness = total_cleanliness / getExhibitCount();
    cleanliness_score = (avg_cleanliness / 100.0) * 1.0;
  }

  double financial_score = 0.0;
  if (balance_ > 5000) {
    financial_score = 0.5;
  } else if (balance_ > 2000) {
    financial_score = 0.3;
  } else if (balance_ > 500) {
    financial_score = 0.2;
  }

  double total_rating = happiness_score + health_score + cleanliness_score + financial_score;

  if (total_rating > 5.0) {
    total_rating = 5.0;
  }
  if (total_rating < 0.0) {
    total_rating = 0.0;
  }

  return total_rating;
}

void Zoo::advanceDay() {
  updateAnimalStats();
  removeDeadAnimals();

  // degrade cleanliness of exhibits
  for (const auto& exhibit : exhibits_) {
    exhibit->updateCleanliness(-5);
  }

  int visitors = calculateVisitorCount();
  double revenue = calculateDailyRevenue(visitors);
  double expenses = calculateDailyExpenses();

  // update balance
  balance_ += revenue;
  balance_ -= expenses;

  int dirty_exhibits = 0;
  int sick_animals = 0;
  int unhappy_animals = 0;
  int needy_animals = 0;

  for (const auto& animal : animals_) {
    if (animal->getHealthLevel() < 50) {
      sick_animals++;
    }

    if (animal->getHappinessLevel() < 50) {
      unhappy_animals++;
    }

    if (animal->needsAttention()) {
      needy_animals++;
    }
  }

  for (const auto& exhibit : exhibits_) {
    if (exhibit->needsCleaning()) {
      dirty_exhibits++;
    }
  }

  std::cout << "Animals:\n";
  std::cout << "  Total: " << getAnimalCount() << "\n";
  std::cout << "  Sick: " << sick_animals << "\n";
  std::cout << "  Unhappy: " << unhappy_animals << "\n";
  std::cout << "  Need Attention: " << needy_animals << "\n";
  std::cout << "Exhibits Needing Cleaning: " << dirty_exhibits << "\n";
  std::cout << "Visitors: " << visitors << "\n";
  std::cout << "Revenue : $" << revenue << "\n";
  std::cout << "Expenses: $" << expenses << "\n";
  std::cout << "Net     : $" << revenue - expenses << "\n";
  std::cout << "Balance : $" << balance_ << "\n";
  std::cout << "Zoo Rating: " << calculateZooRating() << "/5.0\n";
  std::cout << "----------------------------------\n";

  day_++;
  std::cout << "\nStart Day " << day_ << "\n";
}

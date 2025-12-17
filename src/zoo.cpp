#include "zoo.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>

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
    std::cout << animal->getName() << " is already in exhibit " << exhibit->getName() << ".\n ";
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
    std::cout << animal->getName() << " is already in exhibit " << exhibit->getName() << ".\n";
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
    std::cout << name << " has died.\n";
  }
}

void Zoo::earnBonus(double amount) {
  bonus_earned_ += amount;
}

bool Zoo::spendMoney(double amount) {
  if (balance_ < amount) {
    return false;
  }

  balance_ -= amount;
  return true;
}

void Zoo::addMoney(double amount) {
  balance_ += amount;
}

void Zoo::updateAnimalStats() {
  for (const auto& animal : animals_) {
    animal->updateStatsEndOfDay();  // daily decay

    // apply health penalties for animal neglect
    // decline health due to starvation
    int hunger = animal->getHungerLevel();
    if (hunger >= 90) {
      animal->updateHealth(-30);
    } else if (hunger >= 75) {
      animal->updateHealth(-20);
    } else if (hunger >= 60) {
      animal->updateHealth(-15);
    } else if (hunger >= 45) {
      animal->updateHealth(-5);
    }

    // decline health due to unhappiness
    int happiness = animal->getHappinessLevel();
    if (happiness < 20) {
      animal->updateHealth(-15);
    } else if (happiness < 40) {
      animal->updateHealth(-5);
    } else if (happiness < 60) {
      animal->updateHealth(-2);
    }

    // decline health due to exhaustion
    int energy = animal->getEnergyLevel();
    if (energy < 20) {
      animal->updateHealth(-10);
    } else if (energy < 40) {
      animal->updateHealth(-5);
    }

    Exhibit* exhibit = findAnimalLocation(animal.get());
    // habitat matching happiness bonus
    if (exhibit && exhibit->getType() == animal->getPreferredHabitat()) {
      animal->updateHappiness(3);
    } else if (exhibit) {
      animal->updateHappiness(-2);
    }
    // happiness penalty for homeless animals
    if (!exhibit) {
      animal->updateHappiness(-15);
      animal->updateHealth(-5);
    }

    animal->sleep();  // nightly recovery
  }
}

int Zoo::calculateVisitorCount() {
  int base_visitors = static_cast<int>(getAnimalCount()) * 5;

  double rating = calculateZooRating();
  double rating_multiplier;
  if (rating >= 4.0) {  // excellent, 2x visitors
    rating_multiplier = 2.0;
  } else if (rating >= 3.5) {  // good, 1.5x visitors
    rating_multiplier = 1.5;
  } else if (rating >= 3.0) {  // ok, normal
    rating_multiplier = 1.0;
  } else if (rating >= 2.5) {  // poor, -30%
    rating_multiplier = 0.7;
  } else if (rating >= 2.0) {  // bad, -60%
    rating_multiplier = 0.4;
  } else {  // terrible, -80%
    rating_multiplier = 0.2;
  }

  int visitors = static_cast<int>(base_visitors * rating_multiplier);

  std::set<std::string> species;
  for (const auto& animal : animals_) {
    species.insert(animal->getSpecies());
  }
  int diversity_bonus = static_cast<int>(species.size());  // +1 visitor per species

  int rarity_bonus = 0;
  for (const auto& animal : animals_) {
    if (animal->getSpecies() == "Elephant") {
      rarity_bonus += 6;
    } else if (animal->getSpecies() == "Bear" || animal->getSpecies() == "Lion") {
      rarity_bonus += 4;
    } else if (animal->getSpecies() == "Monkey" || animal->getSpecies() == "Penguin") {
      rarity_bonus += 2;
    }
  }

  int happiness_bonus = 0;
  for (const auto& animal : animals_) {
    if (animal->getHappinessLevel() > 80) {
      happiness_bonus += 2;  // +2 visitors per happy animal
    }
  }

  int neglect_penalty = 0;
  for (const auto& animal : animals_) {
    if (animal->needsAttention()) {
      neglect_penalty += 3;  // -3 visitors per neglected animal
    }
  }

  int cleanliness_penalty = 0;
  for (const auto& exhibit : exhibits_) {
    if (exhibit->needsCleaning()) {
      cleanliness_penalty += 2;  // -2 visitors per dirty exhibit
    }
  }

  int final_visitors = visitors + rarity_bonus + diversity_bonus + happiness_bonus -
                       neglect_penalty - cleanliness_penalty;
  return final_visitors < 0 ? 0 : final_visitors;
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

  double staff_wages = 30.0;
  staff_wages += getAnimalCount() * 8.0;
  staff_wages += getExhibitCount() * 5.0;
  total += staff_wages;

  return total;
}

// get balance after accounting for projected revenue and expenses
double Zoo::getProjectedBalance() {
  // don't use calculateVisitorCount here to avoid circular dependency
  int visitors = static_cast<int>(getAnimalCount() * 5);
  double revenue = calculateDailyRevenue(visitors);
  double expenses = calculateDailyExpenses();
  return balance_ + revenue - expenses;
}

double Zoo::calculateZooRating() {
  double happiness_score = 0.0;
  double health_score = 0.0;

  if (getAnimalCount() > 0) {
    // animal happiness = 50% weight
    double total_happiness = 0.0;
    for (const auto& animal : animals_) {
      total_happiness += animal->getHappinessLevel();
    }
    double avg_happiness = total_happiness / getAnimalCount();
    happiness_score = (avg_happiness / 100.0) * 2.5;  // max 2.5 stars

    // animal health = 30% weight
    double total_health = 0.0;
    for (const auto& animal : animals_) {
      total_health += animal->getHealthLevel();
    }
    double avg_health = total_health / getAnimalCount();
    health_score = (avg_health / 100.0) * 1.5;  // max 1.5 stars
  }

  // exhibit cleanliness = 15% weight
  double cleanliness_score = 0.5;
  if (getExhibitCount() > 0) {
    double total_cleanliness = 0.0;
    for (const auto& exhibit : exhibits_) {
      total_cleanliness += exhibit->getCleanliness();
    }
    double avg_cleanliness = total_cleanliness / getExhibitCount();
    cleanliness_score = (avg_cleanliness / 100.0) * 0.75;  // max 0.75 stars
  }

  // zoo financial health = 5% weight
  double financial_score = 0.0;
  double projected_balance = getProjectedBalance();
  if (projected_balance > 3000) {
    financial_score = 0.25;  // max 0.25 stars
  } else if (projected_balance > 1500) {
    financial_score = 0.15;
  } else if (projected_balance > 500) {
    financial_score = 0.05;
  }

  double total_rating = happiness_score + health_score + cleanliness_score + financial_score;
  return std::max(0.0, std::min(5.0, total_rating));
}

void Zoo::viewZooRatingBreakdown() {
  // animal happiness
  double total_happiness = 0.0;
  for (const auto& animal : animals_) {
    total_happiness += animal->getHappinessLevel();
  }
  double avg_happiness = total_happiness / getAnimalCount();
  std::cout << "Animal Happiness: " << std::fixed << std::setprecision(1) << avg_happiness
            << "/100\n";

  // animal health
  double total_health = 0.0;
  for (const auto& animal : animals_) {
    total_health += animal->getHealthLevel();
  }
  double avg_health = total_health / getAnimalCount();
  std::cout << "Animal Health: " << std::fixed << std::setprecision(1) << avg_health << "/100\n";

  // exhibit cleanliness
  if (getExhibitCount() > 0) {
    double total_cleanliness = 0.0;
    for (const auto& exhibit : exhibits_) {
      total_cleanliness += exhibit->getCleanliness();
    }
    double avg_cleanliness = total_cleanliness / getExhibitCount();
    std::cout << "Exhibit Cleanliness: " << std::fixed << std::setprecision(1) << avg_cleanliness
              << "/100\n";
  }

  std::cout << "Financial Stability: ";
  if (balance_ > 3000) {
    std::cout << "Excellent\n";
  } else if (balance_ > 1500) {
    std::cout << "Good\n";
  } else if (balance_ > 500) {
    std::cout << "Fair\n";
  } else {
    std::cout << "Poor\n";
  }
}

std::string Zoo::getRatingMessage(double rating) {
  if (rating >= 4.5) {
    return "(Outstanding)";
  } else if (rating >= 4.0) {
    return "(Excellent)";
  } else if (rating >= 3.5) {
    return "(Great)";
  } else if (rating >= 3.0) {
    return "(Good)";
  } else if (rating >= 2.5) {
    return "(Poor)";
  } else if (rating >= 2.0) {
    return "(Bad)";
  } else {
    return "(Terrible)";
  }
}

void Zoo::degradeStats() {
  updateAnimalStats();
  removeDeadAnimals();

  // degrade cleanliness of exhibits
  for (const auto& exhibit : exhibits_) {
    exhibit->updateCleanliness(-15);
  }
}

void Zoo::updateBalance() {
  int visitors = calculateVisitorCount();
  double revenue = calculateDailyRevenue(visitors);
  double expenses = calculateDailyExpenses();

  // update balance
  balance_ += revenue;
  balance_ -= expenses;
}

void Zoo::advanceDay() {
  day_++;
}

void Zoo::displayEndOfDaySummary() {
  int dirty_exhibits = 0;
  int sick_animals = 0;
  int hungry_animals = 0;
  int unhappy_animals = 0;
  int tired_animals = 0;
  int needy_animals = 0;
  int homeless_animals = 0;

  for (const auto& animal : animals_) {
    if (animal->getHealthLevel() < 50) {
      sick_animals++;
    }

    if (animal->getHungerLevel() > 50) {
      hungry_animals++;
    }

    if (animal->getHappinessLevel() < 50) {
      unhappy_animals++;
    }

    if (animal->getEnergyLevel() < 50) {
      tired_animals++;
    }

    if (animal->needsAttention()) {
      needy_animals++;
    }

    if (!findAnimalLocation(animal.get())) {
      homeless_animals++;
    }
  }

  for (const auto& exhibit : exhibits_) {
    if (exhibit->needsCleaning()) {
      dirty_exhibits++;
    }
  }

  int visitors = calculateVisitorCount();
  double revenue = calculateDailyRevenue(visitors);
  double expenses = calculateDailyExpenses();

  std::cout << "\nAnimals:\n";
  std::cout << "  Total: " << getAnimalCount() << "\n";
  std::cout << "  Sick: " << sick_animals << "\n";
  std::cout << "  Hungry: " << hungry_animals << "\n";
  std::cout << "  Unhappy: " << unhappy_animals << "\n";
  std::cout << "  Tired: " << tired_animals << "\n";
  std::cout << "  Need Attention: " << needy_animals << "\n";
  std::cout << "  Homeless: " << homeless_animals << "\n";

  std::cout << "\nExhibits:\n";
  std::cout << "  Total: " << getExhibitCount() << "\n";
  std::cout << "  Need Cleaning: " << dirty_exhibits << "\n";

  std::cout << "\nStats:\n";
  std::cout << "  Visitors: " << visitors << "\n";
  std::cout << "  Revenue : $" << revenue << "\n";
  std::cout << "  Expenses: $" << expenses << "\n";
  std::cout << "  Net     : $" << revenue - expenses << "\n";
  std::cout << "  Bonus   : $" << bonus_earned_ << "\n";
  std::cout << "  Balance : $" << balance_ << "\n";

  double rating = calculateZooRating();
  std::cout << "\nZoo Rating: " << std::fixed << std::setprecision(1) << rating << "/5.0 "
            << getRatingMessage(rating) << "\n";
  std::cout << "----------------------------------------------------------------------\n";
}

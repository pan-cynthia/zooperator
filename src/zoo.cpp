#include "zoo.h"

#include <algorithm>
#include <iostream>

Zoo::Zoo(std::string name, double starting_balance)
    : name_(std::move(name)), day_(0), balance_(starting_balance) {}

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

  std::cout << "Purchased " << animal->getName() << " the " << animal->getSpecies() << "for $"
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
    removeAnimalFromExhibit(animal, exhibit);
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

  std::cout << "Purchased Exhibit" << exhibit->getName() << "for $" << cost << ".\n";
  balance_ -= cost;
  exhibits_.push_back(std::move(exhibit));
  return true;
}

Exhibit* Zoo::getExhibit(size_t index) {
  if (index >= exhibits_.size()) {
    return nullptr;
  }
  return exhibits_[index].get();
}

std::vector<Exhibit*> Zoo::getExhibitsNeedingCleaning() {
  std::vector<Exhibit*> exhibits;
  for (const auto& ptr : exhibits_) {
    if (ptr->getCleanliness() < 50) {
      exhibits.push_back(ptr.get());
    }
  }
  return exhibits;
}

size_t Zoo::getExhibitCount() const {
  return exhibits_.size();
}

Exhibit* Zoo::findAnimalLocation(Animal* animal) {
  auto it = animal_locations_.find(animal);
  if (it == animal_locations_.end()) {
    return nullptr;
  }
  return it->second;
}

bool Zoo::addAnimalToExhibit(Animal* animal, Exhibit* exhibit) {
  if (exhibit->addAnimal(animal)) {
    animal_locations_[animal] = exhibit;
    return true;
  }
  return false;
}

bool Zoo::removeAnimalFromExhibit(Animal* animal, Exhibit* exhibit) {
  if (exhibit->removeAnimal(animal)) {
    animal_locations_.erase(animal);
    return true;
  }
  return false;
}

bool Zoo::moveAnimalToExhibit(Animal* animal, Exhibit* exhibit) {
  if (!animal || !exhibit) {
    return false;
  }

  // remove animal from its current exhibit
  Exhibit* old_exhibit = findAnimalLocation(animal);
  if (!old_exhibit) {
    std::cout << "Animal not found in any exhibit!\n";
    return false;
  }

  // see if animal can be added to new exhibit
  if (!exhibit->canAddAnimal()) {
    std::cout << "Exhibit is full!\n";
    return false;
  }

  // remove animal from old exhibit
  if (!removeAnimalFromExhibit(animal, old_exhibit)) {
    std::cout << "Failed to remove animal from its current exhibit!\n";
    return false;
  }

  // add animal to new exhibit
  if (!addAnimalToExhibit(animal, exhibit)) {
    std::cout << "Failed to add animal to new exhibit!\n";
    // add animal back to old exhibit
    addAnimalToExhibit(animal, old_exhibit);
    return false;
  }
  return true;
}

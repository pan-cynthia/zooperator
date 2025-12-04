#include "exhibit.h"

#include <algorithm>
#include <iostream>
#include <utility>

Exhibit::Exhibit(std::string name, std::string type, int capacity, double purchase_cost,
                 double maintenance_cost)
    : name_(std::move(name)),
      type_(std::move(type)),
      capacity_(capacity),
      cleanliness_(100),
      purchase_cost_(purchase_cost),
      maintenance_cost_(maintenance_cost) {}

bool Exhibit::canAddAnimal() const {
  return static_cast<int>(animals_.size()) < capacity_;
}

bool Exhibit::addAnimal(Animal* animal) {
  if (!animal) {
    std::cout << "Cannot add null animal!\n";
    return false;
  }

  if (containsAnimal(animal)) {
    std::cout << animal->getName() << " is already in this exhibit!\n";
    return false;
  }

  if (!canAddAnimal()) {
    std::cout << "Exhibit " << name_ << " is at full capacity!\n";
    return false;
  }

  animals_.push_back(animal);
  std::cout << "Added " << animal->getName() << " to Exhibit " << name_ << "!\n";
  return true;
}

bool Exhibit::removeAnimal(Animal* animal) {
  if (!animal) {
    return false;
  }

  auto it = std::find(animals_.begin(), animals_.end(), animal);

  if (it == animals_.end()) {
    std::cout << "Animal not found in this exhibit!\n";
    return false;
  }

  std::cout << "Removed " << (*it)->getName() << " from Exhibit " << name_ << "!\n";
  animals_.erase(it);
  return true;
}

void Exhibit::removeAllAnimalsFromExhibit() {
  animals_.clear();
}

bool Exhibit::containsAnimal(Animal* animal) const {
  if (!animal) {
    return false;
  }

  return std::find(animals_.begin(), animals_.end(), animal) != animals_.end();
}

Animal* Exhibit::getAnimal(size_t index) {
  if (index >= animals_.size()) {
    return nullptr;
  }
  return animals_[index];
}

const std::string& Exhibit::getName() const {
  return name_;
}

const std::string& Exhibit::getType() const {
  return type_;
}

int Exhibit::getMaxCapacity() const {
  return capacity_;
}

size_t Exhibit::getCapacityUsed() const {
  return animals_.size();
}

int Exhibit::getCleanliness() const {
  return cleanliness_;
}

double Exhibit::getPurchaseCost() const {
  return purchase_cost_;
}

double Exhibit::getMaintenanceCost() const {
  return maintenance_cost_;
}

bool Exhibit::needsCleaning() {
  return cleanliness_ < 50;
}

void Exhibit::updateCleanliness(int delta) {
  cleanliness_ += delta;
  if (cleanliness_ > 100) {
    cleanliness_ = 100;
  }
  if (cleanliness_ < 0) {
    cleanliness_ = 0;
  }
}

void Exhibit::clean() {
  cleanliness_ = 100;
  std::cout << "Exhibit " << name_ << " has been cleaned!\n";
}

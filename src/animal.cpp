#include "animal.h"

#include <iostream>
#include <utility>

Animal::Animal(std::string name, std::string species, int age)
    : name_(std::move(name)),
      species_(std::move(species)),
      age_(age),
      health_(100),
      hunger_(0),
      happiness_(100),
      energy_(100),
      purchase_cost_(0.0),
      feeding_cost_(0.0),
      maintenance_cost_(0.0) {}

// getters
const std::string& Animal::getName() const {
  return name_;
}

const std::string& Animal::getSpecies() const {
  return species_;
}

int Animal::getAge() const {
  return age_;
}

int Animal::getHealthLevel() const {
  return health_;
}

int Animal::getHungerLevel() const {
  return hunger_;
}

int Animal::getHappinessLevel() const {
  return happiness_;
}

int Animal::getEnergyLevel() const {
  return energy_;
}

bool Animal::isAlive() const {
  return health_ > 0;
}

bool Animal::needsAttention() const {
  return health_ < 20 || hunger_ > 80 || happiness_ < 20 || energy_ < 20;
}

double Animal::getPurchaseCost() const {
  return purchase_cost_;
}

double Animal::getFeedingCost() const {
  return feeding_cost_;
}

double Animal::getMaintenanceCost() const {
  return maintenance_cost_;
}

// setters
void Animal::updateHealth(int delta) {
  health_ += delta;
  if (health_ > 100) {
    health_ = 100;
  }
  if (health_ < 0) {
    health_ = 0;
  }
}

void Animal::updateHunger(int delta) {
  hunger_ += delta;
  if (hunger_ > 100) {
    hunger_ = 100;
  }
  if (hunger_ < 0) {
    hunger_ = 0;
  }
}

void Animal::updateHappiness(int delta) {
  happiness_ += delta;
  if (happiness_ > 100) {
    happiness_ = 100;
  }
  if (happiness_ < 0) {
    happiness_ = 0;
  }
}

void Animal::updateEnergy(int delta) {
  energy_ += delta;
  if (energy_ > 100) {
    energy_ = 100;
  }
  if (energy_ < 0) {
    energy_ = 0;
  }
}

void Animal::eat(int amount) {
  if (amount <= 0) {
    std::cout << getName() << " needs a positive amount of food!\n";
    return;
  }

  updateHunger(-amount);
  updateHappiness(5);
  std::cout << getName() << " the " << getSpecies() << " is eating.\n";
}

void Animal::sleep(int hours) {
  if (hours <= 0) {
    std::cout << getName() << " needs positive hours of sleep!\n";
    return;
  }

  updateEnergy(hours * 10);
  updateHealth(hours);
  updateHunger(hours * 2);
  std::cout << getName() << " the " << getSpecies() << " is sleeping.\n";
}

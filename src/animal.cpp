#include "animal.h"

#include <algorithm>
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
  return health_ < CRITICAL_THRESHOLD || hunger_ > (MAX_STAT - CRITICAL_THRESHOLD) ||
         happiness_ < CRITICAL_THRESHOLD || energy_ < CRITICAL_THRESHOLD;
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

int Animal::clamp(int value, int min_val, int max_val) {
  return std::max(min_val, std::min(value, max_val));
}

// setters
void Animal::updateHealth(int delta) {
  health_ = clamp(health_ + delta, MIN_STAT, MAX_STAT);
}

void Animal::updateHunger(int delta) {
  hunger_ = clamp(hunger_ + delta, MIN_STAT, MAX_STAT);
}

void Animal::updateHappiness(int delta) {
  happiness_ = clamp(happiness_ + delta, MIN_STAT, MAX_STAT);
}

void Animal::updateEnergy(int delta) {
  energy_ = clamp(energy_ + delta, MIN_STAT, MAX_STAT);
}

void Animal::updateStatsEndOfDay() {
  updateHunger(15);
  updateHappiness(-15);
  updateEnergy(-10);
}

void Animal::setName(const std::string& name) {
  name_ = name;
}

void Animal::eat(int amount) {
  if (amount <= 0) {
    std::cout << getName() << " needs a positive amount of food!\n";
    return;
  }

  updateHunger(-amount);
  updateHappiness(5);
  updateEnergy(5);
  std::cout << getName() << " the " << getSpecies() << " is eating.\n";
}

void Animal::sleep() {
  updateEnergy(15);
  updateHealth(5);
  updateHunger(5);
}

void Animal::receivePlay() {
  updateEnergy(-10);
  updateHappiness(15);
  updateHunger(5);
}

void Animal::receiveExercise() {
  updateEnergy(-20);
  updateHealth(10);
  updateHappiness(10);
  updateHunger(10);
}

void Animal::receiveTreatment() {
  updateHealth(30);
  updateEnergy(10);
}

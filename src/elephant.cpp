#include "elephant.h"

#include <iostream>
#include <utility>

Elephant::Elephant(std::string name, int age) : Animal(std::move(name), "Elephant", age) {
  purchase_cost_ = 1500.0;
  feeding_cost_ = 40.0;
  maintenance_cost_ = 64.0;
}

void Elephant::makeSound() const {
  std::cout << getName() << " the Elephant is trumpeting!\n";
}

void Elephant::updateStatsEndOfDay() {
  updateHunger(14);
  updateHappiness(-5);
  updateEnergy(-10);
}

std::string Elephant::getPreferredHabitat() const {
  return "Savanna";
}

#include "elephant.h"

#include <iostream>
#include <utility>

Elephant::Elephant(std::string name, int age) : Animal(std::move(name), "Elephant", age) {
  purchase_cost_ = 1200.0;
  feeding_cost_ = 50.0;
  maintenance_cost_ = 80.0;
}

void Elephant::makeSound() const {
  std::cout << getName() << " the Elephant is trumpeting!\n";
}

void Elephant::updateStatsEndOfDay() {
  updateHunger(15);
  updateHappiness(-8);
  updateEnergy(-11);
}

std::string Elephant::getPreferredHabitat() const {
  return "Savanna";
}

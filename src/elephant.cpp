#include "elephant.h"

#include <iostream>
#include <utility>

Elephant::Elephant(std::string name, int age) : Animal(std::move(name), "Elephant", age) {
  purchase_cost_ = 3000.0;
  feeding_cost_ = 60.0;
  maintenance_cost_ = 100.0;
}

void Elephant::makeSound() const {
  std::cout << getName() << " the Elephant is trumpeting!\n";
}

void Elephant::updateStatsEndOfDay() {
  updateHunger(20);
  updateHappiness(-8);
  updateEnergy(-14);
}

std::string Elephant::getPreferredHabitat() const {
  return "Savanna";
}

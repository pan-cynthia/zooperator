#include "lion.h"

#include <iostream>
#include <utility>

Lion::Lion(std::string name, int age) : Animal(std::move(name), "Lion", age) {
  purchase_cost_ = 1000.0;
  feeding_cost_ = 40.0;
  maintenance_cost_ = 60.0;
}

void Lion::makeSound() const {
  std::cout << getName() << " the Lion is roaring!\n";
}

void Lion::updateStatsEndOfDay() {
  updateHunger(17);
  updateHappiness(-10);
  updateEnergy(-8);
}

std::string Lion::getPreferredHabitat() const {
  return "Savanna";
}

#include "lion.h"

#include <iostream>
#include <utility>

Lion::Lion(std::string name, int age) : Animal(std::move(name), "Lion", age) {
  purchase_cost_ = 1200.0;
  feeding_cost_ = 32.0;
  maintenance_cost_ = 48.0;
}

void Lion::makeSound() const {
  std::cout << getName() << " the Lion is roaring!\n";
}

void Lion::updateStatsEndOfDay() {
  updateHunger(15);
  updateHappiness(-3);
  updateEnergy(-7);
}

std::string Lion::getPreferredHabitat() const {
  return "Savanna";
}

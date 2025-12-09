#include "lion.h"

#include <iostream>
#include <utility>

Lion::Lion(std::string name, int age) : Animal(std::move(name), "Lion", age) {
  purchase_cost_ = 2000.0;
  feeding_cost_ = 50.0;
  maintenance_cost_ = 80.0;
}

void Lion::makeSound() const {
  std::cout << getName() << " the Lion is roaring!\n";
}

void Lion::updateStatsEndOfDay() {
  updateHunger(22);
  updateHappiness(-5);
  updateEnergy(-10);
}

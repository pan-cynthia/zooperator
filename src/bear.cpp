#include "bear.h"

#include <iostream>
#include <utility>

Bear::Bear(std::string name, int age) : Animal(std::move(name), "Bear", age) {
  purchase_cost_ = 1000.0;
  feeding_cost_ = 32.0;
  maintenance_cost_ = 48.0;
}

void Bear::makeSound() const {
  std::cout << getName() << " the Bear is growling!\n";
}

void Bear::updateStatsEndOfDay() {
  updateHunger(8);
  updateHappiness(-2);
  updateEnergy(-5);
}

std::string Bear::getPreferredHabitat() const {
  return "Forest";
}

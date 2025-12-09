#include "bear.h"

#include <iostream>
#include <utility>

Bear::Bear(std::string name, int age) : Animal(std::move(name), "Bear", age) {
  purchase_cost_ = 1500.0;
  feeding_cost_ = 40.0;
  maintenance_cost_ = 60.0;
}

void Bear::makeSound() const {
  std::cout << getName() << " the Bear is growling!\n";
}

void Bear::updateStatsEndOfDay() {
  updateHunger(12);
  updateHappiness(-3);
  updateEnergy(-8);
}

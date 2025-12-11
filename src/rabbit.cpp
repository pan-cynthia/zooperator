#include "rabbit.h"

#include <iostream>
#include <utility>

Rabbit::Rabbit(std::string name, int age) : Animal(std::move(name), "Rabbit", age) {
  purchase_cost_ = 150.0;
  feeding_cost_ = 4.0;
  maintenance_cost_ = 6.0;
}

void Rabbit::makeSound() const {
  std::cout << getName() << " the Rabbit is thumping!\n";
}

void Rabbit::updateStatsEndOfDay() {
  updateHunger(12);
  updateHappiness(-4);
  updateEnergy(-8);
}

std::string Rabbit::getPreferredHabitat() const {
  return "Grassland";
}

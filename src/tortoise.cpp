#include "tortoise.h"

#include <iostream>
#include <utility>

Tortoise::Tortoise(std::string name, int age) : Animal(std::move(name), "Tortoise", age) {
  purchase_cost_ = 250.0;
  feeding_cost_ = 6.0;
  maintenance_cost_ = 12.0;
}

void Tortoise::makeSound() const {
  std::cout << getName() << " the Tortoise is hissing!\n";
}

void Tortoise::updateStatsEndOfDay() {
  updateHunger(9);
  updateHappiness(-6);
  updateEnergy(-5);
}

std::string Tortoise::getPreferredHabitat() const {
  return "Grassland";
}

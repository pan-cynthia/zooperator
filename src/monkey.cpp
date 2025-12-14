#include "monkey.h"

#include <iostream>
#include <utility>

Monkey::Monkey(std::string name, int age) : Animal(std::move(name), "Monkey", age) {
  purchase_cost_ = 600.0;
  feeding_cost_ = 15.0;
  maintenance_cost_ = 25.0;
}

void Monkey::makeSound() const {
  std::cout << getName() << " the Monkey is screeching!\n";
}

void Monkey::updateStatsEndOfDay() {
  updateHunger(13);
  updateHappiness(-10);
  updateEnergy(-11);
}

std::string Monkey::getPreferredHabitat() const {
  return "Jungle";
}
